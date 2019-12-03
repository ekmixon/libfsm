/*
 * Copyright 2008-2017 Katherine Flavel
 *
 * See LICENCE for the full copyright terms.
 */

#define _POSIX_C_SOURCE 2

#include <unistd.h>

#include <assert.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdint.h> /* XXX: for ast.h */
#include <stdio.h>
#include <ctype.h>

#include <fsm/fsm.h>
#include <fsm/bool.h>
#include <fsm/pred.h>
#include <fsm/print.h>
#include <fsm/options.h>
#include <fsm/vm.h>

#include <re/re.h>

#include "libfsm/internal.h" /* XXX */
#include "libre/print.h" /* XXX */
#include "libre/class.h" /* XXX */
#include "libre/ast.h" /* XXX */


#define DEBUG_ESCAPES     0
#define DEBUG_VM_FSM      0
#define DEBUG_TEST_REGEXP 0

/*
 * TODO: accepting a delimiter would be useful: /abc/. perhaps provide that as
 * a convenience function, especially wrt. escaping for lexing. Also convenient
 * for specifying flags: /abc/g
 * TODO: flags; -r for RE_REVERSE, etc
 */

struct match {
	int i;
	const char *s;
	struct match *next;
};

static struct fsm_options opt;

static void
usage(void)
{
	fprintf(stderr, "usage: re    [-r <dialect>] [-nbiusyz] [-x] <re> ... [ <text> | -- <text> ... ]\n");
	fprintf(stderr, "       re    [-r <dialect>] [-nbiusyz] {-q <query>} <re> ...\n");
	fprintf(stderr, "       re -p [-r <dialect>] [-nbiusyz] [-l <language>] [-acwX] [-k <io>] [-e <prefix>] <re> ...\n");
	fprintf(stderr, "       re -m [-r <dialect>] [-nbiusyz] <re> ...\n");
	fprintf(stderr, "       re -h\n");
}

static enum fsm_io
io(const char *name)
{
	size_t i;

	struct {
		const char *name;
		enum fsm_io io;
	} a[] = {
		{ "getc", FSM_IO_GETC },
		{ "str",  FSM_IO_STR  },
		{ "pair", FSM_IO_PAIR }
	};

	assert(name != NULL);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, name)) {
			return a[i].io;
		}
	}

	fprintf(stderr, "unrecognised IO API; valid IO APIs are: ");

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "%s%s",
			a[i].name,
			i + 1 < sizeof a / sizeof *a ? ", " : "\n");
	}

	exit(EXIT_FAILURE);
}

static void
print_name(const char *name,
	fsm_print **print_fsm, ast_print **print_ast)
{
	size_t i;

	struct {
		const char *name;
		fsm_print *print_fsm;
		ast_print *print_ast;
	} a[] = {
		{ "api",    fsm_print_api,    NULL  },
		{ "c",      fsm_print_c,      NULL  },
		{ "dot",    fsm_print_dot,    NULL  },
		{ "fsm",    fsm_print_fsm,    NULL  },
		{ "ir",     fsm_print_ir,     NULL  },
		{ "irjson", fsm_print_irjson, NULL  },
		{ "json",   fsm_print_json,   NULL  },

		{ "tree",   NULL, ast_print_tree },
		{ "abnf",   NULL, ast_print_abnf },
		{ "ast",    NULL, ast_print_dot  },
		{ "pcre",   NULL, ast_print_pcre }
	};

	assert(name != NULL);
	assert(print_fsm != NULL);
	assert(print_ast != NULL);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, name)) {
			*print_fsm = a[i].print_fsm;
			*print_ast = a[i].print_ast;
			return;
		}
	}

	fprintf(stderr, "unrecognised output language; valid languages are: ");

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "%s%s",
			a[i].name,
			i + 1 < sizeof a / sizeof *a ? ", " : "\n");
	}

	exit(EXIT_FAILURE);
}

