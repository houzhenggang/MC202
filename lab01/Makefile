objdir = bin
objs = $(addprefix $(objdir)/,main.o balloc.o)
CFLAGS = -O0 -ggdb -Wall # -Werror -ansi -pedantic

lab01: $(objs)
	$(CC) -o $(objdir)/lab01 $(objs)

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
