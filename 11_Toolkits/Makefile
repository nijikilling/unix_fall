all: main

main: main.c
	gcc -o main main.c -g `pkg-config --cflags --libs glib-2.0` 

clean:
	rm *.o main