static enum re_dialect
dialect_name(const char *name)
{
	size_t i;

	struct {
		const char *name;
		enum re_dialect dialect;
	} a[] = {
/* TODO:
		{ "ere",     RE_ERE     },
		{ "bre",     RE_BRE     },
		{ "plan9",   RE_PLAN9   },
		{ "js",      RE_JS      },
		{ "python",  RE_PYTHON  },
		{ "sql99",   RE_SQL99   },
*/
		{ "like",    RE_LIKE    },
		{ "literal", RE_LITERAL },
		{ "glob",    RE_GLOB    },
		{ "native",  RE_NATIVE  },
		{ "pcre",    RE_PCRE    },
		{ "sql",     RE_SQL     }
	};

	assert(name != NULL);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, name)) {
			return a[i].dialect;
		}
	}

	fprintf(stderr, "unrecognised regexp dialect \"%s\"; valid dialects are: ", name);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "%s%s",
			a[i].name,
			i + 1 < sizeof a / sizeof *a ? ", " : "\n");
	}

	exit(EXIT_FAILURE);
}

static int
(*comparison(const char *name))
(const struct fsm *, const struct fsm *)
{
	size_t i;

	struct {
		const char *name;
		int (*comparison)(const struct fsm *, const struct fsm *);
	} a[] = {
		{ "equal",    fsm_equal },
		{ "isequal",  fsm_equal },
		{ "areequal", fsm_equal }
	};

	assert(name != NULL);

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		if (0 == strcmp(a[i].name, name)) {
			return a[i].comparison;
		}
	}

	fprintf(stderr, "unrecognised comparison; valid comparisons are: ");

	for (i = 0; i < sizeof a / sizeof *a; i++) {
		fprintf(stderr, "%s%s",
			a[i].name,
			i + 1 < sizeof a / sizeof *a ? ", " : "\n");
	}

	exit(EXIT_FAILURE);
}

static void *
xmalloc(size_t n)
{
	void *p = malloc(n);
	if (p == NULL) {
		perror("xmalloc");
		exit(EXIT_FAILURE);
	}

	return p;
}

static FILE *
xopen(const char *s)
{
	FILE *f;

	assert(s != NULL);

	if (0 == strcmp(s, "-")) {
		return stdin;
	}

	f = fopen(s, "r");
	if (f == NULL) {
		perror(s);
		exit(EXIT_FAILURE);
	}

	return f;
}

static struct match *
addmatch(struct match **head, int i, const char *s)
{
	struct match *new;

	assert(head != NULL);
	assert(s != NULL);

	if ((1U << i) > INT_MAX) {
		fprintf(stderr, "Too many patterns for int bitmap\n");
		exit(EXIT_FAILURE);
	}

	/* TODO: explain we find duplicate; return success */
	/*
	 * This is a purposefully shallow comparison (rather than calling strcmp)
	 * so that 're xyz xyz' will find the ambiguity.
	 */
	{
		struct match *p;

		for (p = *head; p != NULL; p = p->next) {
			if (p->s == s) {
				return p;
			}
		}
	}

	new = malloc(sizeof *new);
	if (new == NULL) {
		return NULL;
	}

	new->i = i;
	new->s = s;

	new->next = *head;
	*head     = new;

	return new;
}

static void
carryopaque(struct fsm *src_fsm, const fsm_state_t *src_set, size_t n,
	struct fsm *dst_fsm, fsm_state_t dst_state)
{
	struct match *matches;
	struct match *m;
	size_t i;

	assert(src_fsm != NULL);
	assert(src_set != NULL);
	assert(n > 0);
	assert(dst_fsm != NULL);
	assert(fsm_isend(dst_fsm, dst_state));
	assert(fsm_getopaque(dst_fsm, dst_state) == NULL);

	/*
	 * Here we mark newly-created DFA states with the same regexp string
	 * as from their corresponding source NFA states.
	 *
	 * Because all the accepting states are reachable together, they
	 * should all share the same regexp, unless re(1) was invoked with
	 * a regexp which is a subset of (or equal to) another.
	 */

	matches = NULL;

	for (i = 0; i < n; i++) {
		/*
		 * The opaque data is attached to end states only, so we skip
		 * non-end states here.
		 */
		if (!fsm_isend(src_fsm, src_set[i])) {
			continue;
		}

		assert(fsm_getopaque(src_fsm, src_set[i]) != NULL);

		for (m = fsm_getopaque(src_fsm, src_set[i]); m != NULL; m = m->next) {
			if (!addmatch(&matches, m->i, m->s)) {
				perror("addmatch");
				goto error;
			}
		}
	}

	fsm_setopaque(dst_fsm, dst_state, matches);

