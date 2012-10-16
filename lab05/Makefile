
objdir = bin
objs = $(addprefix $(objdir)/, balloc.o setcover.o datastruct.o)
CFLAGS = -O0 -ggdb3 -Wall # -Werror -ansi -pedantic

lab05: $(objs) bin/main.o
	$(CC) -o $(objdir)/lab05 $(objs) bin/main.o

# testa: $(objs) bin/testa.o
# 	$(CC) -o $(objdir)/testa $(objs) bin/testa.o

bin/%.o : %.c
	$(CC) -c $(CFLAGS) $< -o $@

clean:
	rm -f bin/*
