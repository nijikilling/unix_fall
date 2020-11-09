#include "buf.h"
#define _TEST(a, b) ck_assert_msg(b, a);

#test tbuf_push
    /* buf_push(), [] operator */
    long *ai = 0;
    for (int i = 0; i < 10000; i++)
        buf_push(ai, i);
    _TEST("size 10000", buf_size(ai) == 10000);
    int match = 0;
    for (int i = 0; i < (int)(buf_size(ai)); i++)
        match += ai[i] == i;
    _TEST("match 10000", match == 10000);
    buf_free(ai);
