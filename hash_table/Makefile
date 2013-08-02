CC=gcc
CFLAGS=-c -Wall -Werror -std=gnu99 -ggdb3
LDFLAGS=
SOURCES=test.c ht.c
OBJECTS=$(SOURCES:.c=.o)
EXECUTABLE=test

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f $(OBJECTS) $(EXECUTABLE)
