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
            
            puts("ポインタと const 修飾の復習 ---");
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
        /**
                            構造体は、配列と同じように初期化できる。
        */
        if("9-42") {
            puts("9-42 構造体の初期化 ---");
            struct PERSON {
                const char* const name;
                int age;
            };
            struct PERSON person = {"Jack",14};
            printf("name is %s\tage is %d\n",person.name,person.age);
        }
         /**
                            構造体の全部のフィールドに 0 を代入できる。
        */
        if("9-43") {
            puts("9-43 構造体のフィールドに 0 を代入 ---");
            struct pair {
                int a;
                int b;
            };
            struct pair p = {0};
            printf("a is %d\tb is %d\n",p.a,p.b);
        }
         /**
                            構造体の初期化 ... C99 で追加された、指定フィールドの初期化（指定フィールド以外は 0 で初期化される）。
        */
        if("9-44") {
            puts("9-44 C99 で追加された、指定フィールドの初期化（指定フィールド以外は 0 で初期化される） ---");
            struct pair {
                char a;
                char b;
            };
            struct pair p = {.a='A'};
            printf("a is %c\tb is %d\n",p.a,p.b);
        }
        /**
                            共用体（union）は、構造体とよく似ているが、フィールドが必ず重複する（構造体は、フィールドが重複しない）。
                            言い換えると、共用体のすべてのフィールドは同じアドレスから始まるのだ。共用体の名前空間は構造体および列挙型と共通している。
        */
        puts("9.2.2 共用体 ---------");
        if("9-45") {
            puts("9-45 ---");
            union dword {
                int integer;
                short shorts[2];
            };
            union dword test;
            test.integer = 0xAABBCCDD;
            /**
                                    今定義した共用体は、（x86 または x64 アーキテクチャで）サイズが 4 バイトとなる数を格納する。
                                    そのデータは、２つの数（それぞれ２バイト幅）からなる配列にも、同時に格納される。
                                    つまり、２つのフィールド（４バイトの.integer と ２バイト x２の.shorts 配列）は、重複する。
                                    前者を変更すれば、後者も変更される。
            */
            printf("integer is %x\tshorts[0] is %x\tshorts[1] is %x\n",test.integer,test.shorts[0],test.shorts[1]); // リトルエンディアン：データをバイト単位で配置する際のやり方のひとつで「最後のバイトからデータを並べる」やり方
        }
        if("9-46") {
            puts("9-46 ---");
            /**
                                    構造体と共用体を組み合わせると面白い結果が得られる。
                                    次の例は、３バイトの構造体の各部をインデックス参照する方法を示している。
                                    ただし、型のサイズによっては、構造体のフィールド間に生じるギャップのせいで、うまく
                                    いかない可能性がある。
            */
            union pixel {
                struct {
                    char a,b,c;
                };
                char at[3];
            };
            union pixel pix = {.a=2,.b=4,.c=6};
            printf("a is %d\tb is %d\t c is %d\n",pix.a,pix.b,pix.c);
            for(int i=0; i<3; i++) {
                printf("at[%d] is %d\n",i,pix.at[i]);
            }
        }
        if("9-47") {
            puts("9-47 ---");
            /**
                                    一般に、共用体のどれかのフィールドに値を代入したら、他のフィールドの値について標準は何も保証しない。
                                    ただし、どちらも同じフィールドシーケンスを先頭に持つ２つの構造体ならば例外である。
            */
            struct sa {
                int x;
                char y;
                char z;
            };
            struct sb {
                int x;
                char y;
                int notz;
            };
            union test {
                struct sa as_sa;
                struct sb as_sb;
            };
            union test t = {.as_sa={300,1,2}};
            printf("as_sa.x is %d\tas_sa.y is %d\tas_sa.z is %d\n",t.as_sa.x,t.as_sa.y,t.as_sa.z);
            printf("as_sb.x is %d\tas_sb.y is %d\tas_sb.notz is %d\n",t.as_sb.x,t.as_sb.y,t.as_sb.notz);
        }
        /**
            C11 から、共用体と構造体は、他の構造体または共用体の内側にあるとき、名前（タグ）をつけないことが許されるようになった。
                          これによって、内側のフィールドにアクセスする構文を短くすることができる。
        */
        puts("9.2.3 無名の構造体・共用体 ---------");
        if("9-48") {
            puts("9-48 ---");
            // C11 より前の書き方
            union vec3d {
                struct {
                    double x;
                    double y;
                    double z;
                } named;    // named というタグが必要、またこの位置にないとコンパイル・エラーになった。
            };
            union vec3d vec = {.named={10.0,20.0,30.0}};
            printf("x is %lf\ty is %lf\t z is %lf\n",vec.named.x,vec.named.y,vec.named.z);
        }
        if("9-49") {
            puts("9-49 ---");
            // C11 から許可された書き方、内側の struct のタグの記述がない。
            union vec3d {
                struct {
                    double x;
                    double y;
                    double z;
                };
                double row[3];
            };
            union vec3d vec = {.x=10.0,.y=20.0,.z=30.0};
            printf("x is %lf\ty is %lf\t z is %lf\n",vec.x,vec.y,vec.z);
            size_t sz = sizeof(vec.row)/sizeof(vec.row[0]);
            unsigned long i = 0;
            for(i=0; i < sz; i++) {
                printf("vec.row[%lu] is %lf\n",i,vec.row[i]);
            }
        }

   }
    return 0;
}
