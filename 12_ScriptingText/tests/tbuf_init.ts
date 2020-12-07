#include "buf.h"
#define _TEST(a, b) ck_assert_msg(b, a);

#test tbuf_init
    /* initialization, buf_free() */
    float *a = 0;
    _TEST("capacity init", buf_capacity(a) == 0);
    _TEST("size init", buf_size(a) == 0);
    buf_push(a, 1.3f);
    _TEST("size 1", buf_size(a) == 1);
    _TEST("value", a[0] == (float)1.3f);
    buf_clear(a);
    _TEST("clear", buf_size(a) == 0);
    _TEST("clear not-free", a != 0);
    buf_free(a);
    _TEST("free", a == 0);


