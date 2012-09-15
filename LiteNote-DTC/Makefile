CC=gcc
TARGET=ilisp
LDLIBS=-lreadline
CFLAGS=-O2 -W -Wall -I./include/
#CFLAGS=-g3 -O0 -DDEBUG_MODE=1 -W -Wall -I./include/
OBJS=\
	build/main.o \
    build/token.o \
    build/parser.o \
	build/compiler.o \
	build/vm.o \
	build/hash.o

.PHONY: all
all:	$(TARGET)

$(TARGET): $(OBJS)
#	$(CC) $(LDLIBS) -o $@ $^
	$(CC) $(CFLAGS) -o $(TARGET) $^ $(LDLIBS)

build/main.o: src/main.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/token.o: src/token.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/parser.o: src/parser.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/compiler.o: src/compiler.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/vm.o: src/vm.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

build/hash.o: src/hash.c # include/ilisp.h
	$(CC) $(CFLAGS) -o $@ -c $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: test
test:
	./$(TARGET) < test.lisp

