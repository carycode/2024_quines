
/*
format_string_prints_itself.c
quine
using decimal ASCII to represent quotes and newlines.
2026-02-11: started by David Cary
*/

#include <stdio.h>

extern char*d;

int main(void){
    printf(d, 10, 10, 10, 10, 10, 10, 34, d, 34, 10);
}

char*d =
    "#include <stdio.h>%c" // newline is 0x0A == 10
    "extern char*d;%c" // newline
    "int main(void){%c" // newline
    "    printf(d,10,10,10,10,10,10,34,d,34,10);%c" // newline
    "}%c" // newline
    "char*d=%c"
    "%c" // quote is 0x22 == 34
    "%s" // self-referential particle
    "%c" // quote is 0x22
    ";%c" // newline
    "";

/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */

