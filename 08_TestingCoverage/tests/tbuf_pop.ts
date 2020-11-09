#include "buf.h"
#define _TEST(a, b) ck_assert_msg(b, a);

#test tbuf_pop
    /* buf_pop() */
    float *a = 0;
    buf_push(a, 1.1);
    buf_push(a, 1.2);
    buf_push(a, 1.3);
    buf_push(a, 1.4);
    _TEST("size 4", buf_size(a) == 4);
    _TEST("pop 3", buf_pop(a) == (float)1.4f);
    buf_trunc(a, 3);
    _TEST("size 3", buf_size(a) == 3);
    _TEST("pop 2", buf_pop(a) == (float)1.3f);
    _TEST("pop 1", buf_pop(a) == (float)1.2f);
    _TEST("pop 0", buf_pop(a) == (float)1.1f);
    _TEST("size 0 (pop)", buf_size(a) == 0);

