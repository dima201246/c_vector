CC = gcc
LDFLAGS = -shared
CFLAGS = -fPIC -Wall -c
SOURCES = c_vector.c
OBJECTS = $(SOURCES:.c=.o)

vpath %.c

EXECUTABLE = libc_vector.so

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $@ $(LDFLAGS) 

.c.o:
	$(CC) $(CFLAGS) $< -o $@

.PHONY: install
install:
	cp $(EXECUTABLE) /usr/lib/$(EXECUTABLE)

.PHONY: clean
clean:
	rm $(OBJECTS)

.PHONY: clean-all
clean-all:
	rm -rf *.o && rm $(EXECUTABLE)
