/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Pc_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[8] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 8; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xef)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], '_')) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[4], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[5], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[4], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[6], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[7], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[4], s[3], 0xbf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[3], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[5], s[3], 0x94)) { goto error; }
	for (i = 0xb3; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[3], i)) { goto error; }
	}
	for (i = 0x8d; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[3], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[3], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

