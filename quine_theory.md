
## Quine Theory

2025-07-15: started by David Cary

A quine is a computer program that prints out its own source code.

I'm kind of embarrassed to admit how much time I've spent been pondering quines.

In particular,
I prefer quines that don't depend on ASCII
or any other particular mapping from character to numeric code.
(In particular,
the "Basic Execution Character Set" defined by ANSI C
and
one of its supersets, the
"Portable Character Set" defined by POSIX
is a "mathematical set" of characters
without any particular numeric value encoding.
).

ASCII defines 128 (0x80) total "characters":
33 control codes and 95 isprint() printable characters.

0x00 .. 0x1F: control codes
0x20 : space character: isprint() but not isgraph().
0x21 .. 0x7E: the isprint() and isgraph() characters
0x7F : the "del" control code.

Any byte or character can be represented in a C string
using some kind of escape sequence.
The 33 control codes cannot be literally placed in a C string,
and *require* escape codes.

(C source files only require "\n" from that group,
although C compilers also accept
several other characters such as "\t" from that group.
).
The 95 isprint() printable characters
usually can represent themselves in C strings in source files,
except for the end-of-string marker '"' quote and
the '\' backslash used for the above escape sequences.
That leaves 93 isprint() printable characters
that can represent themselves in strings,
but a quine also generally needs to emit
a few characters outside that set of 93:
it seems difficult to avoid
the quote and the newline and the backslash
in C source code.
(It's pretty easy to avoid a literal tab in C source code).




