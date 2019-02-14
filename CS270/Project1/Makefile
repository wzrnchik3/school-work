SOURCES=test-abbrev.c kstring.c
BINARIES=test-abbrev test-full

CFLAGS = -fPIC -no-pie -std=c99 -Wall $(OPT)

all: $(BINARIES)

memcheck: test-full
	valgrind --tool=memcheck --child-silent-after-fork=yes ./test-full

clean:
	-rm -f $(BINARIES) $(SOURCES:.c=.o) core vgcore.*

test-abbrev: test-abbrev.o kstring.o
	$(CC) $(CFLAGS) -o $@ $^

test-full: test-full.o kstring.o
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c kstring.h
	$(CC) $(CFLAGS) -c -o $@ $<

run: test-full
	./test-full