#
#
#	Assignment 8 - Makefile
#	Student Number: 3020946
#	Name: Lucas Martin-Tully
#	Purpose: 
#

FLTK_CONFIG=/usr/local/opt/fltk/bin/fltk-config
INCLUDE=-I/usr/local/include
LIBS=-L/usr/local/lib
CFLAGS=-std=c++11 -Wall ${INCLUDE} `${FLTK_CONFIG} --cxxflags` -O2
LINK=${LIBS} `${FLTK_CONFIG} --ldflags --use-images`
LOCALLIBS=fltk-stuff/
override CFLAGS += -g -O0

all: assignment8 project-start

project-start: project-start.o Window.o Graph.o GUI.o line_window.o
	g++ $^ $(LINK) -o project-start

assignment8: assignment8.o Window.o Graph.o GUI.o Simple_window.o demographics.o
	g++ $^ $(LINK) -o assignment8

assignment8.o: assignment8.cpp Simple_window.h fltk-stuff/Window.h fltk-stuff/GUI.h fltk-stuff/Point.h demographics.h
	g++ $(CFLAGS) -c assignment8.cpp -o assignment8.o

project-start.o: project-start.cpp libraries/Window.h libraries/GUI.h libraries/Graph.h line_window.h
	g++ $(CFLAGS) -c project-start.cpp

Simple_window.o: Simple_window.cpp Simple_window.h fltk-stuff/GUI.h fltk-stuff/Window.h fltk-stuff/Point.h
	g++ $(CFLAGS) -c Simple_window.cpp -o Simple_window.o

Window.o: fltk-stuff/Window.cpp fltk-stuff/Window.h fltk-stuff/Point.h
	g++ $(CFLAGS) -c fltk-stuff/Window.cpp -o Window.o

Graph.o: fltk-stuff/Graph.cpp fltk-stuff/Graph.h fltk-stuff/GUI.cpp fltk-stuff/GUI.h fltk-stuff/Window.h fltk-stuff/Point.h 
	g++ $(CFLAGS) -c libraries/Graph.cpp -o Graph.o

GUI.o: fltk-stuff/GUI.cpp fltk-stuff/GUI.h fltk-stuff/Window.h fltk-stuff/Point.h
	g++ $(CFLAGS) -c fltk-stuff/GUI.cpp -o GUI.o

demographics.o: demographics.cpp demographics.h
	g++ $(CFLAGS) -c demographics.cpp -o demographics.o

line_window.o: line_window.h line_window.cpp Simple_window.h fltk-stuff/GUI.h fltk-stuff/Window.h fltk-stuff/Graph.h fltk-stuff/Point.h
	g++ $(CFLAGS) -c line_window.cpp -o line_window.o

clean:
	rm *.o assignment8; rm -r *.dSYM;