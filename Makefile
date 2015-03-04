CFLAGS+=-g
CFLAGS+=-Wall -Wextra -std=c99 -pedantic -Wformat=2
CFLAGS+=-Wmissing-declarations -Wstrict-prototypes -Wcast-qual
CFLAGS+=-Wpointer-arith -Wuninitialized -Wmissing-prototypes
CFLAGS+=-Wsign-compare -Wshadow -Wdeclaration-after-statement
CFLAGS+=-Wfloat-equal -Wcast-align -Wundef -Wstrict-aliasing=2

all: xxdc README

xxdc: xxdc.c
	${CC} ${CFLAGS} ${LDFLAGS} -o xxdc xxdc.c

README: xxdc.1
	mandoc xxdc.1 | col -bx > README

clean:
	rm -f xxdc xxdc.o README
