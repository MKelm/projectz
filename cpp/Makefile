# Makefile for project z editor
ARCH := $(shell uname -m)
GCC = g++
#CFLAGS = -Wall -ggdb -std=c++0x
CFLAGS =
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

editor : editor.o map.o main.o json/loader.o events.o screen.o screen/text.o ../jsmn/jsmn.o
	$(GCC) editor.o map.o main.o json/loader.o events.o screen.o screen/text.o ../jsmn/jsmn.o -o editor.$(ARCH) $(LDFLAGS)

game : game.o main.o map.o json/loader.o events.o screen.o screen/text.o ../jsmn/jsmn.o
	$(GCC) game.o main.o map.o json/loader.o events.o screen.o screen/text.o ../jsmn/jsmn.o -o game.$(ARCH) $(LDFLAGS)

map.o : map.cpp global.hpp map.hpp json/loader.hpp
	$(GCC) $(CFLAGS) -c map.cpp

json/loader.o : json/loader.cpp global.hpp json/loader.hpp
	$(GCC) $(CFLAGS) -c json/loader.cpp -o json/loader.o

events.o : events.cpp global.hpp events.hpp
	$(GCC) $(CFLAGS) -c events.cpp

editor.o : editor.cpp global.hpp main.hpp
	$(GCC) $(CFLAGS) -c editor.cpp

game.o : game.cpp global.hpp main.hpp
	$(GCC) $(CFLAGS) -c game.cpp

main.o : main.cpp global.hpp main.hpp screen.hpp
	$(GCC) $(CFLAGS) -c main.cpp

screen.o : screen.cpp global.hpp screen.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen.cpp

screen/text.o : screen/text.cpp global.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen/text.cpp -o screen/text.o

clean :
	$(RM) *.o
