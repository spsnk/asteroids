all: main

gfx:	gfx.c gfx.h
	gcc -c gfx.c -o obj/gfx.o
anim:	anim.cpp
	g++ -c anim.cpp -o obj/anim.o
ex:	gfx anim
	g++ -o build/ex obj/anim.o obj/gfx.o -lX11
asteroids:  asteroids.cpp
	g++ -c asteroids.cpp -o obj/asteroids.o
main: gfx asteroids
	g++ -o build/asteroids obj/gfx.o obj/asteroids.o -lX11
clean:
	rm -f *.o *~ ex main
	rm -f build/* obj/*
