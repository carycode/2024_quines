

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
extern char dna[];


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

    {
        int len = strlen(dna);
        printf( "dna length: %i (octal %o ).\n", len, len ); // debug
        assert( 'y' == dna[41] );
    }

    // start overwriting just *past* the NULL byte at the end of the initialized data
    char * dest = dna + strlen(dna) + 1;
    char * d = dna;
    const char * const start_output = dest;

    // we leave that NULL byte for this test:
    for(int i=42; d[i]; i++){
        // First read a relative offset,length item
        // and copy that into the dest string
        // This is used for
        // (a) the self-referential copy that copies the bulk of the dna string
        // except for a short initial teleomere
        // (which cannot be a simple literal copy)
        // (b) bytes that cannot represent themselves
        // in the bulk of the dna string (double-quotes, backslashes, etc.)
        // both inside the dna string (the short initial telomere)
        // (in other quines, handled by a "regenerate dna string" section)
        // *and* also in the executable source
        // (in other quines, handled by a "regenerate executable source" section)
        // .
        // and optionally could be used for
        // (c) data compression, expanding repeated sections of the executable source.
        {
            printf("copy item: (%c)[%.6s] \n", *(d+i-1), d+i); // debug
            int offset = d[i++] - 'A';
            assert( 0 <= offset );
            assert( offset <= 25 );
            char * end = 0;
            // long strtol(char * str, char ** end, int base)
            // strtol sets "end" to point to the character *following*
            // the last valid numeric character in the string.
            int length = strtol(d+i, &end, 8);
            int delta_i = end - (d+i);
            i += delta_i;
            // assume we've hit the quote character, not the end of the string
            // (also we're assuming the quote character is not an octal digit).
            assert( d[i] );
            // mempcpy() would also work.
            //
            printf("length: %i; offset: %i\n", length, offset); // debug
#if 1 // forward_offset
            memcpy( dest, d+offset, length ); 
#else // backward offset
            memcpy( dest, d+i-offset, length );
#endif
            dest += length;
        };
        // Second, read a "literal string" and emit it;
        // DAV has designed this little language / domain specific language
        // to avoid unnecessary restrictions on the content of the string
        // by allowing each literal string
        // to use a different quote character at the beginning and end of the string.
        {
            const char quote = d[i++];
            printf("quote: %c; literal: %.5s... \n", quote, d+i ); // debug
            // void *memccpy(void *dest, const void *src, int c, size_t n);
            // copy up to n bytes between two memory areas, which must not overlap,
            // stopping when byte c is found.
            // memccpy() returns a pointer to the next character in dest after c,
            // or NULL if c was not found in the first n characters of src.
            // Apparently the byte c is the last byte copied.
            char * end = 0;
            end = memccpy( dest, d+i, quote, 1000 );
            assert( quote == end[-1] );
            const int delta_i = end - dest;
            // The smallest possible value for this delta_i 
            // (when the "empty string")
            // (when src points directly at a byte c),
            // is delta_i == 1.
            printf("dest: [%s]; delta_i: %i \n", dest, delta_i ); // debug
            printf("literal: %.5s...; end-quote: %c\n", d+i, d[i+delta_i-1] ); // debug
            assert( quote == d[i+delta_i-1] );
            printf("start_output: [%s]\n", start_output ); // debug
            i += delta_i-1; // make d[i] refer to the end-quote
            dest += delta_i-1; // make dest point at the end-quote, so quote will be overwritten
            assert( quote == d[i] );
            assert( quote == dest[0] );
        };
#if 0
        int offset = get_i(d+i);
        int length = get_i(d+i);
        int literals = get_i(d+i);
#endif
#if 0
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

        // FUTURE: consider forward offsets from original start of dna string
        // rather than backward offsets from current position in output string.
        // FUTURE: consider using memccpy() ?
        // void *memcpy( void * dest, cost void * src, size_t n );
#define MIN_COPY_ITEM 6 /* FIXME: probably wrong */
        memcpy( dest, d+i-offset, length );
        i += MIN_COPY_ITEM; dest += length;
        memcpy( dest, d+i, literals );
        i += literals; dest += literals;
#endif
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
char dna[1000]=
// start with a teleomere of bytes we need that must be escaped
"\n\\"
// followed by an unnecessarily clever quote
"\""
// then more-or-less the text of the executable quine
// as a series of
// long literals with null copies (length=0 copies)
// zero-length literals with length-1 copies for the newlines and other "escaped" bytes
// The above are all that's necessary, but
// perhaps we'll occasionally "optimize"
// with longer copies or combined copy+literal or both.

" 2025-07-08: ANSI C quine by David Cary"
"A1Z"
"ZA1Z"
"#include <stdio.h>"
"ZA1Z" // literal newline required after #include
"extern char d[];"
"ZA1Z"
"int main(void){"
"ZA1Z"
"   ..."
"ZA1Z"
"    puts(start_output);"
"ZA1Z"
"}"
"ZA1Z"
"char d[1000]="
"ZA1Z"
"ZC1Z" // begin quote
// regenerate teleomere with a bunch of length=1 copies

// offset = +2, length = 1
// regenerate entire dna string with a length=strlen(d) copy
// regenerate ending quote with
// perhaps a length=1 copy of the quote, and a length=1 literal semicolon.
"ZC1Z" // end quote
";" // final semicolon
"ZA1Z" // final newline, with zero-length literal.
"Z"
"";



/* vim: set shiftwidth=4 expandtab visualbell ignorecase smartcase linebreak : */
