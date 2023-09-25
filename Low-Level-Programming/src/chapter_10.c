/**
        第１０章
        コードの構造
        
        宣言と定義
        
        相互再帰する定義の解決として、宣言と定義を分ける。
        定義より前に置いた宣言を前方宣言と呼ぶ（確かにこれはたまに、使う）。
        
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_10.c -o ../bin/main
    ```
    @author jack
*/
#include "stdio.h"

// グローバル変数 z の宣言と初期化
int z = 10;         // @see square.c

/* これが関数の宣言、このような宣言は、ときに関数プロトタイプとも呼ばれる */
int foo(int x);     // この仮引数は省略できたはず。
int bar(int,int);   
int square(int);    // @see square.c
int square_v2(int);    // @see square.c

int main(void) {
    // この章はサンプルをとることはあまりないかもしれないが、念の為用意した。
    // どちらかといえば、実践内容をメモすることになりそう。
    if("10.1") {
        puts("10.1 宣言と定義 =========");
        foo(16);
        printf("bar(3,6) is %d\n",bar(3,6));
    }
    /**
                再帰的なデータ構造を定義するのは、ごく一般的なことだ。連結リストの場合、それぞれの要素には、
                値とともに次の要素へのリンクが格納される。最後の要素では、有効なポインタ代わりに NULL を入れて、リストの終端
                を示すマークとする。
                けれども、相互再帰する２つの構造体の場合、少なくとも片方について、前方宣言を追加する必要がある。
    */
    if("10.1.2 構造体宣言") {
        puts("10.1.2 構造体宣言 =========");
        if("10-9 相互再帰する構造体") {
            struct b;    // 前方宣言
            struct a {
                int value;
                struct b* next;
            };
            
            struct b {
                struct a* other;    // struct a はすでに定義されているので、前方宣言は不要。
            };
        }
    }
    if("10.2 他のファイルのコードをアクセスする") {
        if("10.2.1 他のファイルの関数") {
            /**
                square.c を利用する。
                @see square.c
                ```
                gcc -c -std=c11 -pedantic -Wall -Werror chapter_10.c
                objdump -t chapter_10.o
                
                gcc -c -std=c11 -pedantic -Wall -Werror square.c
                objdump -t square.o
                
                gcc -o ../bin/main chapter_10.o square.o
                objdump -t ../bin/main
                ```
            */
            puts("10.2.1 他のファイルの関数 =========");
            printf("square(3) is %d\n",square(3));
        }
        if("10.2.2 他のファイルのデータ") {
            /**
                ```
                gcc -c -std=c11 -pedantic -Wall -Werror chapter_10.c
                gcc -c -std=c11 -pedantic -Wall -Werror square.c
                gcc -o ../bin/main chapter_10.o square.o
                ```
            */
            puts("10.2.2 他のファイルのデータ =========");
            printf("square_v2(3) is %d\n",square_v2(3));
        }
    }
    return 0;
}

/* これが関数の定義 */
int foo(int x) {
    printf("x is %d\t%x\n",x,x);
    return 0;
}
int bar(int x, int y) {
    return x*y;
}

