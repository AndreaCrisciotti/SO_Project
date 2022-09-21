CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar


BINS=topOS

OBJS=binary_file_search.c

HEADERS=binary_file_search.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

.phony: clean all


all:	$(BINS) $(LIBS)

topOS: topOS.c $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
