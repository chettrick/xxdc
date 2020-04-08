XXDC(1) - General Commands Manual

# NAME

**xxdc** - hexadecimal dump to C include file

# SYNOPSIS

**xxdc**
\[infile]

# DESCRIPTION

The
**xxdc**
utility reads
*infile*
and writes a hexadecimal static array definition and array length to
the standard output in a form suitable for inclusion in a C program.
If
*infile*
is a single dash
('-')
or absent,
**xxdc**
reads from the standard input and does not write out
the array definition nor the array length.

The array definition is named after
*infile*
as
*unsigned char infile\[]*.
The array length is named after
*infile*
as
*unsigned int infile\_len*.

# EXIT STATUS

The **xxdc** utility exits&#160;0 on success, and&#160;&gt;0 if an error occurs.

# SEE ALSO

hexdump(1),
od(1),
xxd(1),
ascii(7)

# AUTHORS

**xxdc**
was originally written by
Juergen Weigert &lt;jnweiger@informatik.uni-erlangen.de&gt;
as
xxd(1)
and flensed into its current form by
Chris Hettrick &lt;chris@structfoo.com&gt;.

OpenBSD 6.6 - March 12, 2015
