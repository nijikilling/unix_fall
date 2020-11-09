#include "buf.h"
#define _TEST(a, b) ck_assert_msg(b, a);

#test tbuf_grow_trunc
    /* buf_grow(), buf_trunc() */
    long *ai = 0;
    buf_grow(ai, 1000);
    _TEST("grow 1000", buf_capacity(ai) == 1000);
    _TEST("size 0 (grow)", buf_size(ai) == 0);
    buf_trunc(ai, 100);
    _TEST("trunc 100", buf_capacity(ai) == 100);
    buf_free(ai);
