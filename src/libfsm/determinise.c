/*
 * Copyright 2019 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#include <assert.h>
#include <stddef.h>
#include <errno.h>

#include <fsm/fsm.h>
#include <fsm/capture.h>
#include <fsm/pred.h>
#include <fsm/walk.h>

#include <adt/alloc.h>
#include <adt/set.h>
#include <adt/edgeset.h>
#include <adt/stateset.h>
#include <adt/hashset.h>
#include <adt/mappinghashset.h>

#include "internal.h"
#include "capture.h"
#include "endids.h"

#define DUMP_MAPPING 0
#define LOG_DETERMINISE_CLOSURES 0
#define LOG_DETERMINISE_CAPTURES 0

/*
 * This maps a DFA state onto its associated NFA symbol closure, such that an
 * existing DFA state may be found given any particular set of NFA states
 * forming a symbol closure.
 */
struct mapping {
	/* The set of NFA states forming the symbol closure for this DFA state */
	struct state_set *closure;

	/* The DFA state associated with this epsilon closure of NFA states */
	fsm_state_t dfastate;

	/* Newly-created DFA edges */
	struct edge_set *edges;
};

struct reverse_mapping {
	unsigned count;
	unsigned ceil;
	fsm_state_t *list;
};

struct det_copy_capture_actions_env {
	char tag;
	struct fsm *dst;
	struct reverse_mapping *reverse_mappings;
	int ok;
};

static int
remap_capture_actions(struct mapping_hashset *mappings,
    struct fsm *dst_dfa, struct fsm *src_nfa);

static int
add_reverse_mapping(const struct fsm_alloc *alloc,
    struct reverse_mapping *reverse_mappings,
    fsm_state_t dfa_state, fsm_state_t nfa_state);

static int
det_copy_capture_actions(struct reverse_mapping *reverse_mappings,
    struct fsm *dst, struct fsm *src);

static int
cmp_mapping(const void *a, const void *b)
{
	const struct mapping * const *ma = a, * const *mb = b;

	assert(ma != NULL && *ma != NULL);
	assert(mb != NULL && *mb != NULL);

	return state_set_cmp((*ma)->closure, (*mb)->closure);
}

static unsigned long
hash_mapping(const void *a)
{
	const struct mapping *m = a;

	/* TODO: could cache the hashed value in the mapping struct,
	 * or populate it when making the mapping */
	return state_set_hash(m->closure);
}

static struct mapping *
mapping_find(const struct mapping_hashset *mappings, const struct state_set *closure)
{
	struct mapping *m, search;

	assert(mappings != NULL);
	assert(closure != NULL);

	search.closure = (void *) closure;
	m = mapping_hashset_find(mappings, &search);
	if (m != NULL) {
		return m;
	}

	return NULL;
}

/*
 * By contract an existing mapping is assumed to not exist.
 */
static struct mapping *
mapping_add(struct mapping_hashset *mappings, const struct fsm_alloc *alloc,
	fsm_state_t dfastate, struct state_set *closure)
{
	struct mapping *m;

	assert(mappings != NULL);
	assert(!mapping_find(mappings, closure));
	assert(closure != NULL);

	m = f_malloc(alloc, sizeof *m);
	if (m == NULL) {
		return NULL;
	}

	m->closure  = closure;
	m->dfastate = dfastate;
	m->edges    = NULL;

	if (!mapping_hashset_add(mappings, m)) {
		f_free(alloc, m);
		return NULL;
	}

	return m;
}

struct mappingstack {
	const struct fsm_alloc *alloc;
	size_t ceil;
	size_t depth;
	struct mapping **s;
};

#define MAPPINGSTACK_DEF_CEIL 16

static struct mappingstack *
stack_init(const struct fsm_alloc *alloc)
{
	struct mapping **s;
	struct mappingstack *res = f_malloc(alloc, sizeof(*res));
	if (res == NULL) {
		return NULL;
	}

	s = f_malloc(alloc, MAPPINGSTACK_DEF_CEIL * sizeof(s[0]));
	if (s == NULL) {
		f_free(alloc, res);
		return NULL;
	}

	res->alloc = alloc;
	res->ceil = MAPPINGSTACK_DEF_CEIL;
	res->depth = 0;
	res->s = s;

	return res;
}

static void
stack_free(struct mappingstack *stack)
{
	if (stack == NULL) {
		return;
	}
	f_free(stack->alloc, stack->s);
	f_free(stack->alloc, stack);
}

