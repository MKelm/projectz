# Makefile for project z
ARCH := $(shell uname -m)
CC = gcc
CFLAGS = -Wall -ggdb
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

editor : editor.o map.o tiles.o tlist.o tlloader.o jsmn/jsmn.o
	$(CC) editor.o map.o tiles.o tlist.o tlloader.o jsmn/jsmn.o -o editor.$(ARCH) $(LDFLAGS)

editor.o : editor.c global.h map.h tlist.h
	$(CC) $(CFLAGS) -c editor.c

map.o : map.c global.h map.h tiles.h
	$(CC) $(CFLAGS) -c map.c

tiles.o : tiles.c global.h tiles.h
	$(CC) $(CFLAGS) -c tiles.c

tlist.o : tlist.c global.h tlist.h tlloader.h
	$(CC) $(CFLAGS) -c tlist.c

tlloader.o : tlloader.c global.h tlloader.h tlist.h jsmn/jsmn.h
	$(CC) $(CFLAGS) -c tlloader.c

clean :
	$(RM) *.o
