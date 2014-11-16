# Makefile for project z editor
ARCH := $(shell uname -m)
GCC = g++
CFLAGS = -Wall -ggdb -std=c++0x
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

editor : main.o editor.o screen.o screen/text.o ../jsmn/jsmn.o
	$(GCC) main.o editor.o screen.o screen/text.o ../jsmn/jsmn.o -o editor.$(ARCH) $(LDFLAGS)

editor.o : editor.cpp global.hpp main.hpp
	$(GCC) $(CFLAGS) -c editor.cpp

main.o : main.cpp global.hpp main.hpp screen.hpp
	$(GCC) $(CFLAGS) -c main.cpp

screen.o : screen.cpp global.hpp screen.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen.cpp

screen/text.o : screen/text.cpp global.hpp screen/text.hpp
	$(GCC) $(CFLAGS) -c screen/text.cpp -o screen/text.o

clean :
	$(RM) *.o
