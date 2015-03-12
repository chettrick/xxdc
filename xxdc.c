/*
 * Copyright (c) 2015 Chris Hettrick <chris@structfoo.com>
 * (c) 1990-1998 by Juergen Weigert <jnweiger@informatik.uni-erlangen.de>
 *
 * Distribute freely and credit me,
 * make money and share with me,
 * lose money and don't ask me.
 */

#include <ctype.h>
#include <err.h>
#include <libgen.h>
#include <stdio.h>
#include <stdlib.h>

#define COLS 12

int
main(int argc, char *argv[])
{
	FILE *		fp;
	char *		bname;
	int		c, e;
	uint64_t	count;

	if (argc > 2) {
		(void)fprintf(stderr, "usage: xxdc [infile]\n");
		exit(1);
	}
	if (argc == 1 || (argv[1][0] == '-' && !argv[1][1]))
		fp = stdin;
	else
		if ((fp = fopen(argv[1], "r")) == NULL)
			err(1, "%s", argv[1]);

	if ((bname = basename(argv[1])) == NULL)
		err(1, "%s", argv[1]);

	if (fp != stdin) {
		if (fprintf(stdout, "unsigned char %s",
		    isdigit((int)bname[0]) ? "__" : "") < 0)
			err(1, "stdout");
		for (e = 0; (c = (int)bname[e]) != 0; e++)
			if (putc(isalnum(c) ? c : '_', stdout) == EOF)
				err(1, "stdout");
		if (fprintf(stdout, "[] = {\n") == EOF)
			err(1, "stdout");
	}

	for (count = 1; (c = getc(fp)) != EOF; count++)
		if (fprintf(stdout, "0x%02x,%s", c,
		    ((count % COLS) > 0) ? " " : "\n") < 0)
			err(1, "stdout");

	if (c == EOF && ferror(fp))
		err(1, "stdin");
	if (fprintf(stdout, "%s",
	    (count % COLS) == 1 ? "" : "\n") == EOF)
		err(1, "stdout");
	if (fprintf(stdout, "%s", (fp == stdin) ? "" : "};\n") == EOF)
		err(1, "stdout");

	if (fp != stdin) {
		if (fprintf(stdout, "unsigned int %s",
		    isdigit((int)bname[0]) ? "__" : "") < 0)
			err(1, "stdout");
		for (e = 0; (c = (int)bname[e]) != 0; e++)
			if (putc(isalnum(c) ? c : '_', stdout) == EOF)
				err(1, "stdout");
		if (fprintf(stdout, "_len = %llu;\n", count - 1) < 0)
			err(1, "stdout");
	}

	if (fclose(fp))
		err(1, "stdin");
	if (fclose(stdout))
		err(1, "stdout");
	return (0);
}
