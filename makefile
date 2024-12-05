cCXX = g++
CXXFLAGS = -Wall -g

mytest: rqueue.o mytest.cpp
	$(CXX) $(CXXFLAGS) rqueue.o mytest.cpp -o mytest

rqueue.o: rqueue.h rqueue.cpp
	$(CXX) $(CXXFLAGS) -c rqueue.cpp

run:
	./mytest

