

// copy_quine.c
// version 0.2025.01
// 2025-07-08: started by David Cary
// Unlike most quines, this is:
// * ANSI C compatible (in particular, it does *not* depend on ASCII)
// * output expansion is uniform; there's no
// distinct "regenerate dna string" phase and
// distinct "regenerate executable source" phases.

// dna string
extern char d[];

#include <stdio.h> // for puts()

int get_i(char * s){
    assert(0);
    // FIXME:


}

int main(void){

    // start overwriting just *past* the NULL byte at the end of the initialized data
    char * dest = d + strlen(d);
    const char * start_output = dest;

    // we leave that NULL byte for this test:
    for(;*d;){
        int offset = get_i(d);
        int length = get_i(d);
        int literals = get_i(d);
        copy( d - offset, length, ....);
        copy( d, literals, ...);
    };
    puts(start_output);

#if 0 // classic approach
    // reconstruct pre-string executable
    puts( d+22 );

    // reconstruct starting quote of string, and early teleomere
    //putchar( d[2] );

    // reconstruct rest dna string
    puts( d+3 );

    // emit ending quote of string and post-string executable 
    putchar( d[2] );
    putchar( ';' );
#endif

}

// dna string
char d[1000]=
// start with a teleomere of bytes we need that must be escaped
"\n\\"
// followed by an unnecessarily clever quote
"\""
// followed by octal digits
"01234567"
// then more-or-less the text of the executable quine
// as a series of
// long literals with null copies (length=0 copies)
// zero-length literals with length-1 copies for the newlines and other "escaped" bytes
// The above are all that's necessary, but
// perhaps we'll occasionally "optimize"
// with longer copies or combined copy+literal or both.

"// 2025-07-08: ANSI C quine by David Cary"
"#include <stdio.h>"
// FIXME: literal newline here
"extern char d[];"
"int main(void){"
"   puts( d+22 );"
"   putchar( d[2] );"
"   puts( d+3 );"
"   putchar( d[2] );"
"   putchar( ';' );"
"}"
"char d[1000]="
// regenerate teleomere with a bunch of length=1 copies
// offset = +2, length = 1
// regenerate entire dna string with a length=strlen(d) copy
// regenerate ending quote with
// perhaps a length=1 copy of the quote, and a length=1 literal semicolon.
"";



/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */
