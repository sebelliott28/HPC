PROG = barley

SRCS = barley_both.c

OBJS = barley_both.o

LIBS = -lm

CC = icc
CFLAGS = -O0
LDFLAGS =

all: $(PROG)

$(PROG): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(PROG) $(OBJS) *.mod

