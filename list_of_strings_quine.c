

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
#define emit(x) printf(d[4], d[x]);

    // reconstruct pre-string executable
    // Generally alternate between printing a string
    // and printing a special character (which typically ends up being a newline)
    // FUTURE: support empty strings (so we can emit 2 consecutive special characters)
    // FUTURE: consider supporting "empty" special character strings (so we emit 2 consecutive normal strings)
    for(int i = 7; d[i]; i++){
        // first character in every string is a digit representing a special character
#if 0
        char *s = d[i];
        // printf("%s", s+1); // skip over the special
        printf(d[4], s+1); // skip over the special
        int special = (s[0] - '0');
        // printf("%s", d[special]); // newline, quote, or backslash
        printf(d[4], d[special]); // newline, quote, or backslash
#else
        printf(d[4], d[i]+1); // skip over the special
        printf(d[4], d[d[i][0]-'0']); // newline, quote, or backslash
#endif
    };

    // the above should have *also* expanded the teleomere at the beginning of the string
    // copy remaining post-teleomere strings in list
    // (should be no escaped characters after the teleomere)
#if 0
    // loop until we get to empty string ""
    int i=3;
    do{
        i++;
        char *s = d[i];
        putchar('"');
        // printf( "%s", s );
        printf( d[4], s );
        puts( "\","); // end-quote, comma, and also emits newline
    }while(d[i][0]);
    // emit ending bracket of list and post-string executable 
    // puts( "};" );
    puts( d[5] );
#else
    // loop until we get to the 0 (null pointer) marking the end of the list 
    for(int i = 4; d[i]; i++){
#if 0
        putchar('"'); // begin-quote
#else
        putchar(d[0][0]); // begin-quote
#endif

#if 0
        char *s = d[i];
        printf(d[4], s);
        puts( "\","); // end-quote, comma, and also emits newline
#elseif 0
        printf(d[4], d[i]);
        puts( "\","); // end-quote, comma, and also emits newline
#else
        printf(d[4], d[i]);
        putchar(d[0][0]); // end-quote
        puts(","); // comma and newline
#endif
    };
    // emit null pointer, ending bracket of list, and post-string executable 
    // puts( "0};" );
    puts( d[5] );
#endif

}

// dna string
char *d[]={
// start with a teleomere of bytes we need that must be escaped
// "", // 0 empty string -- unnecessary.
"\"", // 0 quote
"\n", // 1 newline
"\\", // 2 backslash
// from here on, we avoid using escape sequences ...
"", // 3 -- FIXME: unnecessary
"%s", // 4
"0};", // 5
// citation and attribution (analogous to junk dna?)
" 2025-07-10: ANSI C quine by David Cary", // 6
// then more-or-less the text of the executable quine
"1#include <stdio.h>", // 7
"1extern char *d[];",
"1int main(void){",
"1    for(int i=7; d[i]; i++){",
"1        char *s = d[i];",
"1        printf(d[4], s+1);",
"1        int x = s[0] - '0';",
"1        printf(d[4], d[x]);",
"1    };",
"1    for(int i=4; d[i]; i++){",
"1        putchar(d[2][0]);"
// "1        char *s = d[i];",
"1        printf(d[4], d[i]);",
"0        puts(",
"0,",
"1);",
"1    };",
"1    puts(d[5]);",
"1}",
"1char *d[]={",
// then reconstruct the above teleomere
"0",
"2",
"0",
"0",
"0,",
"2",
"0n",
"0,",
"2",
"2",
"0",
"1,",
#if 0
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