static int
stack_push(struct mappingstack *stack, struct mapping *item)
{
	if (stack->depth + 1 == stack->ceil) {
		size_t nceil = 2 * stack->ceil;
		struct mapping **ns = f_realloc(stack->alloc,
		    stack->s, nceil * sizeof(stack->s[0]));
		if (ns == NULL) {
			return 0;
		}
		stack->ceil = nceil;
		stack->s = ns;
	}

	stack->s[stack->depth] = item;
	stack->depth++;
	return 1;
}

static struct mapping *
stack_pop(struct mappingstack *stack)
{
	struct mapping *m;

	assert(stack != NULL);
	if (stack->depth == 0) {
		return NULL;
	}

	stack->depth--;
	m = stack->s[stack->depth];
	return m;
}

int
fsm_determinise(struct fsm *nfa)
{
	struct mappingstack *stack = NULL;
	struct mapping_hashset *mappings;
	struct mapping *curr;
	size_t dfacount;

	assert(nfa != NULL);

	/*
	 * This NFA->DFA implementation is for Glushkov NFA only; it keeps things
	 * a little simpler by avoiding epsilon closures here, and also a little
	 * faster where we can start with a Glushkov NFA in the first place.
	 */
	if (fsm_has(nfa, fsm_hasepsilons)) {
		if (!fsm_glushkovise(nfa)) {
			return 0;
		}
	}

#if LOG_DETERMINISE_CAPTURES
	fprintf(stderr, "# post_glushkovise\n");
	fsm_print_fsm(stderr, nfa);
	fsm_capture_dump(stderr, "#### post_glushkovise", nfa);
#endif

	dfacount = 0;

	mappings = mapping_hashset_create(nfa->opt->alloc, hash_mapping, cmp_mapping);
	if (mappings == NULL) {
		return 0;
	}

	{
		fsm_state_t start;
		struct state_set *set;

		/*
		 * The starting condition is the epsilon closure of a set of states
		 * containing just the start state.
		 *
		 * You can think of this as having reached the FSM's start state by
		 * previously consuming some imaginary prefix symbol (giving the set
		 * containing just the start state), and then this epsilon closure
		 * is equivalent to the usual case of taking the epsilon closure after
		 * each symbol closure in the main loop.
		 *
		 * (We take a copy of this set for sake of memory ownership only,
		 * for freeing the epsilon closures later).
		 */

		if (!fsm_getstart(nfa, &start)) {
			mapping_hashset_free(mappings);
			return 1;
		}

		set = NULL;

		if (!state_set_add(&set, nfa->opt->alloc, start)) {
			goto error;
		}

#if LOG_DETERMINISE_CAPTURES
		fprintf(stderr, "#### Adding mapping for start state %u -> 0\n", start);
#endif

		curr = mapping_add(mappings, nfa->opt->alloc, dfacount++, set);
		if (curr == NULL) {
			/* TODO: free mappings, set */
			goto error;
		}
	}

	/*
	 * Our "todo" list. It needn't be a stack; we treat it as an unordered
	 * set where we can consume arbitrary items in turn.
	 */
	stack = stack_init(nfa->opt->alloc);
	if (stack == NULL) {
		goto error;
	}

	do {
		struct state_set *sclosures[FSM_SIGMA_COUNT] = { NULL };
		int i;

		assert(curr != NULL);

		/*
		 * The closure of a set is equivalent to the union of closures of
		 * each item. Here we iteratively build up closures[] in-situ
		 * to avoid needing to create a state set to store the union.
		 */
		{
			struct state_iter it;
			fsm_state_t s;

			for (state_set_reset(curr->closure, &it); state_set_next(&it, &s); ) {
				/* TODO: could inline this, and destructively hijack state sets from the source NFA */
				if (!symbol_closure_without_epsilons(nfa, s, sclosures)) {
					/* TODO: free mappings, sclosures, stack */
					goto error;
				}
			}
		}

		for (i = 0; i <= FSM_SIGMA_MAX; i++) {
			struct mapping *m;

			if (sclosures[i] == NULL) {
				continue;
			}

#if LOG_DETERMINISE_CLOSURES
			fprintf(stderr, "fsm_determinise: cur (dfa %u) label '%c': %p:",
			    curr->dfastate, (char)i, (void *)sclosures[i]);
			{
				struct state_iter it;
				fsm_state_t s;

				for (state_set_reset(sclosures[i], &it); state_set_next(&it, &s); ) {
					fprintf(stderr, " %u", s);
				}
				fprintf(stderr, "\n");
			}
#endif

			/*
			 * The set of NFA states sclosures[i] represents a single DFA state.
			 * We use the mappings as a de-duplication mechanism, keyed by this
			 * set of NFA states.
			 */

			/* Use an existing mapping if present, otherwise add a new one */
			m = mapping_find(mappings, sclosures[i]);
			if (m != NULL) {
				/* we already have this closure, free this instance */
				state_set_free(sclosures[i]);

				assert(m->dfastate < dfacount);
			} else {
				m = mapping_add(mappings, nfa->opt->alloc, dfacount++, sclosures[i]);
				if (m == NULL) {
					/* TODO: free mappings, sclosures, stack */
					goto error;
				}

				/* ownership belongs to the mapping now, so don't free sclosures[i] */

				if (!stack_push(stack, m)) {
					/* TODO: free mappings, sclosures, stack */
					goto error;
				}
			}

			if (!edge_set_add(&curr->edges, nfa->opt->alloc, i, m->dfastate)) {
				/* TODO: free mappings, sclosures, stack */
				goto error;
			}
		}

		/* all elements in sclosures[] have been freed or moved to their
		 * respective mapping, so there's nothing to free here */
	} while (curr = stack_pop(stack), curr != NULL);

	{
		struct mapping_hashset_iter it;
		struct mapping *m;
		struct fsm *dfa;

		dfa = fsm_new(nfa->opt);
		if (dfa == NULL) {
			goto error;
		}

#if DUMP_MAPPING
		{
			fprintf(stderr, "#### fsm_determinise: mapping\n");

			/* build reverse mappings table: for every NFA state X, if X is part
			 * of the new DFA state Y, then add Y to a list for X */
			for (m = mapping_hashset_first(mappings, &it); m != NULL; m = mapping_hashset_next(&it)) {
				struct state_iter si;
				fsm_state_t state;
				fprintf(stderr, "%u:", m->dfastate);

				for (state_set_reset(m->closure, &si); state_set_next(&si, &state); ) {
					fprintf(stderr, " %u", state);
				}
				fprintf(stderr, "\n");
			}
			fprintf(stderr, "#### fsm_determinise: end of mapping\n");
		}
#endif
		if (!fsm_addstate_bulk(dfa, dfacount)) {
			/* TODO: free stuff */
			goto error;
		}

		assert(dfa->statecount == dfacount);

		/*
		 * We know state 0 is the start state, because its mapping
		 * was created first.
		 */
		fsm_setstart(dfa, 0);

		for (m = mapping_hashset_first(mappings, &it); m != NULL; m = mapping_hashset_next(&it)) {
			assert(m->dfastate < dfa->statecount);
			assert(dfa->states[m->dfastate].edges == NULL);

			dfa->states[m->dfastate].edges = m->edges;

			/*
			 * The current DFA state is an end state if any of its associated NFA
			 * states are end states.
			 */

			if (!state_set_has(nfa, m->closure, fsm_isend)) {
				continue;
			}

			fsm_setend(dfa, m->dfastate, 1);

			/*
			 * Carry through opaque values, if present. This isn't anything to do
			 * with the DFA conversion; it's meaningful only to the caller.
			 *
			 * The closure may contain non-end states, but at least one state is
			 * known to have been an end state.
			 */
			fsm_carryopaque(nfa, m->closure, dfa, m->dfastate);

			if (!fsm_endid_carry(nfa, m->closure, dfa, m->dfastate)) {
				goto error;
			}
		}

		if (!remap_capture_actions(mappings, dfa, nfa)) {
			goto error;
		}

		fsm_move(nfa, dfa);
	}

	{
		struct mapping_hashset_iter it;
		struct mapping *m;

		for (m = mapping_hashset_first(mappings, &it); m != NULL; m = mapping_hashset_next(&it)) {
			state_set_free(m->closure);
			f_free(nfa->opt->alloc, m);
		}
	}

	mapping_hashset_free(mappings);
	stack_free(stack);

	return 1;

error:

	/* TODO: free stuff */
	mapping_hashset_free(mappings);
	stack_free(stack);

	return 0;
}

