

// list_of_strings_quine.c
// version 0.2026.01
// 2026-03-03: compiles and runs cleanly, but not yet self-regenerating.
// 2026-03-02: started by David Cary (forked from my extern_quine.c )
// Unlike most quines, this is:
// * ANSI C compatible (in particular, it does *not* depend on ASCII)
// * avoids using normal C escape sequences in the bulk of the dna string
// Unlike most C quines, this
// delays the dna string to the *end* of the program.

#include <stdio.h> // for puts() and putchar()
#include <assert.h> // for assert()
#include <ctype.h> // for assert(isdigit(...))

// dna string
extern char *d[];

int main(void){

    // reconstruct pre-string executable
    // Generally alternate between printing a string
    // and printing a special character (which typically ends up being a newline)
    // FUTURE: support empty strings (so we can emit 2 consecutive special characters)
    // FUTURE: consider supporting "empty" special character strings (so we emit 2 consecutive normal strings)
    for(int i = 7; d[i][0]; i++){
        // first character in every string is a digit representing a special character
        char *s = d[i];
        // printf("%s", s+1); // skip over the special
        printf(d[4], s+1); // skip over the special
        int special = (s[0] - '0');
        // printf("%s", d[special]); // newline, quote, or backslash
        printf(d[4], d[special]); // newline, quote, or backslash
    };

#if 0
    // carefully expanding
    // newlines to '\n',
    // quotes to '"', and
    // backslash to '\\'.
#else
    // the above should have *also* expanded the teleomere at the beginning of the string
    // copy remaining post-teleomere strings in list
    // (should be no escaped characters after the teleomere)
    // (also copies the empty string ("") marking the end of the list).
    int i=3;
    do{
        i++;
        char *s = d[i];
        putchar('"');
        // printf( "%s", s );
        printf( d[4], s );
        puts( "\","); // end-quote, comma, and also emits newline
    }while(d[i][0]);
#endif

    // emit ending bracket of list and post-string executable 
    // puts( "};" );
    puts( d[5] );
}

// dna string
char *d[]={
// start with a teleomere of bytes we need that must be escaped
"", // 0 empty string -- perhaps unnecessary?
"\n", // 1 newline
#if 1
"\"", // 2 quote
#else
{ '"', 0 }, // 2 quote
#endif
"\\", // 3 backslash
// from here on, we avoid using escape sequences ...
"%s", // 4
"};", // 5
// citation and attribution (analogous to junk dna?)
" 2025-07-10: ANSI C quine by David Cary", // 6
// then more-or-less the text of the executable quine
"1#include <stdio.h>", // 7
"1extern char *d[];",
"1int main(void){",
"1    for(int i=7; d[i][0]; i++){",
"1        char *s = d[i];",
"1        printf(d[4], s+1);",
"1        int x = s[0] - '0';",
"1        printf(d[4], d[x]);",
"1    };",
"1    for(int i=4; d[i][0]; i++){",
"1        char *s = d[i];",
"2        putchar('",
"1');",
"1        printf( d[4], s );",
"2        puts(",
"3",
"2",
"2,",
"1);",
"1    };",
"1    puts(d[5]);",
"1}",
"1char *d[]={",
// then reconstruct the above teleomere
"Z1Z3",
"Z1Z1",
"Z1Z2",
#if 1
// empty string marks end-of-list:
""
#else
// null pointer marks end-of-list:
0
#endif
// (end-of-list is effectively the self-referential particle)
// then reconstruct the post-teleomere list of strings
// and this final "};\n".
};





/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */
