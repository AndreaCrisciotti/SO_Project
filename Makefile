CC=gcc
CCOPTS=--std=gnu99 -g -Wall 
AR=ar


BINS=topOS

OBJS=

HEADERS=topOS.h

LIBS=

%.o:	%.c $(HEADERS)
	$(CC) $(CCOPTS) -c -o $@  $<

.phony: clean all


all:	$(BINS) $(LIBS)

topOS: topOS.c $(OBJS)
	$(CC) $(CCOPTS) -o $@ $^

clean:
	rm -rf *.o *~ $(LIBS) $(BINS)