	return;

error:

	/* XXX: free matches */

	fsm_setopaque(dst_fsm, dst_state, NULL);

	return;
}

static void
printexample(FILE *f, const struct fsm *fsm, fsm_state_t state)
{
	char buf[256]; /* TODO */
	int n;

	assert(f != NULL);
	assert(fsm != NULL);

	n = fsm_example(fsm, state, buf, sizeof buf);
	if (-1 == n) {
		perror("fsm_example");
		exit(EXIT_FAILURE);
	}

	/* TODO: escape hex etc */
	fprintf(f, "%s%s", buf,
		n >= (int) sizeof buf - 1 ? "..." : "");
}

static int
endleaf_c(FILE *f, const void *state_opaque, const void *endleaf_opaque)
{
	const struct match *m;
	int n;

	assert(state_opaque != NULL);
	assert(endleaf_opaque == NULL);

	(void) f;
	(void) endleaf_opaque;

	n = 0;

	for (m = state_opaque; m != NULL; m = m->next) {
		n |= 1 << m->i;
	}

	fprintf(f, "return %#x;", (unsigned) n);

	fprintf(f, " /* ");

	for (m = state_opaque; m != NULL; m = m->next) {
		fprintf(f, "\"%s\"", m->s); /* XXX: escape string (and comment) */

		if (m->next != NULL) {
			fprintf(f, ", ");
		}
	}

	fprintf(f, " */");

	return 0;
}

static int
endleaf_dot(FILE *f, const void *state_opaque, const void *endleaf_opaque)
{
	const struct match *m;

	assert(f != NULL);
	assert(state_opaque != NULL);
	assert(endleaf_opaque == NULL);

	(void) endleaf_opaque;

	fprintf(f, "label = <");

	for (m = state_opaque; m != NULL; m = m->next) {
		fprintf(f, "#%u", m->i);

		if (m->next != NULL) {
			fprintf(f, ",");
		}
	}

	fprintf(f, ">");

	/* TODO: only if comments */
	/* TODO: centralise to libfsm/print/dot.c */

#if 0
	fprintf(f, " # ");

	for (m = state_opaque; m != NULL; m = m->next) {
		fprintf(f, "\"%s\"", m->s); /* XXX: escape string (and comment) */

		if (m->next != NULL) {
			fprintf(f, ", ");
		}
	}

	fprintf(f, "\n");
#endif

	return 0;
}

enum parse_escape_result {
	PARSE_OK = 0,
	PARSE_INVALID_ESCAPE,
	PARSE_INCOMPLETE_ESCAPE
};

