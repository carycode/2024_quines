

// extern_quine.c
// version 0.2025.01
// 2025-07-10: started by David Cary
// Unlike most quines, this is:
// * ANSI C compatible (in particular, it does *not* depend on ASCII)
// * avoids using normal C escape sequences in the bulk of the dna string
// Unlike most C quines, this
// delays the dna string to the *end* of the program.

// dna string
extern char d[];

#include <stdio.h> // for puts()
#include <assert.h> // for assert()
#include <ctype.h> // for assert(isdigit(...))

int main(void){

    // reconstruct pre-string executable
#if 0
    puts( d+22 );
#else
    for(int i = 43; d[i]; i++){
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
    // copy string (should be no escaped characters after the teleomere)
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
"\n" "\\" "\"" "n"
// citation and attribution (analogous to junk dna?)
" 2025-07-10: ANSI C quine by David Cary"
// then more-or-less the text of the executable quine
"#include <stdio.h>Z0"
"extern char d[];"
"int main(void){"
"   puts( d+22 );"
"   putchar( d[2] );"
"   puts( d+3 );"
"   putchar( d[2] );"
"   putchar( ';' );"
"}"
"char d[1000]=Z2"
// then reconstruct the above teleomere
"Z0Z1Z2"
"";



/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */
