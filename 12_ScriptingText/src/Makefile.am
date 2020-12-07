CFLAGS += -Wall

if COND_GCOV
   CFLAGS += -fprofile-arcs -ftest-coverage -O0 -g
endif

lib_LTLIBRARIES = libbuf.la

buf_LDADD = libnamegen.la

gcov:
	gcov .libs/libbuf -t -j -k
