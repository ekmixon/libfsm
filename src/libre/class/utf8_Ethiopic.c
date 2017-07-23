/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_Ethiopic_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[15] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 15; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xea)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[8], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[9], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[10], 0x8a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[11], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[12], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[13], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[1], s[14], 0x8e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[6], 0xb6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[2], s[7], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[3], s[4], 0xac)) { goto error; }
	for (i = 0x81; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0x89; i <= 0x8e; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0x91; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xa6; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0xa8; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[5], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xa6; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[5], i)) { goto error; }
	}
	for (i = 0xa8; i <= 0xae; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[5], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[5], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x88; i <= 0x8e; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x90; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x98; i <= 0x9e; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[5], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[5], i)) { goto error; }
	}
	for (i = 0x90; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[9], s[5], 0x98)) { goto error; }
	for (i = 0x9a; i <= 0x9d; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[5], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[5], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[5], i)) { goto error; }
	}
	for (i = 0x90; i <= 0xb0; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[5], i)) { goto error; }
	}
	for (i = 0xb2; i <= 0xb5; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[5], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[5], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[11], s[5], 0x80)) { goto error; }
	for (i = 0x82; i <= 0x85; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[5], i)) { goto error; }
	}
	for (i = 0x88; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[5], i)) { goto error; }
	}
	for (i = 0x98; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x90; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[5], i)) { goto error; }
	}
	for (i = 0x92; i <= 0x95; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[5], i)) { goto error; }
	}
	for (i = 0x98; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x9a; i++) {
		if (!fsm_addedge_literal(fsm, s[13], s[5], i)) { goto error; }
	}
	for (i = 0x9d; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[13], s[5], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[14], s[5], i)) { goto error; }
	}

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[5], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

