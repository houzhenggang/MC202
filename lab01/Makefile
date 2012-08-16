objdir = bin
objs = $(addprefix $(objdir)/,main.o balloc.o)
CFLAGS = -O0 -ggdb

lab12: $(objs)
	$(CC) -o $(objdir)/lab12 $(objs)

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
