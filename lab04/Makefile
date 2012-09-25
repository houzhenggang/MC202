objdir = bin
CFLAGS = -O0 -ggdb -Wall # -Werror -ansi -pedantic

lab04: $(objs) bin/principal.o
	$(CC) -o $(objdir)/lab04 bin/principal.o

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
