

/*
embed_quine.c
2025-07-27: started by David Cary.

Uses the C23 "#embed" directive.
which DAV first heard of via
"What is C23 and why should I care?"
https://software.codidact.com/posts/289414
and later DAV read the somewhat humorous description at
https://thephd.dev/finally-embed-in-c23#actual-real-touchable-non-electronic-mail

According to
https://gcc.gnu.org/projects/c-status.html
, C23 mode is the default since GCC 15.
*/

#include <stdio.h> // for printf()

char source_code[] = {
    #embed "embed_quine.c"
    , 0 // add a null terminator
};

int main(void){
    printf("%s", source_code);
};

