#
#	Assignment 8 - Makefile
#	Student Number: 3020946
#	Name: Lucas Martin-Tully
#	Purpose: make the files associated with the entire assignment
#

FLTK_CONFIG=/usr/local/opt/fltk/bin/fltk-config
INCLUDE=-I/usr/local/include
LIBS=-L/usr/local/lib
CFLAGS=-std=c++11 -Wall ${INCLUDE} `${FLTK_CONFIG} --cxxflags` -O2
LINK=${LIBS} `${FLTK_CONFIG} --ldflags --use-images`
LOCALLIBS=libraries/
override CFLAGS += -g -O0

all: assignment8 project-start

project-start: project-start.o Window.o Graph.o GUI.o line_window.o
	g++ $^ $(LINK) -o project-start

assignment8: assignment8.o Window.o Graph.o GUI.o Simple_window.o demographics.o
	g++ $^ $(LINK) -o assignment8

assignment8.o: assignment8.cpp Simple_window.h ${LOCALLIBS}Window.h ${LOCALLIBS}GUI.h ${LOCALLIBS}Point.h ${LOCALLIBS}demographics.h
	g++ $(CFLAGS) -c assignment8.cpp -o assignment8.o

project-start.o: project-start.cpp ${LOCALLIBS}Window.h ${LOCALLIBS}GUI.h ${LOCALLIBS}Graph.h ${LOCALLIBS}line_window.h
	g++ $(CFLAGS) -c project-start.cpp

Simple_window.o: Simple_window.cpp Simple_window.h ${LOCALLIBS}GUI.h ${LOCALLIBS}Window.h ${LOCALLIBS}Point.h
	g++ $(CFLAGS) -c Simple_window.cpp -o Simple_window.o

Window.o: ${LOCALLIBS}Window.cpp ${LOCALLIBS}Window.h ${LOCALLIBS}Point.h
	g++ $(CFLAGS) -c ${LOCALLIBS}Window.cpp -o Window.o

Graph.o: ${LOCALLIBS}Graph.cpp ${LOCALLIBS}Graph.h ${LOCALLIBS}GUI.cpp ${LOCALLIBS}GUI.h ${LOCALLIBS}Window.h ${LOCALLIBS}Point.h 
	g++ $(CFLAGS) -c ${LOCALLIBS}Graph.cpp -o Graph.o

GUI.o: ${LOCALLIBS}GUI.cpp ${LOCALLIBS}GUI.h ${LOCALLIBS}Window.h ${LOCALLIBS}Point.h
	g++ $(CFLAGS) -c ${LOCALLIBS}GUI.cpp -o GUI.o

demographics.o: ${LOCALLIBS}demographics.cpp ${LOCALLIBS}demographics.h
	g++ $(CFLAGS) -c ${LOCALLIBS}demographics.cpp -o demographics.o

line_window.o: ${LOCALLIBS}line_window.h ${LOCALLIBS}line_window.cpp Simple_window.h ${LOCALLIBS}GUI.h ${LOCALLIBS}Window.h ${LOCALLIBS}Graph.h ${LOCALLIBS}Point.h
	g++ $(CFLAGS) -c ${LOCALLIBS}line_window.cpp -o line_window.o

clean:
	rm *.o assignment8 project-start;