# Makefile for project z editor
ARCH := $(shell uname -m)
GCC = g++
#CFLAGS = -Wall -ggdb -std=c++0x
CFLAGS = -std=c++0x
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

editor : editor.o map.o main.o lists.o json.o event/handler.o screen/list.o surface.o screen.o screen/text.o screen/map.o jsmn/jsmn.o
	$(GCC) editor.o map.o main.o lists.o json.o event/handler.o screen/list.o surface.o screen.o screen/text.o screen/map.o jsmn/jsmn.o -o editor.$(ARCH) $(LDFLAGS)

game : game.o main.o map.o lists.o json.o event/handler.o screen/list.o surface.o screen.o screen/text.o screen/map.o jsmn/jsmn.o
	$(GCC) game.o main.o map.o lists.o json.o event/handler.o screen/list.o surface.o screen.o screen/text.o screen/map.o jsmn/jsmn.o -o game.$(ARCH) $(LDFLAGS)

map.o : map.cpp global.hpp map.hpp json.hpp
	$(GCC) $(CFLAGS) -c map.cpp

json.o : json.cpp global.hpp jsmn/jsmn.h json.hpp
	$(GCC) $(CFLAGS) -c json.cpp

event/handler.o : event/handler.cpp global.hpp event/handler.hpp
	$(GCC) $(CFLAGS) -c event/handler.cpp -o event/handler.o

lists.o : lists.cpp global.hpp lists.hpp
	$(GCC) $(CFLAGS) -c lists.cpp

editor.o : editor.cpp global.hpp main.hpp
	$(GCC) $(CFLAGS) -c editor.cpp

game.o : game.cpp global.hpp main.hpp
	$(GCC) $(CFLAGS) -c game.cpp

main.o : main.cpp global.hpp main.hpp screen.hpp lists.hpp screen/map.hpp event/handler.hpp
	$(GCC) $(CFLAGS) -c main.cpp

screen.o : screen.cpp global.hpp surface.hpp screen.hpp screen/text.hpp screen/map.hpp screen/list.hpp
	$(GCC) $(CFLAGS) -c screen.cpp

surface.o : surface.cpp global.hpp surface.hpp
	$(GCC) $(CFLAGS) -c surface.cpp

screen/map.o : screen/map.cpp global.hpp screen.hpp screen/map.hpp
	$(GCC) $(CFLAGS) -c screen/map.cpp -o screen/map.o

screen/text.o : screen/text.cpp global.hpp surface.hpp map.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen/text.cpp -o screen/text.o

screen/list.o : screen/list.cpp global.hpp surface.hpp screen/list.hpp
	$(GCC) $(CFLAGS) -c screen/list.cpp -o screen/list.o

clean :
	$(RM) *.o
	$(RM) screen/*.o
	$(RM) event/*.o
