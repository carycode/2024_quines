
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


DAV:
Many quines
represent most of their information as
a long string.
Typically the entire text of the quine
(including both that string
and also all the executable machinery of the quine).
is printed in 3 phases:
phase 1: the executable machinery *before* the string
(including the start-quote of the string);
phase 2: regenerating the string;
and
phase 3: the executable machinery *after* the string
(including the end-quote at the end of the string).
There seems to be 3 approaches
to switching between phases:

1. Some explicit "self-referential particle" in the string,
representing more-or-less the entire contents of the string.
2. Some quines more-or-less directly store in the string
the executable machinery that comes *after* the string.
One can think of this as an "implied" self-referential particle
at the beginning of the string.
(Such quines typically try to minimize the executable machinery
*before* the string,
because it is a little awkward to regenerate).
3. Some quines more-or-less directly store in the string
the executable machinery that comes *before* the string.
One can think of this as an "implied" self-referential particle
at the end of the string.
(Such quines typically try to minimize the executable machinery
*after* the string,
because it is a little awkward to regenerate).
In C, such type-3 quines typically use
something like
"extern char d[];"
in order to allow the dna string to be placed
at the very end of the file.


DAV:
The vast majority of quines
represent most of their information as
a long string
(or an array of strings).
Many programming languages
"helpfully" allow practically any byte
to be represented in-memory in the string.
Most letters are represented by themselves as-is
in the source version of the string,
but a few bytes
(in particular, the end-of-string quote)
are represented by a few bytes of "escape sequence".
Because the in-memory and the source sequence
are not exactly the same,
a quine designer must decide:
1. will I need to "expand" the in-memory strings
I have available in-ram to re-insert those escape sequences?
(Some languages make this easy,
such as python's print(repr(text))
).
Or will I carefully design the format of the string(s)
such that they never use escape sequences,
(except perhaps for a short telemere
regenerated pretty much the same as the
quotes at both ends of the string)?
Then I can simply print(text)
the bulk of the string.
2.  Will I need to "expand" the in-memory strings
or otherwise process them,
to print the text of the executable machinery of the quine?
Or will I design the quine
so I can simply print(text)
the bulk of the executable machinery of the quine?
Alas, it's
impossible to pick the "easy" way in both case (1) and (2) --
simplifying one seems to make the other more complex.
In particular, the end-of-string symbol ...
It's unclear (and may be different for different programming languages)
whether it's simplest to:
Make (1) simple (never use built-in langauge escape sequences)
and (2) harder (perhaps using custom escape-like sequences
to handle quotes).
Or,
Make (2) simple (by using built-in language escape sequences to handle quotes)
and hope that makes up for making (1) harder.
Or, perhaps
Somehow split the difference and
do a little bit of proccessing in both (1) and (2).


## ASCII

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




