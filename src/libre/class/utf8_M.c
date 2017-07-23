/* Generated by libfsm */

#include LF_HEADER

#include <stddef.h>

#include <fsm/fsm.h>

struct fsm *
utf8_M_fsm(const struct fsm_options *opt)
{
	struct fsm *fsm;
	size_t i;

	struct fsm_state *s[145] = { 0 };

	fsm = fsm_new(opt);
	if (fsm == NULL) {
		return NULL;
	}

	for (i = 0; i < 145; i++) {
		s[i] = fsm_addstate(fsm);
		if (s[i] == NULL) {
			goto error;
		}
	}

	if (!fsm_addedge_literal(fsm, s[0], s[1], 0xcc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[2], 0xcd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[3], 0xd2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[4], 0xd6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[5], 0xd7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[6], 0xd8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[7], 0xd9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[8], 0xdb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[9], 0xdc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[10], 0xdd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[11], 0xde)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[12], 0xdf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[13], 0xe0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[14], 0xe1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[15], 0xe2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[16], 0xe3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[17], 0xea)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[18], 0xef)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[19], 0xf0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[0], s[20], 0xf3)) { goto error; }
	for (i = 0x80; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[1], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[2], s[21], i)) { goto error; }
	}
	for (i = 0x83; i <= 0x89; i++) {
		if (!fsm_addedge_literal(fsm, s[3], s[21], i)) { goto error; }
	}
	for (i = 0x91; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[4], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[4], s[21], 0xbf)) { goto error; }
	for (i = 0x81; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[21], i)) { goto error; }
	}
	for (i = 0x84; i <= 0x85; i++) {
		if (!fsm_addedge_literal(fsm, s[5], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[5], s[21], 0x87)) { goto error; }
	for (i = 0x90; i <= 0x9a; i++) {
		if (!fsm_addedge_literal(fsm, s[6], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[7], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[7], s[21], 0xb0)) { goto error; }
	for (i = 0x96; i <= 0x9c; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[21], i)) { goto error; }
	}
	for (i = 0x9f; i <= 0xa4; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[21], i)) { goto error; }
	}
	for (i = 0xa7; i <= 0xa8; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[21], i)) { goto error; }
	}
	for (i = 0xaa; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[8], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[9], s[21], 0x91)) { goto error; }
	for (i = 0xb0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[9], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x8a; i++) {
		if (!fsm_addedge_literal(fsm, s[10], s[21], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xb0; i++) {
		if (!fsm_addedge_literal(fsm, s[11], s[21], i)) { goto error; }
	}
	for (i = 0xab; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[12], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[13], s[67], 0xa0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[68], 0xa1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[69], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[70], 0xa4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[71], 0xa5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[72], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[72], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[72], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[72], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[72], 0xb2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[73], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[74], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[75], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[76], 0xad)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[77], 0xae)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[78], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[79], 0xb0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[80], 0xb1)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[80], 0xb3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[81], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[82], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[83], 0xb6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[84], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[85], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[86], 0xb9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[87], 0xba)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[88], 0xbb)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[89], 0xbc)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[90], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[91], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[13], s[92], 0xbf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[46], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[47], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[48], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[49], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[50], 0x9c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[51], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[52], 0x9e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[53], 0x9f)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[54], 0xa0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[55], 0xa2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[56], 0xa4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[57], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[58], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[59], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[60], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[61], 0xad)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[62], 0xae)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[63], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[64], 0xb0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[65], 0xb3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[14], s[66], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[26], 0x83)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[27], 0xb3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[28], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[15], s[29], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[16], s[22], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[16], s[23], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[30], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[31], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[32], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[33], 0xa0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[34], 0xa2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[35], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[36], 0xa4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[37], 0xa5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[38], 0xa6)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[39], 0xa7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[40], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[41], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[42], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[43], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[17], s[44], 0xaf)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[24], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[18], s[25], 0xb8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[93], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[94], 0x91)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[95], 0x96)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[96], 0x9b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[97], 0x9d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[19], s[98], 0x9e)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[20], s[45], 0xa0)) { goto error; }
	for (i = 0xaa; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[22], s[21], i)) { goto error; }
	}
	for (i = 0x99; i <= 0x9a; i++) {
		if (!fsm_addedge_literal(fsm, s[23], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[24], s[21], 0x9e)) { goto error; }
	for (i = 0x80; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[25], s[21], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[25], s[21], i)) { goto error; }
	}
	for (i = 0x90; i <= 0xb0; i++) {
		if (!fsm_addedge_literal(fsm, s[26], s[21], i)) { goto error; }
	}
	for (i = 0xaf; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[27], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[28], s[21], 0xbf)) { goto error; }
	for (i = 0xa0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[29], s[21], i)) { goto error; }
	}
	for (i = 0xaf; i <= 0xb2; i++) {
		if (!fsm_addedge_literal(fsm, s[30], s[21], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[30], s[21], i)) { goto error; }
	}
	for (i = 0x9e; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[31], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[32], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[33], s[21], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[33], s[21], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[33], s[21], 0x8b)) { goto error; }
	for (i = 0xa3; i <= 0xa7; i++) {
		if (!fsm_addedge_literal(fsm, s[33], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x81; i++) {
		if (!fsm_addedge_literal(fsm, s[34], s[21], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[34], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x85; i++) {
		if (!fsm_addedge_literal(fsm, s[35], s[21], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[35], s[21], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[36], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x93; i++) {
		if (!fsm_addedge_literal(fsm, s[37], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[38], s[21], i)) { goto error; }
	}
	for (i = 0xb3; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[38], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[39], s[21], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[39], s[21], 0xa5)) { goto error; }
	for (i = 0xa9; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[40], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[41], s[21], 0x83)) { goto error; }
	for (i = 0x8c; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[41], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[41], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[42], s[21], 0xb0)) { goto error; }
	for (i = 0xb2; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[42], s[21], i)) { goto error; }
	}
	for (i = 0xb7; i <= 0xb8; i++) {
		if (!fsm_addedge_literal(fsm, s[42], s[21], i)) { goto error; }
	}
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[42], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[43], s[21], 0x81)) { goto error; }
	for (i = 0xab; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[43], s[21], i)) { goto error; }
	}
	for (i = 0xb5; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[43], s[21], i)) { goto error; }
	}
	for (i = 0xa3; i <= 0xaa; i++) {
		if (!fsm_addedge_literal(fsm, s[44], s[21], i)) { goto error; }
	}
	for (i = 0xac; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[44], s[21], i)) { goto error; }
	}
	for (i = 0x84; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[45], s[1], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[45], s[2], 0x87)) { goto error; }
	for (i = 0xab; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[46], s[21], i)) { goto error; }
	}
	for (i = 0x96; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[47], s[21], i)) { goto error; }
	}
	for (i = 0x9e; i <= 0xa0; i++) {
		if (!fsm_addedge_literal(fsm, s[47], s[21], i)) { goto error; }
	}
	for (i = 0xa2; i <= 0xa4; i++) {
		if (!fsm_addedge_literal(fsm, s[47], s[21], i)) { goto error; }
	}
	for (i = 0xa7; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[47], s[21], i)) { goto error; }
	}
	for (i = 0xb1; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[47], s[21], i)) { goto error; }
	}
	for (i = 0x82; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[48], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[48], s[21], 0x8f)) { goto error; }
	for (i = 0x9a; i <= 0x9d; i++) {
		if (!fsm_addedge_literal(fsm, s[48], s[21], i)) { goto error; }
	}
	for (i = 0x9d; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[49], s[21], i)) { goto error; }
	}
	for (i = 0x92; i <= 0x94; i++) {
		if (!fsm_addedge_literal(fsm, s[50], s[21], i)) { goto error; }
	}
	for (i = 0xb2; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[50], s[21], i)) { goto error; }
	}
	for (i = 0x92; i <= 0x93; i++) {
		if (!fsm_addedge_literal(fsm, s[51], s[21], i)) { goto error; }
	}
	for (i = 0xb2; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[51], s[21], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[52], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x93; i++) {
		if (!fsm_addedge_literal(fsm, s[53], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[53], s[21], 0x9d)) { goto error; }
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[54], s[21], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[55], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[55], s[21], 0xa9)) { goto error; }
	for (i = 0xa0; i <= 0xab; i++) {
		if (!fsm_addedge_literal(fsm, s[56], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xbb; i++) {
		if (!fsm_addedge_literal(fsm, s[56], s[21], i)) { goto error; }
	}
	for (i = 0x97; i <= 0x9b; i++) {
		if (!fsm_addedge_literal(fsm, s[57], s[21], i)) { goto error; }
	}
	for (i = 0x95; i <= 0x9e; i++) {
		if (!fsm_addedge_literal(fsm, s[58], s[21], i)) { goto error; }
	}
	for (i = 0xa0; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[58], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[58], s[21], 0xbf)) { goto error; }
	for (i = 0xb0; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[59], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[60], s[21], i)) { goto error; }
	}
	for (i = 0xb4; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[60], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[61], s[21], i)) { goto error; }
	}
	for (i = 0xab; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[61], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[62], s[21], i)) { goto error; }
	}
	for (i = 0xa1; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[62], s[21], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[63], s[21], i)) { goto error; }
	}
	for (i = 0xa4; i <= 0xb7; i++) {
		if (!fsm_addedge_literal(fsm, s[64], s[21], i)) { goto error; }
	}
	for (i = 0x90; i <= 0x92; i++) {
		if (!fsm_addedge_literal(fsm, s[65], s[21], i)) { goto error; }
	}
	for (i = 0x94; i <= 0xa8; i++) {
		if (!fsm_addedge_literal(fsm, s[65], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[65], s[21], 0xad)) { goto error; }
	for (i = 0xb2; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[65], s[21], i)) { goto error; }
	}
	for (i = 0xb7; i <= 0xb9; i++) {
		if (!fsm_addedge_literal(fsm, s[65], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xb9; i++) {
		if (!fsm_addedge_literal(fsm, s[66], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[66], s[21], i)) { goto error; }
	}
	for (i = 0x96; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[67], s[21], i)) { goto error; }
	}
	for (i = 0x9b; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[67], s[21], i)) { goto error; }
	}
	for (i = 0xa5; i <= 0xa7; i++) {
		if (!fsm_addedge_literal(fsm, s[67], s[21], i)) { goto error; }
	}
	for (i = 0xa9; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[67], s[21], i)) { goto error; }
	}
	for (i = 0x99; i <= 0x9b; i++) {
		if (!fsm_addedge_literal(fsm, s[68], s[21], i)) { goto error; }
	}
	for (i = 0x94; i <= 0xa1; i++) {
		if (!fsm_addedge_literal(fsm, s[69], s[21], i)) { goto error; }
	}
	for (i = 0xa3; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[69], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[70], s[21], i)) { goto error; }
	}
	for (i = 0xba; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[70], s[21], i)) { goto error; }
	}
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[70], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[71], s[21], i)) { goto error; }
	}
	for (i = 0x91; i <= 0x97; i++) {
		if (!fsm_addedge_literal(fsm, s[71], s[21], i)) { goto error; }
	}
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[71], s[21], i)) { goto error; }
	}
	for (i = 0x81; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[72], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[72], s[21], 0xbc)) { goto error; }
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[72], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[73], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[73], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[73], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[73], s[21], 0x97)) { goto error; }
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[73], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[74], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[74], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[74], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[74], s[21], 0x91)) { goto error; }
	for (i = 0xb0; i <= 0xb1; i++) {
		if (!fsm_addedge_literal(fsm, s[74], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[74], s[21], 0xb5)) { goto error; }
	for (i = 0x80; i <= 0x85; i++) {
		if (!fsm_addedge_literal(fsm, s[75], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x89; i++) {
		if (!fsm_addedge_literal(fsm, s[75], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[75], s[21], i)) { goto error; }
	}
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[75], s[21], i)) { goto error; }
	}
	for (i = 0xba; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[75], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[76], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[76], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[76], s[21], i)) { goto error; }
	}
	for (i = 0x96; i <= 0x97; i++) {
		if (!fsm_addedge_literal(fsm, s[76], s[21], i)) { goto error; }
	}
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[76], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[77], s[21], 0x82)) { goto error; }
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[77], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[78], s[21], i)) { goto error; }
	}
	for (i = 0x86; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[78], s[21], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[78], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[78], s[21], 0x97)) { goto error; }
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[79], s[21], i)) { goto error; }
	}
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[79], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[80], s[21], i)) { goto error; }
	}
	for (i = 0x86; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[80], s[21], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[80], s[21], i)) { goto error; }
	}
	for (i = 0x95; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[80], s[21], i)) { goto error; }
	}
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[80], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[81], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[81], s[21], i)) { goto error; }
	}
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[81], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[82], s[21], i)) { goto error; }
	}
	for (i = 0x86; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[82], s[21], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[82], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[82], s[21], 0x97)) { goto error; }
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[82], s[21], i)) { goto error; }
	}
	for (i = 0x82; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[83], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[84], s[21], 0x8a)) { goto error; }
	for (i = 0x8f; i <= 0x94; i++) {
		if (!fsm_addedge_literal(fsm, s[84], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[84], s[21], 0x96)) { goto error; }
	for (i = 0x98; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[84], s[21], i)) { goto error; }
	}
	for (i = 0xb2; i <= 0xb3; i++) {
		if (!fsm_addedge_literal(fsm, s[84], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[85], s[21], 0xb1)) { goto error; }
	for (i = 0xb4; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[85], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x8e; i++) {
		if (!fsm_addedge_literal(fsm, s[86], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[87], s[21], 0xb1)) { goto error; }
	for (i = 0xb4; i <= 0xb9; i++) {
		if (!fsm_addedge_literal(fsm, s[87], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[87], s[21], i)) { goto error; }
	}
	for (i = 0x88; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[88], s[21], i)) { goto error; }
	}
	for (i = 0x98; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[89], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[89], s[21], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[89], s[21], 0xb7)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[89], s[21], 0xb9)) { goto error; }
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[89], s[21], i)) { goto error; }
	}
	for (i = 0xb1; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[90], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[91], s[21], i)) { goto error; }
	}
	for (i = 0x86; i <= 0x87; i++) {
		if (!fsm_addedge_literal(fsm, s[91], s[21], i)) { goto error; }
	}
	for (i = 0x8d; i <= 0x97; i++) {
		if (!fsm_addedge_literal(fsm, s[91], s[21], i)) { goto error; }
	}
	for (i = 0x99; i <= 0xbc; i++) {
		if (!fsm_addedge_literal(fsm, s[91], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[92], s[21], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[93], s[100], 0x87)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[93], s[101], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[93], s[102], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[93], s[103], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[93], s[104], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[118], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[119], 0x81)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[120], 0x82)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[121], 0x84)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[122], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[123], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[124], 0x87)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[125], 0x88)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[126], 0x8b)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[127], 0x8c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[128], 0x8d)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[129], 0x90)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[130], 0x91)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[131], 0x92)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[131], 0x98)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[132], 0x93)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[133], 0x96)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[134], 0x97)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[135], 0x99)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[136], 0x9a)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[137], 0x9c)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[138], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[139], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[140], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[141], 0xb0)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[142], 0xb2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[143], 0xb4)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[94], s[144], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[95], s[108], 0xab)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[95], s[109], 0xac)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[95], s[110], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[95], s[111], 0xbe)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[96], s[99], 0xb2)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[112], 0x85)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[113], 0x86)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[114], 0x89)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[115], 0xa8)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[116], 0xa9)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[97], s[117], 0xaa)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[98], s[105], 0x80)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[98], s[106], 0xa3)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[98], s[107], 0xa5)) { goto error; }
	for (i = 0x9d; i <= 0x9e; i++) {
		if (!fsm_addedge_literal(fsm, s[99], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[100], s[21], 0xbd)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[101], s[21], 0xa0)) { goto error; }
	for (i = 0xb6; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[102], s[21], i)) { goto error; }
	}
	for (i = 0x81; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[103], s[21], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[103], s[21], i)) { goto error; }
	}
	for (i = 0x8c; i <= 0x8f; i++) {
		if (!fsm_addedge_literal(fsm, s[103], s[21], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[103], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[103], s[21], 0xbf)) { goto error; }
	for (i = 0xa5; i <= 0xa6; i++) {
		if (!fsm_addedge_literal(fsm, s[104], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[105], s[21], i)) { goto error; }
	}
	for (i = 0x88; i <= 0x98; i++) {
		if (!fsm_addedge_literal(fsm, s[105], s[21], i)) { goto error; }
	}
	for (i = 0x9b; i <= 0xa1; i++) {
		if (!fsm_addedge_literal(fsm, s[105], s[21], i)) { goto error; }
	}
	for (i = 0xa3; i <= 0xa4; i++) {
		if (!fsm_addedge_literal(fsm, s[105], s[21], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xaa; i++) {
		if (!fsm_addedge_literal(fsm, s[105], s[21], i)) { goto error; }
	}
	for (i = 0x90; i <= 0x96; i++) {
		if (!fsm_addedge_literal(fsm, s[106], s[21], i)) { goto error; }
	}
	for (i = 0x84; i <= 0x8a; i++) {
		if (!fsm_addedge_literal(fsm, s[107], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[108], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[109], s[21], i)) { goto error; }
	}
	for (i = 0x91; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[110], s[21], i)) { goto error; }
	}
	for (i = 0x8f; i <= 0x92; i++) {
		if (!fsm_addedge_literal(fsm, s[111], s[21], i)) { goto error; }
	}
	for (i = 0xa5; i <= 0xa9; i++) {
		if (!fsm_addedge_literal(fsm, s[112], s[21], i)) { goto error; }
	}
	for (i = 0xad; i <= 0xb2; i++) {
		if (!fsm_addedge_literal(fsm, s[112], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[112], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[113], s[21], i)) { goto error; }
	}
	for (i = 0x85; i <= 0x8b; i++) {
		if (!fsm_addedge_literal(fsm, s[113], s[21], i)) { goto error; }
	}
	for (i = 0xaa; i <= 0xad; i++) {
		if (!fsm_addedge_literal(fsm, s[113], s[21], i)) { goto error; }
	}
	for (i = 0x82; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[114], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[115], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[115], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0xac; i++) {
		if (!fsm_addedge_literal(fsm, s[116], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[116], s[21], 0xb5)) { goto error; }
	if (!fsm_addedge_literal(fsm, s[117], s[21], 0x84)) { goto error; }
	for (i = 0x9b; i <= 0x9f; i++) {
		if (!fsm_addedge_literal(fsm, s[117], s[21], i)) { goto error; }
	}
	for (i = 0xa1; i <= 0xaf; i++) {
		if (!fsm_addedge_literal(fsm, s[117], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[118], s[21], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[118], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[119], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[119], s[21], 0xbf)) { goto error; }
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[120], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xba; i++) {
		if (!fsm_addedge_literal(fsm, s[120], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[121], s[21], i)) { goto error; }
	}
	for (i = 0xa7; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[121], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[122], s[21], 0xb3)) { goto error; }
	for (i = 0x80; i <= 0x82; i++) {
		if (!fsm_addedge_literal(fsm, s[123], s[21], i)) { goto error; }
	}
	for (i = 0xb3; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[123], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[124], s[21], 0x80)) { goto error; }
	for (i = 0x8a; i <= 0x8c; i++) {
		if (!fsm_addedge_literal(fsm, s[124], s[21], i)) { goto error; }
	}
	for (i = 0xac; i <= 0xb7; i++) {
		if (!fsm_addedge_literal(fsm, s[125], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[125], s[21], 0xbe)) { goto error; }
	for (i = 0x9f; i <= 0xaa; i++) {
		if (!fsm_addedge_literal(fsm, s[126], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[127], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[127], s[21], 0xbc)) { goto error; }
	for (i = 0xbe; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[127], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x84; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	for (i = 0x87; i <= 0x88; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	for (i = 0x8b; i <= 0x8d; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[128], s[21], 0x97)) { goto error; }
	for (i = 0xa2; i <= 0xa3; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	for (i = 0xa6; i <= 0xac; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xb4; i++) {
		if (!fsm_addedge_literal(fsm, s[128], s[21], i)) { goto error; }
	}
	for (i = 0xb5; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[129], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x86; i++) {
		if (!fsm_addedge_literal(fsm, s[130], s[21], i)) { goto error; }
	}
	for (i = 0xb0; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[131], s[21], i)) { goto error; }
	}
	for (i = 0x80; i <= 0x83; i++) {
		if (!fsm_addedge_literal(fsm, s[132], s[21], i)) { goto error; }
	}
	for (i = 0xaf; i <= 0xb5; i++) {
		if (!fsm_addedge_literal(fsm, s[133], s[21], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[133], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[134], s[21], 0x80)) { goto error; }
	for (i = 0x9c; i <= 0x9d; i++) {
		if (!fsm_addedge_literal(fsm, s[134], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[135], s[21], 0x80)) { goto error; }
	for (i = 0xab; i <= 0xb7; i++) {
		if (!fsm_addedge_literal(fsm, s[136], s[21], i)) { goto error; }
	}
	for (i = 0x9d; i <= 0xab; i++) {
		if (!fsm_addedge_literal(fsm, s[137], s[21], i)) { goto error; }
	}
	for (i = 0x81; i <= 0x8a; i++) {
		if (!fsm_addedge_literal(fsm, s[138], s[21], i)) { goto error; }
	}
	for (i = 0xb3; i <= 0xb9; i++) {
		if (!fsm_addedge_literal(fsm, s[138], s[21], i)) { goto error; }
	}
	for (i = 0xbb; i <= 0xbe; i++) {
		if (!fsm_addedge_literal(fsm, s[138], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[139], s[21], 0x87)) { goto error; }
	for (i = 0x91; i <= 0x9b; i++) {
		if (!fsm_addedge_literal(fsm, s[139], s[21], i)) { goto error; }
	}
	for (i = 0x8a; i <= 0x99; i++) {
		if (!fsm_addedge_literal(fsm, s[140], s[21], i)) { goto error; }
	}
	for (i = 0xaf; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[141], s[21], i)) { goto error; }
	}
	for (i = 0xb8; i <= 0xbf; i++) {
		if (!fsm_addedge_literal(fsm, s[141], s[21], i)) { goto error; }
	}
	for (i = 0x92; i <= 0xa7; i++) {
		if (!fsm_addedge_literal(fsm, s[142], s[21], i)) { goto error; }
	}
	for (i = 0xa9; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[142], s[21], i)) { goto error; }
	}
	for (i = 0xb1; i <= 0xb6; i++) {
		if (!fsm_addedge_literal(fsm, s[143], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[143], s[21], 0xba)) { goto error; }
	for (i = 0xbc; i <= 0xbd; i++) {
		if (!fsm_addedge_literal(fsm, s[143], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[143], s[21], 0xbf)) { goto error; }
	for (i = 0x80; i <= 0x85; i++) {
		if (!fsm_addedge_literal(fsm, s[144], s[21], i)) { goto error; }
	}
	if (!fsm_addedge_literal(fsm, s[144], s[21], 0x87)) { goto error; }

	fsm_setstart(fsm, s[0]);
	fsm_setend(fsm, s[21], 1);

	return fsm;

error:

	fsm_free(fsm);

	return NULL;
}

