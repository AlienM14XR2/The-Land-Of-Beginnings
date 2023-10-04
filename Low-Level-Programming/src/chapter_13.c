/**
        第１３章    良いコードをかくには
        
    ```
    gcc -c -std=c11 -pedantic-errors -Wall -Werror stack.c
    gcc -c -std=c11 -pedantic-errors -Wall -Werror chapter_13.c
    gcc -o ../bin/main chapter_13.o stack.o

    ```
*/
#include "stdio.h"
#include "malloc.h"
#include "stack.h"

int main(void) {
    puts("第１３章    良いコードをかくには");
    return 0;
}
