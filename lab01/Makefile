<<<<<<< HEAD
objdir = bin
objs = $(addprefix $(objdir)/,main.o balloc.o)
CFLAGS = -O0 -ggdb -Wall # -Werror -ansi -pedantic

lab01: $(objs)
	$(CC) -o $(objdir)/lab01 $(objs)

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
=======
compile: balloc.h main.h balloc.c main.c
	gcc main.c -o main
>>>>>>> a24eb0074d1761c3ce4af285ca8bee4ce6945cad
