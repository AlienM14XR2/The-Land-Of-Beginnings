/**
    9.2 タグのある型
    
    C には「タグのある」型が３つある。構造体と、共用体と、列挙型だ。このように呼ぶ理由は、
        それらの名前が、キーワード（struct か union か enum）の後に、名前で呼ぶためのタグを付けた形式になるからだ。
        
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_9.2.c -o ../bin/main
    ```
    
    @author jack
*/
#include "stdio.h"

int main(void) {
    puts("9.2 タグのある型 （struct, union, enum）=========");
    return 0;
}
