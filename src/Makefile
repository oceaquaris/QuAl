CXX=g++
CXXFLAGS=-std=c++0x -fdiagnostics-color -Wall -g
OPTIONS=$(CXXFLAGS)

CPP_FILES=$(sort $(wildcard *.cpp))
O_FILES=$(sort $(patsubst %.c,%.o,$(CPP_FILES)))


all: QuAl

%.o: %.c
	@printf "Compiling %s..." $<
	@$(CXX) $(OPTIONS) -c -o $@ $<
	@printf "\t\t...Done\n"

QuAl: $(O_FILES)
	@printf "Compiling %s..." $@
	@$(CXX) $(OPTIONS) -o $@ $^
	@printf "\t\t...Done\n"

clean:
	rm -f *.o QuAl
