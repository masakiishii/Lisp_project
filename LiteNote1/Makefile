CC=gcc
TARGET=ilisp
LDLIBS=-lreadline
CFLAGS=-g0 -O2 -W -Wall
OBJS=\
	main.o \
    tokenizer.o \
    parser.o \
	print.o \
	read.o \
	eval.o \
	eval_string.o \
	hash.o

.PHONY: all
all:	$(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(LDLIBS) -o $@ $^
#	$(CC) $(CFLAGS) $(LDLIBS) -o $(TARGET) $^

main.o: main.c ilisp.h
	$(CC) $(CFLAGS) -c $^

tokenizer.o: tokenizer.c ilisp.h
	$(CC) $(CFLAGS) -c $^

parser.o: parser.c ilisp.h
	$(CC) $(CFLAGS) -c $^

print.o: print.c ilisp.h
	$(CC) $(CFLAGS) -c $^

read.o: read.c ilisp.h
	$(CC) $(CFLAGS) -c $^

eval.o: eval.c ilisp.h
	$(CC) $(CFLAGS) -c $^

eval_string.o: eval_string.c ilisp.h
	$(CC) $(CFLAGS) -c $^

hash.o: hash.c ilisp.h
	$(CC) $(CFLAGS) -c $^

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)

.PHONY: test
test:
	./$(TARGET) < test.lisp
