src = $(wildcard *.c)
obj = $(patsubst %.c, %.o, $(src))
target = out

CC = gcc
CFLAGS = -g -O2

all : $(target)
$(target) : $(obj)
	$(CC) -o $@ $^ 
clean :
	rm -rf *.o out