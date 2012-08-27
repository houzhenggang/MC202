objdir = bin
objs = $(addprefix $(objdir)/,lab02.o balloc.o)
CFLAGS = -O0 -ggdb -Wall # -Werror -ansi -pedantic

lab01: $(objs)
	$(CC) -o $(objdir)/lab02 $(objs)

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
