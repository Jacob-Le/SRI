# Variable Definition Include file
CODE_HOME=$(HOME)/code
BIN=$(CODE_HOME)/bin
OBJECTS=$(CODE_HOME)/objects
SOURCES=$(CODE_HOME)/sources
HEADERS=$(CODE_HOME)/headers
GCC=/usr/bin/g++
DEBUG= -g
INCLUDES= -I $(CODE_HOME)/headers
GCC_FLAGS= -std=c++11

include makefile.vars # Include variable file

# Notice the three dependencies that correspond to the target of the three compile rules
$(BIN)/SRI: $(OBJECTS)/SRI.o $(OBJECTS)/good_morning_lib.o $(OBJECTS)/SRI.o
	$(GCC) $(OBJECTS)/SRI.o \
	$(OBJECTS)/Parse.o\
	-o$(BIN)/SRI

# Cleaning by deleting all the object and the excutable files
clean:
	rm -rf $(BIN)/* $(OBJECTS)/*
	
$(OBJECTS)/Parse.o: $(SOURCES)/Parse.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Parse.cpp \
	-o $(OBJECTS)/Parse.o

$(OBJECTS)/SRI.o: $(SOURCES)/SRI.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/SRI.cpp \
	-o $(OBJECTS)/SRI.o