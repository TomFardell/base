AR = ar
CC = gcc
AFLAGS = rcs
CFLAGS = -g3 -Wall -std=c17 $(DEPFLAGS)
DEPFLAGS = -MMD -MP

CFILES = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
DEPFILES = $(OBJFILES:.o=.d)
LIB = libbase.a

$(LIB): $(OBJFILES)
	$(AR) $(AFLAGS) $@ $^

%.o: %.c
	$(CC) $(CFLAGS) $(EXTRAFLAGS) -c -o $@ $<

clean:
	rm -f $(LIB) *.o *.d

-include $(DEPFILES)

.PHONY: clean