static int
parse_escapes(char *s, char **errpos, int *lenp)
{
	int i,j,st;
	unsigned char ccode;
	int hexcurly, ndig;

	enum { ST_BARE, ST_ESC, ST_OCT, ST_HEX, ST_HEX_DIGIT };

	ccode = 0;
	hexcurly = 0;

	st = ST_BARE;
	for (i=0, j=0; s[i] != '\0'; i++) {
#if DEBUG_ESCAPES
		fprintf(stderr, "%3d | st=%d hexcurly=%d ndig=%d ccode=0x%02x | %2d %c\n",
			i, st, hexcurly, ndig, (unsigned int)ccode, s[i], 
			isprint(s[i]) ? s[i] : ' ');
#endif /* DEBUG_ESCAPES */

		if (s[i] == '\0') {
			break;
		}

		switch (st) {
		case ST_BARE:
bare:
			if (s[i] == '\\') {
				st = ST_ESC;
			} else {
				s[j++] = s[i];
			}
			break;

		case ST_ESC:
			switch (s[i]) {
			case 'a':  s[j++] = '\a'; st = ST_BARE; break;
			case 'b':  s[j++] = '\b'; st = ST_BARE; break;
			case 'e':  s[j++] = '\033'; st = ST_BARE; break;
			case 'f':  s[j++] = '\f'; st = ST_BARE; break;
			case 'n':  s[j++] = '\n'; st = ST_BARE; break;
			case 'r':  s[j++] = '\r'; st = ST_BARE; break;
			case 't':  s[j++] = '\t'; st = ST_BARE; break;
			case 'v':  s[j++] = '\v'; st = ST_BARE; break;
			case '"':  s[j++] = '\"'; st = ST_BARE; break;
			case '\\': s[j++] = '\\'; st = ST_BARE; break;

			case '0': case '1': case '2': case '3':
			case '4': case '5': case '6': case '7':
				   ccode = 0; ndig = 0; st = ST_OCT; goto octdig;
			case 'x': ccode = 0; ndig = 0; hexcurly = 0; st = ST_HEX; break;

			default:
				if (errpos) {
					*errpos = &s[i];
					return PARSE_INVALID_ESCAPE;
				}
				break;
			}
			break;

		case ST_OCT:
octdig:
			if (ndig < 3 && s[i] >= '0' && s[i] <= '7') {
				ccode = (ccode * 8) + (s[i] - '0');
				ndig++;
			} else {
				s[j++] = ccode;
				st = ST_BARE;
				goto bare;
			}

			break;

		case ST_HEX:
			st = ST_HEX_DIGIT;
			if (s[i] != '{') {
				hexcurly = 0;
				goto hexdigit;
			}

			hexcurly = 1;
			break;

		case ST_HEX_DIGIT:
hexdigit:
			{
				unsigned char uc = toupper(s[i]);
				if (ndig < 2 && isxdigit(uc)) {
					if (uc >= '0' && uc <= '9') {
						ccode = (ccode * 16) + (uc - '0');
					} else {
						ccode = (ccode * 16) + (uc - 'A' + 10);
					}

					ndig++;
				} else {
					s[j++] = ccode;
					st = ST_BARE;

					if (!hexcurly) {
						goto bare;
					} else if (uc != '}') {
						if (errpos) {
							*errpos = &s[i];
						}
						return PARSE_INCOMPLETE_ESCAPE;
					}
				}
			}
			break;
		}
	}

	switch (st) {
	case ST_BARE:
		break;

	case ST_ESC:
		if (errpos) {
			*errpos = &s[i];
		}
		return PARSE_INVALID_ESCAPE;

	case ST_HEX:
	case ST_OCT:
	case ST_HEX_DIGIT:
		if (hexcurly && st == ST_HEX_DIGIT) {
			if (errpos) {
				*errpos = &s[i];
			}
			return PARSE_INCOMPLETE_ESCAPE;
		}

		s[j++] = ccode;
		break;
	}

	s[j] = '\0';

	*lenp = j;

	return PARSE_OK;
}

/* test file format:
 *
 * 1. lines starting with '#' are skipped
 * 2. (TODO) lines starting with 'R' set the dialect
 * 3. records are separated by empty lines
 * 4. the first line of each record is the regular expression to be
 *    tested 
 * 5. after the regular expression, valid lines start with '#', '+', or '-'
 *     a. '+' indicates that the rest of the line should be matched with the
 *        current regular expression
 *     b. '-' indicates the the rest of the line should *not* be matched with
 *        the current regular expression
 *     c. '#' lines are comments
 */
