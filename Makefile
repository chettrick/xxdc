PROG=		xxdc

SRCS=		xxdc.c

MAN=		xxdc.1

CFLAGS+=	-g
CFLAGS+=	-Wall -Wextra -std=c99 -pedantic -Wformat=2
CFLAGS+=	-Wmissing-declarations -Wstrict-prototypes -Wcast-qual
CFLAGS+=	-Wpointer-arith -Wuninitialized -Wmissing-prototypes
CFLAGS+=	-Wsign-compare -Wshadow -Wdeclaration-after-statement
CFLAGS+=	-Wfloat-equal -Wcast-align -Wundef -Wstrict-aliasing=2

all: ${PROG} README.md

${PROG}: ${SRCS}
	${CC} ${CFLAGS} ${LDFLAGS} -o $@ ${SRCS}

README.md: ${MAN}
	mandoc -T markdown ${MAN} > $@

clean:
	rm -f a.out [Ee]rrs mklog *.core y.tab.h ${PROG} ${PROG}.o README.md
