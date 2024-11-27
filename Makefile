# Compiler and flags
CC = g++
CFLAGS = -Iinclude -std=c++11 -g
LIBS = -lglut -lGLEW -lGL -lGLU

# Targets
TARGET = city_simulation
OBJECTS = main.o InitShader.o

# Default rule
all: $(TARGET)

# Link the executable
$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) -o $(TARGET) $(OBJECTS) $(LIBS)

# Compile main file
main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

# Compile InitShader utility
InitShader.o: city_simulation/InitShader.cc
	$(CC) $(CFLAGS) -c city_simulation/InitShader.cc -o InitShader.o

# Clean rule to remove all generated files
clean:
	rm -f $(TARGET) *.o *~
