include makefile.vars # Include variable file

$(BIN)/SRI_Test: $(OBJECTS)/Parse.o
	$(GCC) $(OBJECTS)/Parse.o \
	-o $(BIN)/SRI

# Cleaning by deleting all the object and the excutable files
clean:
	rm -rf $(BIN)/* $(OBJECTS)/*
    
$(OBJECTS)/Parse.o: $(SOURCES)/Parse.cpp
	$(GCC) $(DEBUG) $(GCC_FLAGS) $(INCLUDES) $(SOURCES)/Parse.cpp \
	-o $(OBJECTS)/Parse.o