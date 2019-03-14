CXX=g++
CXXFLAGS=-std=c++0x
SRCS=smatrix.cpp

all: QuAl

QuAl: smatrix.o qual.o
	$(CXX) -o QuAl $?

smatrix.o: smatrix.cpp smatrix.hpp
	$(CXX) $(CXXFLAGS) -c smatrix.cpp
qual.o: qual.cpp
	$(CXX) $(CXXFLAGS) -c qual.cpp

clean:
	rm *.o
