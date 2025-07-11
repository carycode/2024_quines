

// extern_quine.c
// version 0.2025.01
// 2025-07-10: started by David Cary
// Unlike most quines, this is:
// * ANSI C compatible (in particular, it does *not* depend on ASCII)
// * avoids using normal C escape sequences in the bulk of the dna string
// Unlike most C quines, this
// delays the dna string to the *end* of the program.

#include <stdio.h> // for puts() and putchar()
#include <assert.h> // for assert()
#include <ctype.h> // for assert(isdigit(...))

// dna string
extern char d[];

int main(void){

    // reconstruct pre-string executable
#if 0
    puts( d+22 );
#else
    for(int i = 44; d[i]; i++){
        char c = d[i];
        if('Z' == c){
            i++;
            c = d[i] - '0';
            putchar(d[c]); // newline, quote, or backslash
        }else{
            putchar(c);
        };
    };
#endif

    // expand string, carefully expanding
    // newlines to '\n',
    // quotes to '"', and
    // backslash to '\\'.
#if 0
    for(int i = 0; d[i]; i++){
        char c = d[i];
        if(d[0] == c){
            putchar(d[1]);
            c = 'n';
        }else if(d[2] == c){
            putchar(d[1]);
        }else if(d[1] == c){
            putchar(d[1]);
        };
        putchar(c);
    };
#elseif 0
    for(int i = 0; d[i]; i++){
        char c = d[i];
        if('\n' == c){
            puts("\\n");
        else if('"' == c){
            puts("\\\"");
        else if('\\' == c){
            puts("\\\\");
        else{
            putchar(c);
        };
    };
#else
    // the above should have *also* expanded the teleomere at the beginning of the string
    // copy post-teleomere string (should be no escaped characters after the teleomere)
    puts(d+3);
#endif

    // emit ending quote of string and post-string executable 
#if 0
    putchar( '"' ); // quote
    putchar( ';' );
#else
    puts( "\";" );
#endif
}

// dna string
char d[]=
// start with a teleomere of bytes we need that must be escaped
"\n" "\\" "\"" "n" "Z"
// citation and attribution (analogous to junk dna?)
" 2025-07-10: ANSI C quine by David Cary"
// then more-or-less the text of the executable quine
"#include <stdio.h>Z0"
"extern char d[];Z0"
"int main(void){Z0"
"    for(int i = 43; d[i]; i++){Z0"
"        char c = d[i];Z0"
"        if('Z4' == c){Z0"
"            i++;Z0"
"            c = d[i] - '0';Z0"
"            putchar(d[c]);Z0"
"        }else{Z0"
"            putchar(c);Z0"
"        };Z0"
"    };Z0"
"    puts(d+3);Z0"
"    puts( Z2Z1Z2;Z2 );Z0"
"}Z0"
"char d[]=Z0Z2"
// then reconstruct the above teleomere
"Z1Z3"
"Z1Z1"
"Z1Z2"
"";





/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */
