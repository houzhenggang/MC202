
objdir = bin
objs = $(addprefix $(objdir)/, principal.o)
CFLAGS = -O0 -ggdb3 -Wall # -Werror -ansi -pedantic

lab06: $(objs) bin/principal.o
	$(CC) -o $(objdir)/lab06 $(objs) 

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
