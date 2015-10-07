TARGETS=homework4 thread_example

CFLAGS=-Wall -g -O0

all: $(TARGETS)

homework4: homework4.c
	gcc $(CFLAGS) -o homework4 homework4.c -lpthread

thread_example: thread_example.c
	gcc $(CFLAGS) -o thread_example thread_example.c -lpthread

clean:
	rm -f $(TARGETS)
