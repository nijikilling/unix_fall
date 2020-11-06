.PHONY: all clean test test_one test_two

all: lib.o test

lib.o: lib.c
	g++ -shared -o lib.o -fPIC lib.c

test: test_one test_two

test_one: lib.o
	echo "\n==TEST 1 START=="
	echo "FIX" > t1.txt
	echo "Lol" > t2.txt
	rm t1.txt
	rm t2.txt
	echo "==TEST 1 SUCCEEDED==\n"

test_two: lib.o
	echo "FIX" > t1.txt
	echo "Lol" > t2.txt
	LD_PRELOAD=./lib.o echo "\n==TEST 2.0 START==";LD_PRELOAD=./lib.o rm t1.txt && exit 1 || (echo "rm failed with $$? as expected";exit 0)
	echo "\n==TEST 2.1 START=="
	LD_PRELOAD=./lib.o rm t2.txt
	echo "==TEST SUCCEEDED==\n"
clean:
	rm *.txt *.o

