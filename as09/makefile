CC = g++
CFLAGS = -Wall -std=c++20
LDFLAGS = -lgmp

SOURCES = cs19_integer_quick_test.cpp
EXECUTABLE = cs19_integer_quick_test

all: clean $(EXECUTABLE)

$(EXECUTABLE): $(SOURCES)
	$(CC) $(CFLAGS) -o $(EXECUTABLE) $(SOURCES) $(LDFLAGS)

clean:
	rm -f $(EXECUTABLE)

