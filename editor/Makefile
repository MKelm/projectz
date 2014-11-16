# Makefile for project z editor
ARCH := $(shell uname -m)
GCC = g++
CFLAGS = -Wall -ggdb
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

editor : editor.o screen.o screen/text.o ../jsmn/jsmn.o
	$(GCC) editor.o screen.o screen/text.o ../jsmn/jsmn.o -o editor.$(ARCH) $(LDFLAGS)

editor.o : editor.cpp global.hpp screen.hpp
	$(GCC) $(CFLAGS) -c editor.cpp

screen.o : screen.cpp global.hpp screen.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen.cpp

screen/text.o : screen/text.cpp global.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen/text.cpp -o screen/text.o

clean :
	$(RM) *.o
