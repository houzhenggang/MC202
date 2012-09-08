objdir = bin
objs = $(addprefix $(objdir)/,principal.o balloc.o grandeint.o lista.o)
CFLAGS = -O0 -ggdb -Wall # -Werror -ansi -pedantic

lab03: $(objs)
	$(CC) -o $(objdir)/lab03 $(objs)

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
