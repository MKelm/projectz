# Makefile for project z mvc
ARCH := $(shell uname -m)
GCC = g++
#CFLAGS = -Wall -ggdb -std=c++0x
CFLAGS = -std=c++0x
LDFLAGS = -lSDL -lSDL_image -lSDL_gfx -lSDL_ttf

porjectz : porjectz.o models.o controllers.o views.o
	$(GCC) projectz.o models.o controllers.o views.o -o projectz.$(ARCH) $(LDFLAGS)

porjectz.o : projectz.cpp global.hpp models.hpp views.hpp controllers.hpp
	$(GCC) $(CFLAGS) -c projectz.cpp

models.o : models.cpp global.hpp models.hpp
	$(GCC) $(CFLAGS) -c models.cpp

controllers.o : controllers.cpp global.hpp models.hpp views.hpp controllers.hpp
	$(GCC) $(CFLAGS) -c controllers.cpp

views.o : views.cpp global.hpp views.hpp
	$(GCC) $(CFLAGS) -c views.cpp

clean :
	$(RM) *.o
	$(RM) models/*.o
	$(RM) controllers/*.o
	$(RM) views/*.o
