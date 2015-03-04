/*
 * (c) 1990-1998 by Juergen Weigert (jnweiger@informatik.uni-erlangen.de)
 *
 * Distribute freely and credit me,
 * make money and share with me,
 * lose money and don't ask me.
 */

#include <ctype.h>
#include <err.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static void usage(void)__attribute__((__noreturn__));

static char *pname;

int
main(int argc, char *argv[])
{
	FILE *		fp;
	FILE *		fpo = stdout;
	char *		pp;
	int		c, e;
	uint64_t	count;
	unsigned int	cols = 12;

	pname = argv[0];
	for (pp = pname; *pp;)
		if (*pp++ == '/')
			pname = pp;

	while (argc >= 2) {
		pp = argv[1] + (!strncmp(argv[1], "--", 2) && argv[1][2]);
		if (!strncmp(pp, "-i", 2)) {		/* continue on -i */
			argc--;
			argv++;
			break;
		} else if (!strcmp(pp, "--")) {		/* end of options */
			argc--;
			argv++;
			break;
		} else if (pp[0] == '-' && pp[1])	/* unknown option */
			usage();
			/* NOTREACHED */
		else
			break;				/* not an option */
	}

	if (argc > 3)
		usage();
		/* NOTREACHED */

	if (argc == 1 || (argv[1][0] == '-' && !argv[1][1]))
		fp = stdin;
	else
		if ((fp = fopen(argv[1], "r")) == NULL)
			err(2, "%s", argv[1]);

	if (argc < 3 || (argv[2][0] == '-' && !argv[2][1]))
		fpo = stdout;
	else {
		int fd;

		if (((fd = open(argv[2], O_WRONLY | O_CREAT, 0666)) < 0) ||
		    (fpo = fdopen(fd, "w")) == NULL)
			err(3, "%s", argv[2]);
		if (fpo)
			rewind(fpo);
	}

	if (fp != stdin) {
		if (fprintf(fpo, "unsigned char %s",
		    isdigit((int)argv[1][0]) ? "__" : "") < 0)
			err(3, NULL);
		for (e = 0; (c = argv[1][e]) != 0; e++)
			if (putc(isalnum(c) ? c : '_', fpo) == EOF)
				err(3, NULL);
		if (fputs("[] = {\n", fpo) == EOF)
			err(3, NULL);
	}

	for (count = 1; (c = getc(fp)) != EOF; count++)
		if (fprintf(fpo, "0x%02x,%s", c,
		    ((count % 12) > 0) ? " " : "\n") < 0)
			err(3, NULL);
	if (c == EOF && ferror(fp))
		err(2, NULL);
	if (count && fprintf(fpo, "%s",
	    (count % cols) == 1 ? "" : "\n") == EOF)
		err(3, NULL);
	if (fprintf(fpo, "%s", (fp == stdin) ? "" : "};\n") == EOF)
		err(3, NULL);

	if (fp != stdin) {
		if (fprintf(fpo, "unsigned int %s",
		    isdigit((int)argv[1][0]) ? "__" : "") < 0)
			err(3, NULL);
		for (e = 0; (c = argv[1][e]) != 0; e++)
			if (putc(isalnum(c) ? c : '_', fpo) == EOF)
				err(3, NULL);
		if (fprintf(fpo, "_len = %llu;\n", count - 1) < 0)
			err(3, NULL);
	}

	if (fclose(fp))
		err(2, NULL);
	if (fclose(fpo))
		err(3, NULL);
	return (0);
}

static void
usage(void)
{
	(void)fprintf(stderr, "usage: %s [infile [outfile]]\n", pname);
	exit(1);
	/* NOTREACHED */
}
