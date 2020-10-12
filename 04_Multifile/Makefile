GENERATES = prog prog-a prog-so README *.a *.so
TRASH = *.o *~ o.* *.out
%.o:    %.c
	cc $< -c -fPIC -o $@

all:    README libs bins test

libs: liboutput_static.a liboutput.so

bins: prog prog-a prog-so

prog:   const.o fun.o prog.o
	cc $^ -o $@

prog-a:   prog.o liboutput_static.a
	cc $^ -o $@

prog-so:   prog.o liboutput.so
	cc $^ -o $@

README: prog
	./$< 2> $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

test: test1 test2 test3 

test1: bins
	./prog > $@1.out 2>/dev/null
	./prog-a > $@2.out 2>/dev/null
	LD_LIBRARY_PATH=. ./prog-so > $@3.out 2>/dev/null
	cmp $@1.out $@2.out
	cmp $@1.out $@3.out

test2: bins
	./prog 1 > $@1.out 2>/dev/null
	./prog-a 1 > $@2.out 2>/dev/null
	LD_LIBRARY_PATH=. ./prog-so 1 > $@3.out 2>/dev/null
	cmp $@1.out $@2.out
	cmp $@1.out $@3.out

test3: bins
	./prog 1 3 4 > $@1.out 2>/dev/null
	./prog-a 1 3 4 > $@2.out 2>/dev/null
	LD_LIBRARY_PATH=. ./prog-so 1 3 4 > $@3.out 2>/dev/null
	cmp $@1.out $@2.out
	cmp $@1.out $@3.out

clean:
	rm -f $(TRASH)

distclean:      clean
	rm -rf $(GENERATES)
