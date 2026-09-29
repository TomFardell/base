AR = ar
CC = gcc
AFLAGS = rcs
CFLAGS = -g3 -Wall -std=c23 $(DEPFLAGS)
DEPFLAGS = -MMD -MP
SANFLAGS = -fsanitize=address,undefined

LIBDEF = libbase.a
LIBSAN = libbasesan.a

BUILDDIR = build
BUILDDIRDEF = $(BUILDDIR)/default
BUILDDIRSAN = $(BUILDDIR)/sanitized

CFILES = $(wildcard *.c)
OBJFILES = $(CFILES:.c=.o)
OBJFILESDEF = $(addprefix $(BUILDDIRDEF)/, $(OBJFILES))
OBJFILESSAN = $(addprefix $(BUILDDIRSAN)/, $(OBJFILES))
DEPFILESDEF = $(OBJFILESDEF:.o=.d)
DEPFILESSAN = $(OBJFILESSAN:.o=.d)

all: $(LIBDEF) $(LIBSAN)

$(LIBDEF): $(OBJFILESDEF)
	$(AR) $(AFLAGS) $@ $^

$(LIBSAN): $(OBJFILESSAN)
	$(AR) $(AFLAGS) $@ $^

$(BUILDDIRDEF)/%.o: %.c | $(BUILDDIRDEF)
	$(CC) $(CFLAGS) $(EXTRAFLAGS) -c -o $@ $<

$(BUILDDIRSAN)/%.o: %.c | $(BUILDDIRSAN)
	$(CC) $(CFLAGS) $(SANFLAGS) $(EXTRAFLAGS) -c -o $@ $<

$(BUILDDIRDEF) $(BUILDDIRSAN):
	mkdir -p $@

clean:
	rm -rf $(LIBDEF) $(LIBSAN) $(BUILDDIR)

-include $(DEPFILES)

.PHONY: all clean

