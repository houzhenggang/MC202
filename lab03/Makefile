
objdir = bin
objs = $(addprefix $(objdir)/, balloc.o grandeint.o lista.o)
CFLAGS = -O2 -Wall # -Werror -ansi -pedantic

lab03: $(objs) bin/principal.o
	$(CC) -o $(objdir)/lab03 $(objs) bin/principal.o

testa: $(objs) bin/testa.o
	$(CC) -o $(objdir)/testa $(objs) bin/testa.o

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