static int
remap_capture_actions(struct mapping_hashset *mappings,
    struct fsm *dst_dfa, struct fsm *src_nfa)
{
	struct mapping_hashset_iter it;
	struct state_iter si;
	struct mapping *m;
	struct reverse_mapping *reverse_mappings;
	fsm_state_t state;
	const size_t capture_count = fsm_countcaptures(src_nfa);
	size_t i, j;
	int res = 0;

	if (capture_count == 0) {
		return 1;
	}

	/* This is not 1 to 1 -- if state X is now represented by multiple
	 * states Y in the DFA, and state X has action(s) when transitioning
	 * to state Z, this needs to be added on every Y, for every state
	 * representing Z in the DFA.
	 *
	 * We could probably filter this somehow, at the very least by
	 * checking reachability from every X, but the actual path
	 * handling later will also check reachability. */
	reverse_mappings = f_calloc(dst_dfa->opt->alloc, src_nfa->statecount, sizeof(reverse_mappings[0]));
	if (reverse_mappings == NULL) {
		return 0;
	}

	/* build reverse mappings table: for every NFA state X, if X is part
	 * of the new DFA state Y, then add Y to a list for X */
	for (m = mapping_hashset_first(mappings, &it); m != NULL; m = mapping_hashset_next(&it)) {
		assert(m->dfastate < dst_dfa->statecount);

		for (state_set_reset(m->closure, &si); state_set_next(&si, &state); ) {
			if (!add_reverse_mapping(dst_dfa->opt->alloc,
				reverse_mappings,
				m->dfastate, state)) {
				goto cleanup;
			}
		}
	}

#if LOG_DETERMINISE_CAPTURES
	fprintf(stderr, "#### reverse mapping for %zu states\n", src_nfa->statecount);
	for (i = 0; i < src_nfa->statecount; i++) {
		struct reverse_mapping *rm = &reverse_mappings[i];
		fprintf(stderr, "%lu:", i);
		for (j = 0; j < rm->count; j++) {
			fprintf(stderr, " %u", rm->list[j]);
		}
		fprintf(stderr, "\n");
	}
#else
	(void)j;
#endif

