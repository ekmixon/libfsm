/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Batak_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[4] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 4; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[2], 0xaf)) { goto error; }
	for (i = 0x80; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[3], i)) { goto error; }
	}
	for (i = 0xbc; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[3], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[3], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

