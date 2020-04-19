
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
	rm -rf faultsim_gui
	rm -rf out.txt
	rm -rf HBM_BCH_out.txt
	rm -rf HBM_RS_out.txt
	rm -rf HBM_none_out.txt

doc:
	cd doc && make

trying:
	$(CC) $(SOURCES) $(INC) $(LDFLAGS) -o faultsim

debug:
	$(CC) -g $(SOURCES) $(INC) $(LDFLAGS) -o faultsim
gui:
	g++ -std=c++11 -rdynamic -o faultsim_gui src/ConfigParser.cpp faultsim_gui.c `pkg-config --cflags --libs gtk+-3.0` -export-dynamic