static int
process_test_file(const char *fname, enum re_dialect dialect, int max_errors)
{
	char buf[4096];
	char cpy[sizeof buf];
	char *s;
	FILE *f;
	int num_re_errors, num_errors;
	int num_regexps, num_test_cases;
	int linenum;

	char *regexp;
	struct fsm_dfavm *vm;

	regexp = NULL;
	vm     = NULL;

	/* XXX - fix this */
	opt.comments = 0;

	f = xopen(fname);

	num_regexps    = 0;
	num_re_errors  = 0;
	num_test_cases = 0;
	num_errors     = 0;

	linenum        = 0;

	while (s = fgets(buf, sizeof buf, f), s != NULL) {
		int len;

		linenum++;
		len = strlen(s);
		if (len > 0 & s[len-1] == '\n') {
			s[--len] = '\0';
		}

		if (len == 0) {
			free(regexp);
			regexp = NULL;

			fsm_vm_free(vm);
			vm = NULL;

			continue;
		}

		if (s[0] == '#') {
			continue;
		}

		if (regexp == NULL) {
			static const struct re_err err_zero;

			struct fsm *fsm;
			struct re_err err;
			enum re_flags flags;
			char *re_str;

			assert(vm == NULL);
			assert(s  != NULL);

			regexp = xmalloc(len+1);
			memcpy(regexp, s, len+1);

			assert(strlen(regexp) == (size_t)len);
			assert(strcmp(regexp,s) == 0);

			flags = 0;
			err   = err_zero;

			num_regexps++;

			re_str = regexp;
			fsm = re_comp(dialect, fsm_sgetc, &re_str, &opt, flags, &err);
			if (fsm == NULL) {
				fprintf(stderr, "line %d: error with regexp /%s/: %s\n",
					linenum, regexp, re_strerror(err.e));

				/* don't exit; instead we leave vm==NULL so we
				 * skip to next regexp ... */

				num_re_errors++;
				continue;
			}

			/* XXX - minimize or determinize? */
			if (!fsm_determinise(fsm)) {
				fprintf(stderr, "line %d: error determinising /%s/: %s\n", linenum, regexp, strerror(errno));

				/* don't exit; instead we leave vm==NULL so we
				 * skip to next regexp ... */

				num_re_errors++;
				continue;
			}

#if DEBUG_VM_FSM
			fprintf(stderr, "FSM:\n");
			fsm_print_fsm(stderr, fsm);
			fprintf(stderr, "---\n");
			{
				FILE *f = fopen("dump.fsm", "w");
				fsm_print_fsm(f, fsm);
				fclose(f);
			}
#endif /* DEBUG_VM_FSM */

#if DEBUG_TEST_REGEXP
			fprintf(stderr, "REGEXP matching for /%s/\n", regexp);
#endif /* DEBUG_TEST_REGEXP */
			vm = fsm_vm_compile(fsm);
			if (vm == NULL) {
				fprintf(stderr, "line %d: error compiling /%s/: %s\n", linenum, regexp, strerror(errno));

				/* don't exit; instead we leave vm==NULL so we
				 * skip to next regexp ... */

				num_re_errors++;
				continue;
			}

			fsm_free(fsm);
		} else if (vm != NULL) {
			int matching;
			char *orig;
			char *test;
			char *err;
			int tlen;
			int ret;

			if (s[0] != '-' && s[0] != '+') {
				fprintf(stderr, "line %d: unrecognized record type '%c': %s\n", linenum, s[0], s);
				num_errors++;
				continue;
			}

			num_test_cases++;

			matching = (s[0] == '+');
			orig = &s[1];
			test = strcpy(cpy, orig);
			tlen = len-1;

			err = NULL;
			ret = parse_escapes(test, &err, &tlen);
			if (ret != PARSE_OK) {
				fprintf(stderr, "line %d: invalid/incomplete escape sequence at column %zd\n",
					linenum, err - test);
				num_errors++;
				continue;
			}

			ret = fsm_vm_match_buffer(vm, test, tlen);
			if (!!ret == !!matching) {
				printf("[OK    ] line %d: regexp /%s/ %s \"%s\"\n",
					linenum, regexp, matching ? "matched" : "did not match", orig);
			} else {
				printf("[NOT OK] line %d: regexp /%s/ expected to %s \"%s\", but %s\n",
					linenum, regexp,
					matching ? "match" : "not match",
					orig,
					ret ? "did" : "did not");
				num_errors++;

				if (max_errors > 0 && num_errors >= max_errors) {
					fprintf(stderr, "too many errors\n");
					goto finish;
				}
			}
		}
	}

	free(regexp);

	if (vm) {
		fsm_vm_free(vm);
		vm = NULL;
	}

	fclose(f);

	if (ferror(f)) {
		fprintf(stderr, "line %d: error reading %s: %s\n", linenum, fname, strerror(errno));
		if (regexp != NULL) {
			num_errors++;
		}
	}

finish:
	printf("%s: %d regexps, %d test cases\n", fname, num_regexps, num_test_cases);
	printf("%s: %d re errors, %d errors\n", fname, num_re_errors, num_errors);

	if (max_errors > 0 && num_errors >= max_errors) {
		exit(EXIT_FAILURE);
	}

	return (num_errors > 0);
}