	if (!det_copy_capture_actions(reverse_mappings, dst_dfa, src_nfa)) {
		goto cleanup;
	}

	res = 1;
cleanup:
	for (i = 0; i < src_nfa->statecount; i++) {
		if (reverse_mappings[i].list != NULL) {
			f_free(dst_dfa->opt->alloc, reverse_mappings[i].list);
		}
	}
	f_free(dst_dfa->opt->alloc, reverse_mappings);

	return res;
}

/* Add DFA_state to the list for NFA_state. */
static int
add_reverse_mapping(const struct fsm_alloc *alloc,
    struct reverse_mapping *reverse_mappings,
    fsm_state_t dfa_state, fsm_state_t nfa_state)
{
	struct reverse_mapping *rm = &reverse_mappings[nfa_state];
	if (rm->count == rm->ceil) {
		const unsigned nceil = (rm->ceil ? 2*rm->ceil : 2);
		fsm_state_t *nlist = f_realloc(alloc,
		    rm->list, nceil * sizeof(rm->list));
		if (nlist == NULL) {
			return 0;
		}
		rm->list = nlist;
		rm->ceil = nceil;
	}

	rm->list[rm->count] = dfa_state;
	rm->count++;
	return 1;
}

static int
det_copy_capture_actions_cb(fsm_state_t state,
    enum capture_action_type type, unsigned capture_id, fsm_state_t to,
    void *opaque)
{
	struct reverse_mapping *rm_s;
	size_t s_i, t_i;
	struct det_copy_capture_actions_env *env = opaque;
	assert(env->tag == 'D');

#if LOG_DETERMINISE_CAPTURES
	fprintf(stderr, "det_copy_capture_actions_cb: state %u, type %s, ID %u, TO %d\n",
	    state, fsm_capture_action_type_name[type],
	    capture_id, to);
#endif

	rm_s = &env->reverse_mappings[state];

	for (s_i = 0; s_i < rm_s->count; s_i++) {
		const fsm_state_t s = rm_s->list[s_i];

		if (to == CAPTURE_NO_STATE) {
			if (!fsm_capture_add_action(env->dst,
				s, type, capture_id, CAPTURE_NO_STATE)) {
				env->ok = 0;
				return 0;
			}
		} else {
			struct reverse_mapping *rm_t = &env->reverse_mappings[to];
			for (t_i = 0; t_i < rm_t->count; t_i++) {
				const fsm_state_t t = rm_t->list[t_i];

				if (!fsm_capture_add_action(env->dst,
					s, type, capture_id, t)) {
					env->ok = 0;
					return 0;
				}
			}
		}
	}

	return 1;
}

static int
det_copy_capture_actions(struct reverse_mapping *reverse_mappings,
    struct fsm *dst, struct fsm *src)
{
	struct det_copy_capture_actions_env env = { 'D', NULL, NULL, 1 };
	env.dst = dst;
	env.reverse_mappings = reverse_mappings;

	fsm_capture_action_iter(src, det_copy_capture_actions_cb, &env);
	return env.ok;
}
