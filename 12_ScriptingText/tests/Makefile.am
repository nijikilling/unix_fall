TESTS = tbuf_init tbuf_clear tbuf_pop tbuf_push tbuf_grow_trunc
check_PROGRAMS = tbuf_init tbuf_clear tbuf_pop tbuf_push tbuf_grow_trunc

CFLAGS = -I$(top_builddir)/src @CHECK_CFLAGS@
LDADD = $(top_builddir)/src/libbuf.la @CHECK_LIBS@

.ts.c:
	checkmk $< > $@
