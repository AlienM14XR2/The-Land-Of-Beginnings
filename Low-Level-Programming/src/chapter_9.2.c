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
    if("9.2.1") {
        puts("9.2.1 構造体 ------");
        // タグという概念
        struct pair {
            int a;
            int b;
        };
        
        struct pair d;  // pair は単なるタグであり、 struct pair ではじめてコンパイラに正しく認識される。
        d.a = 0;
        d.b = 1;
        printf("d.a is %d\n",d.a);
        printf("d.b is %d\n",d.b);
        if("9-40") {
            puts("9-40 ---");
            /**
                                    それぞれ struct type と type という型の２つの変数を、コンパイラが完全に受け入れることを示すデモンストレーションだ。
            */
            typedef unsigned int type;
            struct type {
                char c;
            };
            struct type st;
            st.c = 'A';
            type t = 33;
            printf("st.c is %c ... %d\n",st.c,st.c);
            printf("t is %d\n",t);
            /**
                                    構造体を typedef を使って別名を付けるのは、良いことではない。
                                    なぜなら、それは型の性質を隠すことになるからだ。（書籍ではこのように言っていた：）
                                    これは、個人的には何とも言えない。ソースで実際に書いてみれば分かるが、結局その変数がなんなのかということは
                                    読み込む必要があり、struct tag名だろうと、typedef struct {} FOO; だろうと大差はないと思っている。 
            */
            
            // ちょっとだけポインタに関して復習だ。
            // 次をコンパイルし実行ファイルを作るには、コンパイル/オプションを変更してやる必要がある。
            // e.g. gcc -std=c11 -Wall chapter_9.2.c -o ../bin/main
            if(1) {
                const int foo = 100;
// NG ただしコンパイルオプション次第です。                int* const pf = &foo;
//                *pf = 101;
                printf("foo is %d\n",foo);
            }
            if(2) {
                int y = 42;
                int z = 84;
                const int* pg = &y;
// NG                *pg = 420;
                pg = &z;    // OK
                printf("*pg value is %d\n",*pg);
            }
            if(3) {
                int y = 42;
                int z = 3;
                printf("z value is %d\n",z);
                int* const pg = &y;
// NG                pg = &z;
                *pg = 333;  // OK
                printf("*pg value is %d\n",*pg);
                
            }
            
        }
    }
    return 0;
}
