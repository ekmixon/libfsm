/* Generated by lx */

#ifndef LX_H
#define LX_H

enum lx_pcre_token {
	TOK_NEWLINE,
	TOK_WHITESPACE,
	TOK_MAYBE_COMMENT,
	TOK_COUNT,
	TOK_SEP,
	TOK_CLOSECOUNT,
	TOK_OPENCOUNT,
	TOK_CHAR,
	TOK_RANGE,
	TOK_CLOSEGROUPRANGE,
	TOK_CLOSEGROUP,
	TOK_OPENGROUPINVCB,
	TOK_OPENGROUPCB,
	TOK_OPENGROUPINV,
	TOK_OPENGROUP,
	TOK_FLAG__IGNORE,
	TOK_FLAG__EXTENDED,
	TOK_FLAG__SINGLE,
	TOK_FLAG__INSENSITIVE,
	TOK_FLAG__UNKNOWN,
	TOK_NEGATE,
	TOK_SUB,
	TOK_FLAGS,
	TOK_INVALID__COMMENT,
	TOK_INVALID,
	TOK_NOESC,
	TOK_HEX,
	TOK_OCT,
	TOK_EOL,
	TOK_NAMED__CLASS,
	TOK_CONTROL,
	TOK_ESC,
	TOK_ALT,
	TOK_ANY,
	TOK_PLUS,
	TOK_STAR,
	TOK_OPT,
	TOK_UNSUPPORTED,
	TOK_END,
	TOK_START,
	TOK_OPENCAPTURE,
	TOK_CLOSE,
	TOK_OPEN,
	TOK_EOF,
	TOK_ERROR,
	TOK_UNKNOWN
};

/*
 * .byte is 0-based.
 * .line, .col, and .saved_col are 1-based; 0 means unknown.
 */
struct lx_pos {
	unsigned byte;
	unsigned line;
	unsigned col;
	unsigned saved_col;
};

struct lx_pcre_lx {
	int (*lgetc)(struct lx_pcre_lx *lx);
	void *getc_opaque;

	int c; /* lx_pcre_ungetc buffer */

	struct lx_pos start;
	struct lx_pos end;

	void *buf_opaque;
	int  (*push) (void *buf_opaque, char c);
	int  (*clear)(void *buf_opaque);
	void (*free) (void *buf_opaque);

	enum lx_pcre_token (*z)(struct lx_pcre_lx *lx);
};

/*
 * The initial buffer size; this ought to be over the typical token length,
 * so as to avoid a run-up of lots of resizing.
 */
#ifndef LX_DYN_LOW
#define LX_DYN_LOW 1 << 10
#endif

/*
 * High watermark; if the buffer grows over this, it will resize back down
 * by LX_DYN_FACTOR when no longer in use.
 */
#ifndef LX_DYN_HIGH
#define LX_DYN_HIGH 1 << 13
#endif

/*
 * Andrew Koenig said the growth factor should be less than phi, (1 + sqrt(5)) / 2
 * P.J. Plauger said 1.5 works well in practice. (Perhaps because of internal
 * bookkeeping data stored by the allocator.)
 *
 * Non-integer factors here add the constraint that LX_DYN_LOW > 1 because
 * because conversion to size_t truncates, and e.g. 1 * 1.5 == 1 is no good
 * as the requirement is to *increase* a buffer.
 */
#ifndef LX_DYN_FACTOR
#define LX_DYN_FACTOR 2
#endif

/* dynamic token buffer */
struct lx_dynbuf {
	char *p;
	size_t len;
	char *a;
};

const char *lx_pcre_name(enum lx_pcre_token t);
const char *lx_pcre_example(enum lx_pcre_token (*z)(struct lx_pcre_lx *), enum lx_pcre_token t);

void lx_pcre_init(struct lx_pcre_lx *lx);
enum lx_pcre_token lx_pcre_next(struct lx_pcre_lx *lx);

int  lx_pcre_dynpush(void *buf_opaque, char c);
int  lx_pcre_dynclear(void *buf_opaque);
void lx_pcre_dynfree(void *buf_opaque);

#endif

