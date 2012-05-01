CC=gcc
TARGET=ilispvm
LDLIBS=-lreadline
CFLAGS=-g3 -O0 -W -Wall
OBJS=\
	mainvm.o \
    tokenvm.o \
    parservm.o \
	generatecode.o \
	vm.o

.PHONY: all
all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDLIBS) -o $@ $^
#	$(CC) $(CFLAGS) $(LDLIBS) -o $(TARGET) $^

mainvm.o: mainvm.c ilispvm.h
	$(CC) $(CFLAGS) -c $^

tokenvm.o: tokenvm.c ilispvm.h
	$(CC) $(CFLAGS) -c $^

parservm.o: parservm.c ilispvm.h
	$(CC) $(CFLAGS) -c $^

generatecode.o: generatecode.c ilispvm.h
	$(CC) $(CFLAGS) -c $^

vm.o: vm.c ilispvm.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: test
test:
	./$(TARGET) < test.lisp
