# Makefile, ECE254 lab4 Linux variable size memory management lab 
# Yiqing Huang, 2017/07/10

CC = gcc
CFLAGS = -Wall -g -std=c99
LD = gcc
LDFLAGS = -g 
LDLIBS = -lrt

SRCS   = mem.c util.c main_test.c
OBJS   = mem.o util.o main_test.o
TARGETS= main_test.out

all: ${TARGETS}

main_test.out: $(OBJS) 
	$(LD) -o $@ $^ $(LDLIBS) $(LDFLAGS) 

%.o: %.c 
	$(CC) $(CFLAGS) -c $< 

%.d: %.c
	gcc -MM -MF $@ $<

-include $(SRCS:.c=.d)

.PHONY: clean
clean:
	rm -f *.d *.o $(TARGETS) 
