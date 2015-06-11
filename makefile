# makefile: can be used as a generic multifile template.

# Name of executable
TARGET = solarpower

# Compiler
CC = g++

# compiler flags
CFLAGS =-c -Wall

# loader flags
LDFLAGS =

SOURCES  = $(shell echo *.cpp)
# List source files here
#SOURCES  = solarpower.cpp
#SOURCES += sp-atmospherics.cpp
#SOURCES += sp-computations.cpp
#SOURCES += sp-general.cpp
#SOURCES += sp-module-model.cpp

OBJECTS=$(SOURCES:.cpp=.o)

all: $(SOURCES) $(TARGET)
    
$(TARGET): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	-rm -f $(OBJECTS)

