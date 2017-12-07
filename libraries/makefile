all: fileIO.exe weatherSS.exe testGraph.exe

CCFLAGS=-std=c++11 -Wall -g

testGraph.exe: testGraph.o SCGraph.o SCAxis.o
	g++ $(CCFLAGS) -o $@ $^

testGraph.o: testGraph.cpp
	g++ $(CCFLAGS) -c $^

SCGraph.o: SCGraph.cpp SCGraph.h
	g++ $(CCFLAGS) -c $<

SCAxis.o: SCAxis.cpp SCAxis.h
	g++ $(CCFLAGS) -c $<

weatherSS.exe: weatherSS.o 
	g++ $(CCFLAGS) -o $@ $^

weatherSS.o: weatherSS.cpp
	g++ $(CCFLAGS) -c $^

fileIO.exe: fileIO.o Chrono.o
	g++ $(CCFLAGS) -o $@ $^

fileIO.o: fileIO.cpp
	g++ $(CCFLAGS) -c $<

Chrono.o: Chrono.cpp Chrono.h
	g++ $(CCFLAGS) -c $<

clean:
	rm *.exe *.o *~

.PHONY: all clean