int
main(int argc, char *argv[])
{
	struct fsm *(*join)(struct fsm *, struct fsm *);
	int (*query)(const struct fsm *, const struct fsm *);
	fsm_print *print_fsm;
	ast_print *print_ast;
	enum re_dialect dialect;
	struct fsm *fsm;
	enum re_flags flags;
	int xfiles, yfiles, tfiles;
	int example;
	int keep_nfa;
	int patterns;
	int ambig;
	int makevm;
	int max_test_errors;

	struct fsm_dfavm *vm;

	/* note these defaults are the opposite than for fsm(1) */
	opt.anonymous_states  = 1;
	opt.consolidate_edges = 1;

	opt.comments          = 1;
	opt.io                = FSM_IO_GETC;

	flags     = 0U;
	xfiles    = 0;
	yfiles    = 0;
	tfiles    = 0;
	example   = 0;
	keep_nfa  = 0;
	patterns  = 0;
	ambig     = 0;
	makevm    = 0;
	print_fsm = NULL;
	print_ast = NULL;
	query     = NULL;
	join      = fsm_union;
	dialect   = RE_NATIVE;
	vm        = NULL;

	max_test_errors = 0;

	{
		int c;

		while (c = getopt(argc, argv, "h" "acwXe:E:k:" "bi" "sq:r:l:" "upMmntxyz"), c != -1) {
			switch (c) {
			case 'a': opt.anonymous_states  = 0;          break;
			case 'c': opt.consolidate_edges = 0;          break;
			case 'w': opt.fragment          = 1;          break;
			case 'X': opt.always_hex        = 1;          break;
			case 'e': opt.prefix            = optarg;     break;
			case 'k': opt.io                = io(optarg); break;

			case 'b': flags |= RE_ANCHORED; break;
			case 'i': flags |= RE_ICASE;    break;

			case 's':
				join = fsm_concat;
				break;

			case 'l':
				print_name(optarg, &print_fsm, &print_ast);
				break;

			case 'p': print_fsm = fsm_print_fsm;        break;
			case 'q': query     = comparison(optarg);   break;
			case 'r': dialect   = dialect_name(optarg); break;

			case 't': tfiles   = 1; break;
			case 'E':
				max_test_errors = strtoul(optarg, NULL, 10);
				/* XXX: error handling */
				break;

			case 'u': ambig    = 1; break;
			case 'x': xfiles   = 1; break;
			case 'y': yfiles   = 1; break;
			case 'm': example  = 1; break;
			case 'n': keep_nfa = 1; break;
			case 'z': patterns = 1; break;
			case 'M': makevm   = 1; break;

			case 'h':
				usage();
				return EXIT_SUCCESS;

			case '?':
			default:
				usage();
				return EXIT_FAILURE;
			}
		}

		argc -= optind;
		argv += optind;
	}

	if (argc < 1) {
		usage();
		return EXIT_FAILURE;
	}

	if (tfiles) {
		if (!!print_fsm || !!print_ast || example || !!query || keep_nfa) {
			fprintf(stderr, "-t is not compatible with -m, -n, -p, or -q\n");
			return EXIT_FAILURE;
		}

		if (xfiles || yfiles) {
			fprintf(stderr, "-t is not compatible with -x or -y\n");
			return EXIT_FAILURE;
		}
	}

	if (!!print_fsm + !!print_ast + example + !!query > 1) {
		fprintf(stderr, "-m, -p and -q are mutually exclusive\n");
		return EXIT_FAILURE;
	}

	if (!!print_fsm + !!print_ast + example + !!query && xfiles) {
		fprintf(stderr, "-x applies only when executing\n");
		return EXIT_FAILURE;
	}

	if (makevm && (keep_nfa || example || query)) {
		fprintf(stderr, "-M cannot be used with -m, -q, or -n\n");
		return EXIT_FAILURE;
	}

	if (patterns && !!query) {
		fprintf(stderr, "-z does not apply for querying\n");
		return EXIT_FAILURE;
	}

	if (join == fsm_concat && patterns) {
		fprintf(stderr, "-s is not implemented when printing patterns by -z\n");
		return EXIT_FAILURE;
	}

	if (print_fsm == NULL) {
		keep_nfa = 0;
	}

	if (keep_nfa) {
		ambig = 1;
	}

	/* XXX: repetitive */
	if (print_ast != NULL) {
		struct ast *ast;
		struct re_err err;

		if (argc != 1) {
			fprintf(stderr, "single regexp only for this output format\n");
			return EXIT_FAILURE;
		}

		if (yfiles) {
			FILE *f;

			f = xopen(argv[0]);

			ast = re_parse(dialect, fsm_fgetc, f, &opt, flags, &err, NULL);

			fclose(f);
		} else {
			const char *s;

			s = argv[0];

			ast = re_parse(dialect, fsm_sgetc, &s, &opt, flags, &err, NULL);
		}

		if (ast == NULL) {
			re_perror(dialect, &err,
				 yfiles ? argv[0] : NULL,
				!yfiles ? argv[0] : NULL);

			if (err.e == RE_EXUNSUPPORTD) {
				return 2;
			}

			return EXIT_FAILURE;
		}

		print_ast(stdout, &opt, ast);

		return 0;
	}

	flags |= RE_MULTI;

	if (tfiles) {
		int r, i;

		r = 0;

		if (argc == 0) {
			fprintf(stderr, "-t requires at least one test file\n");
			return EXIT_FAILURE;
		}

		for (i = 0; i < argc; i++) {
			int succ;

			succ = process_test_file(argv[i], dialect, max_test_errors);

			if (!succ) {
				r |= 1;
				continue;
			}
		}

		return r;
	}


	fsm = fsm_new(&opt);
	if (fsm == NULL) {
		perror("fsm_new");
		return EXIT_FAILURE;
	}

	{
		int i;

		for (i = 0; i < argc - !(print_fsm || example || !!query || argc <= 1); i++) {
			struct re_err err;
			struct fsm *new, *q;

			/* TODO: handle possible "dialect:" prefix */

			if (0 == strcmp(argv[i], "--")) {
				argc--;
				argv++;

				break;
			}

			if (yfiles) {
				FILE *f;

				f = xopen(argv[i]);

				new = re_comp(dialect, fsm_fgetc, f, &opt, flags, &err);

				fclose(f);
			} else {
				const char *s;

				s = argv[i];

				new = re_comp(dialect, fsm_sgetc, &s, &opt, flags, &err);
			}

			if (new == NULL) {
				re_perror(dialect, &err,
					 yfiles ? argv[i] : NULL,
					!yfiles ? argv[i] : NULL);

				if (err.e == RE_EXUNSUPPORTD) {
					return 2;
				}

				return EXIT_FAILURE;
			}

			if (!keep_nfa) {
				if (!fsm_minimise(new)) {
					perror("fsm_minimise");
					return EXIT_FAILURE;
				}
			}

			{
				size_t s;

				/*
				 * Attach this mapping to each end state for this regexp.
				 * XXX: we should share the same matches struct for all end states
				 * in the same regexp, and keep an argc-sized array of pointers to free().
				 * XXX: then use fsm_setendopaque() here.
				 */
				for (s = 0; s < new->statecount; s++) {
					if (fsm_isend(new, s)) {
						struct match *matches;

						matches = NULL;

						if (!addmatch(&matches, i, argv[i])) {
							perror("addmatch");
							return EXIT_FAILURE;
						}

						assert(fsm_getopaque(new, s) == NULL);
						fsm_setopaque(new, s, matches);
					}
				}
			}

			/* TODO: implement concatenating patterns for -s in conjunction with -z.
			 * Note that depends on the regexp dialect */

			if (query != NULL) {
				q = fsm_clone(new);
				if (q == NULL) {
					perror("fsm_clone");
					return EXIT_FAILURE;
				}
			}

			fsm = join(fsm, new);
			if (fsm == NULL) {
				perror("fsm_union/concat");
				return EXIT_FAILURE;
			}

			if (query != NULL) {
				int r;

				r = query(fsm, q);
				if (r == -1) {
					perror("query");
					return EXIT_FAILURE;
				}

				if (r == 0) {
					return EXIT_FAILURE;
				}

				fsm_free(q);
			}
		}

		argc -= i;
		argv += i;
	}

	if (query) {
		return EXIT_SUCCESS;
	}

	if ((print_fsm || example) && argc > 0) {
		fprintf(stderr, "too many arguments\n");
		return EXIT_FAILURE;
	}

	if (!ambig) {
		struct fsm *dfa;
		size_t s;

		dfa = fsm_clone(fsm);
		if (dfa == NULL) {
			perror("fsm_clone");
			return EXIT_FAILURE;
		}

		{
			opt.carryopaque = carryopaque;

			if (!fsm_determinise(dfa)) {
				perror("fsm_determinise");
				return EXIT_FAILURE;
			}

			opt.carryopaque = NULL;
		}

		for (s = 0; s < dfa->statecount; s++) {
			const struct match *matches;

			if (!fsm_isend(dfa, s)) {
				continue;
			}

			matches = fsm_getopaque(dfa, s);
			assert(matches != NULL);

			if (matches->next != NULL) {
				const struct match *m;

				/* TODO: // delimeters depend on dialect */
				/* TODO: would deal with dialect: prefix here, too */

				fprintf(stderr, "ambiguous matches for ");
				for (m = matches; m != NULL; m = m->next) {
					/* TODO: print nicely */
					fprintf(stderr, "/%s/", m->s);
					if (m->next != NULL) {
						fprintf(stderr, ", ");
					}
				}

				fprintf(stderr, "; for example on input '");
				printexample(stderr, dfa, s);
				fprintf(stderr, "'\n");

				/* TODO: consider different error codes */
				return EXIT_FAILURE;
			}
		}

		/* TODO: free opaques */

		fsm_free(dfa);
	}

	if (!keep_nfa) {
		opt.carryopaque = carryopaque;

		/*
		 * Minimise only when we don't need to keep the end state information
		 * separated per regexp. Otherwise, convert to a DFA.
		 */
		if (!patterns && !example && print_fsm != fsm_print_c) {
			if (!fsm_minimise(fsm)) {
				perror("fsm_minimise");
				return EXIT_FAILURE;
			}
		} else {
			if (!fsm_determinise(fsm)) {
				perror("fsm_determinise");
				return EXIT_FAILURE;
			}
		}

		opt.carryopaque = NULL;

		if (makevm) {
			vm = fsm_vm_compile(fsm);
		}
	}

	if (example) {
		fsm_state_t s;

		for (s = 0; s < fsm->statecount; s++) {
			if (!fsm_isend(fsm, s)) {
				continue;
			}

			/* TODO: would deal with dialect: prefix here, too */
			if (patterns) {
				const struct match *m;

				assert(fsm_getopaque(fsm, s) != NULL);

				for (m = fsm_getopaque(fsm, s); m != NULL; m = m->next) {
					/* TODO: print nicely */
					printf("/%s/", m->s);
					if (m->next != NULL) {
						printf(", ");
					}
				}

				printf(": ");
			}

			printexample(stdout, fsm, s);
			printf("\n");
		}

/* XXX: free fsm */

		return 0;
	}

	if (print_fsm != NULL) {
		/* TODO: print examples in comments for end states;
		 * patterns in comments for the whole FSM */

		if (print_fsm == fsm_print_c) {
			opt.endleaf = endleaf_c;
		} else if (print_fsm == fsm_print_dot) {
			opt.endleaf = patterns ? endleaf_dot : NULL;
		}

		print_fsm(stdout, fsm);

/* XXX: free fsm */
		
		if (vm != NULL) {
			fsm_vm_free(vm);
		}

		return 0;
	}

	/* execute */
	{
		int r;

		r = 0;

		if (argc > 0) {
			int i;

			/* TODO: option to print input texts which match. like grep(1) does.
			 * This is not the same as printing patterns which match (by associating
			 * a pattern to the end state), like lx(1) does */

			for (i = 0; i < argc; i++) {
				fsm_state_t state;
				int e;

				if (xfiles) {
					FILE *f;

					f = xopen(argv[i]);

					if (vm != NULL) {
						e = fsm_vm_match_file(vm, f);
					} else {
						e = fsm_exec(fsm, fsm_fgetc, f, &state);
					}

					fclose(f);
				} else {
					const char *s;

					s = argv[i];

					if (vm != NULL) {
						e = fsm_vm_match_buffer(vm, s, strlen(s));
					} else {
						e = fsm_exec(fsm, fsm_sgetc, &s, &state);
					}
				}

				if (e != 1) {
					r |= 1;
					continue;
				}

				if (patterns) {
					const struct match *m;

					assert(fsm_getopaque(fsm, state) != NULL);

					for (m = fsm_getopaque(fsm, state); m != NULL; m = m->next) {
						/* TODO: print nicely */
						printf("match: /%s/\n", m->s);
					}
				}
			}
		}

		/* XXX: free opaques */

		fsm_free(fsm);

		if (vm != NULL) {
			fsm_vm_free(vm);
		}

		return r;
	}
}

