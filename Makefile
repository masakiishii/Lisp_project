CC=gcc
TARGET=ilisp
LDLIBS=-lreadline
CFLAGS=-g3 -O0
OBJS=\
	main.o \
    tokenizer.o \
    parser.o \
	print.o \
	read.o

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

.PHONY: clean
clean:
	$(RM) $(TARGET) $(OBJS)
