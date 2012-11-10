
objdir = bin
objs = $(addprefix $(objdir)/, main.o arvoreb.o)
CFLAGS = -O0 -ggdb3 -Wall -std=c99 -Werror -pedantic

lab07: $(objs) bin/main.o
	$(CC) -o $(objdir)/lab06 $(objs) 

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
