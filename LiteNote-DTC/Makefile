CC=gcc
TARGET=ilispvm
LDLIBS=-lreadline
#CFLAGS=-O2 -W -Wall -I./include/
CFLAGS=-g3 -O0 -DDEBUG_MODE -W -Wall -I./include/
OBJS=\
	build/mainvm.o \
    build/tokenvm.o \
    build/parservm.o \
	build/generatecode.o \
	build/vm.o \
	build/hash.o

.PHONY: all
all:	$(TARGET)

$(TARGET): $(OBJS)
#	$(CC) $(LDLIBS) -o $@ $^
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDLIBS)

build/mainvm.o: src/mainvm.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/tokenvm.o: src/tokenvm.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/parservm.o: src/parservm.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/generatecode.o: src/generatecode.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/vm.o: src/vm.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/hash.o: src/hash.c # include/ilispvm.h
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: test
test:
	./$(TARGET) < test.lisp

