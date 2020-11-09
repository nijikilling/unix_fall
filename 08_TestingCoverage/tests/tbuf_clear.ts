#include "buf.h"
#define _TEST(a, b) ck_assert_msg(b, a);

#test tbuf_clear
    /* Clearing an NULL pointer is a no-op */
    float *a = 0;
    buf_clear(a);
    _TEST("clear empty", buf_size(a) == 0);
    _TEST("clear no-op", a == 0);
