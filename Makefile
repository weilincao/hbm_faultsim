
CC=g++
INC=-I$(BOOSTINC)

CFLAGS=-c -Wall -std=c++0x -O2
LDFLAGS=-L $(BOOSTLIB) -lboost_program_options

SOURCES := $(wildcard src/*.cpp)
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=faultsim

all: $(EXECUTABLE) doc

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $(INC) $< -o $@

clean:
	rm -rf faultsim
	rm -rf src/*.o
	cd doc && make clean

doc:
	cd doc && make

trying:
	$(CC) $(SOURCES) $(INC) $(LDFLAGS) -o faultsim

debug:
	$(CC) -g $(SOURCES) $(INC) $(LDFLAGS) -o faultsim
gui:
	gcc -o faultsim_gui faultsim_gui.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
