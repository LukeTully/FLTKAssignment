# Note you should add MSYS to your path.  For example you might add
# C:\MinGW\msys\1.0\bin\ 
# to your path for an MinGW installation on C: drive.  You may have to
# re-run mingw-get-setup.exe to add Msys if it wasn't installed.  
#
# For compiling on your own Windows or Mac machine at home, if you
# have compiled and installed your own version of the fltk libraries
# uncomment the following five lines. (Otherwise comment them out with
# #s)
FLTK_CONFIG=/usr/local/opt/fltk/bin/fltk-config
INCLUDE=-I /usr/local/include
LIBS=-L /usr/local/lib
CFLAGS=-std=c++11 -Wall ${INCLUDE} `${FLTK_CONFIG} --cxxflags` -O2
LINK=${LIBS} `${FLTK_CONFIG} --ldflags --use-images`
override CFLAGS += -g -O0
# For compiling on 2L14 computers, with the fltk libraries and header
# file directory in the directory with this makefile and your code,
# uncomment the following four lines (otherwise uncomment previous set
# of five lines and comment these four with #s)
#INCLUDE=-I.
#LIBS=-L.
#CFLAGS=${INCLUDE} -std=gnu++11 -Wall -mwindows -DWIN32 -DUSE_OPENGL32 -D_LARGEFILE_SOURCE -D_LAREFILE64_SOURCE -mconsole
#LINK=${LIBS} -mwindows -lfltk_images -lfltk_png -lfltk_z -lfltk_jpeg -lfltk -lole32 -luuid -lcomctl32 -mconsole

all: fltkTest ch12drill

ch12drill: ch12drill.o Window.o Graph.o GUI.o Simple_window.o
	g++ $^ $(LINK) -o ch12drill

ch12drill.o: ch12drill.cpp Simple_window.h Window.h GUI.h Point.h
	g++ $(CFLAGS) -c ch12drill.cpp -o ch12drill.o

Simple_window.o: Simple_window.cpp Simple_window.h GUI.h Window.h Point.h
	g++ $(CFLAGS) -c Simple_window.cpp -o Simple_window.o

Window.o: Window.cpp Window.h Point.h
	g++ $(CFLAGS) -c Window.cpp -o Window.o

Graph.o: Graph.cpp Graph.h Point.h
	g++ $(CFLAGS) -c Graph.cpp -o Graph.o

GUI.o: GUI.cpp GUI.h Window.h Point.h
	g++ $(CFLAGS) -c GUI.cpp -o GUI.o

fltkTest: fltkTest.o
	g++ fltkTest.o $(LINK) -o fltkTest

fltkTest.o: fltkTest.cpp
	g++ $(CFLAGS) -c fltkTest.cpp -o fltkTest.o

clean:
	${RM} *.exe *.o fltkTest ch12drill

.PHONY: all clean
