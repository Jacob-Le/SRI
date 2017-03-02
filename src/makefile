include makefile.vars # Include variable file

$(BIN)/SRI_Test: $(OBJECTS)/Parse.o $(OBJECTS)/Predicate.o $(OBJECTS)/RB.o $(OBJECTS)/KB.o $(OBJECTS)/Query.o $(OBJECTS)/testytest.o $(OBJECTS)/SRI.o$(OBJECTS)/CompileTest.o

	$(GCC) $(OBJECTS)/Parse.o \
	$(OBJECTS)/Predicate.o \
	$(OBJECTS)/RB.o \
	$(OBJECTS)/KB.o \
	$(OBJECTS)/Query.o \
	$(OBJECTS)/testytest.o \
	$(OBJECTS)/SRI.o \
	$(OBJECTS)/CompileTest.o \
	-o $(BIN)/SRI_Test

# Cleaning by deleting all the object and the excutable files
clean:
	rm -rf $(BIN)/* $(OBJECTS)/*
    
$(OBJECTS)/Parse.o: $(SOURCES)/Parse.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Parse.cpp \
	-o $(OBJECTS)/Parse.o

$(OBJECTS)/Predicate.o: $(SOURCES)/Predicate.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Predicate.cpp \
	-o $(OBJECTS)/Predicate.o

$(OBJECTS)/RB.o: $(SOURCES)/RB.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/RB.cpp \
	-o $(OBJECTS)/RB.o

$(OBJECTS)/KB.o: $(SOURCES)/KB.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/KB.cpp \
	-o $(OBJECTS)/KB.o

$(OBJECTS)/Query.o: $(SOURCES)/Query.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Query.cpp \
	-o $(OBJECTS)/Query.o

$(OBJECTS)/testytest.o: $(SOURCES)/testytest.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/testytest.cpp \
	-o $(OBJECTS)/testytest.o

$(OBJECTS)/SRI.o: $(SOURCES)/SRI.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/SRI.cpp \
	-o $(OBJECTS)/SRI.o

$(OBJECTS)/CompileTest.o: $(SOURCES)/CompileTest.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/CompileTest.cpp \
	-o $(OBJECTS)/CompileTest.o