

// copy_quine.c
// version 0.2025.01
// 2025-07-08: started by David Cary
// Unlike most quines, this is:
// * ANSI C compatible (in particular, it does *not* depend on ASCII)
// * output expansion is uniform; there's no
// distinct "regenerate dna string" phase and
// distinct "regenerate executable source" phases.

// This quine does not assume ASCII.



#include <stdio.h> // for puts()
#include <string.h> // for memcpy()
#include <assert.h> // for assert()
#include <ctype.h> // for assert(isdigit(...))
#include <stdlib.h> // for strtol()

// dna string
extern char d[];


int fixed_width_get_i(char * s){
    int value = (s[0] - 'A')*20 + (s[1] - 'A');
    return value;
}
int variable_width_get_i(char * s){
    // long strtol(char * str, char ** end, int base)
    // strtol sets "end" to point to the character *following*
    // the last valid numeric character in the string.
    char * end = 0;
    int value = strtol(s, &end, 8); // octal: base 8
    // int value = strtol(s, end, 36); // base36
    return value;
}

int get_i(char * s){
    assert(0);
    // FIXME:


}

int main(void){

    // start overwriting just *past* the NULL byte at the end of the initialized data
    char * dest = d + strlen(d);
    const char * const start_output = dest;

    // we leave that NULL byte for this test:
    for(int i=3; d[i]; i++){
#if 1
        int offset = get_i(d+i);
        int length = get_i(d+i);
        int literals = get_i(d+i);
#else
        int offset = 0;
        int length = 0;
        int literals = 0;
        int consumed = 0;
        // fixed width
        int dummy = sscanf( (d+i), "%2x%2x%2x", &offset, &length, &literals);
        i+=6;
        // all variable-width
        int dummy = sscanf( (d+i), "%o %o %o %n", &offset, &length, &literals, &consumed);
        i+= consumed;
        // mixed (premature optimization?)
        // of octal digits : alphabetic : octal : alphabetic
        // for example "4500C700Z"
        int dummy = sscanf( (d+i), "%o%c%o%c%n", &offset, &length, &literals, &misc, &consumed);
        i+= consumed;
        length -= 'A';
        misc -= 'A';
#endif
        // FUTURE: consider forward offsets from original start of dna string
        // rather than backward offsets from current position in output string.
        // FUTURE: consider using memccpy() ?
        // void *memcpy( void * dest, cost void * src, size_t n );
#define MIN_COPY_ITEM 6 /* FIXME: probably wrong */
        memcpy( dest, d+i-offset, length );
        i += MIN_COPY_ITEM; dest += length;
        memcpy( dest, d+i, literals );
        i += literals; dest += literals;
    };
    puts(start_output);
    // FUTURE: is better have an explicit literal count?
    // (i.e., Pascal-style strings).
    // (This allows nearly all possible bytes in the dna string).
    // Or is it better to have some end-of-string marker?
    // (i.e., something like ASCIIZ C-style strings, except
    // in this quine
    // we're using "any octal digit" to both
    // * mark the end of the literal substring, and
    // * start the next (offset, length) value.
    // (Using octal digits as the end-of-literal-marker
    // requires octal digits to be escaped in the bulk of the dna string).
    // 2024-07-14:DAV: A third option:
    // dynamic quotes / "here document" start each string
    // with an end-of-string marker (potentially different for each string).
    // The more general here document
    // allows a long custom delimiter,
    // which can be selected to avoid matching
    // anywhere in any pre-existing string
    // (with the notable exception of
    // quines that don't yet have a pre-existing string).
    // But for this quine,
    // given that each line is less than 80 characters,
    // it's fairly easy to find a single isgraph() character
    // that isn't on that specific line.
    // Those end-of-literal-marker bytes do not need be escaped
    // in the DNA string.

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

// FUTURE: consider perhaps
// modifying the DNA string on the first or second pass.
// Such as, for example, writing a NULL byte at the end of each line
// and using puts() to emit each line, including the newline.
// That likely requires emitting or at least copying
// the original value of the dna string before those edits.

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
