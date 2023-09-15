/**
    第９章     型システム
    型（type）の認識は、重要な鍵となる概念の１つだ。型の本質は、データエントリに結びつけられた標識である。
    個々のデータ型について、あらゆるデータ変換か定義され、正しく変換されることが保証されている（ただし「サハラ砂漠の正午の平均気温」に
    「アクティブな Reddit ユーザ数」を加算しようとは誰も思わない。意味がないのだから）。
    
    この章では C の型システムを詳しく学ぶ。  
  e.g. compile
  ```
  gcc -o ../bin/main -std=c11 -pedantic-errors -Wall -Werror chapter_9.c
  ```
    
  @author jack   
*/

#include "stdio.h"
#include "stdbool.h"

int first(int array[], size_t sz);
int first_v2(int* array, size_t sz);
int first_v3(int* array, size_t sz);
int first_v4(int array[10], size_t sz);         // これは意味なし、ただのコメントに過ぎない。
int first_v5(int array[static 10], size_t sz);  // これは意味あり、要素数 10 というようにコンパイラが解釈する。
void sub_test_sizeof(int const arr[]);

int main(int argc, char* argv[]) {  // @see 9.1.10 main 関数の引数
    puts("第９章     型システム ===");
    if(9) {
        if(1) {
            if(1) { // 9.1.1 数値型
                puts("数値型 ---------");
                // 2 の 48 乗
                printf("1L << 48 is %ld \n",(1L << 48));    // これは int 型で 8 Bytes という解釈がされる。
               // printf("1 << 48 is %d \n",(1 << 48));  // これは int 型で 4 Bytes という解釈がされる。（コンパイルエラー ... コンパイルオプション '-Werror'。）
               
               // long double 浮動小数点数。サイズは通常 80 ビット。 C99 ではじめて標準に入った。
               long double pai = 3.141592;               
               printf("pai is %Lf \n",pai);    // Lf なんだね。
               // 次のアドレスを表示させるものはコンパイルエラーになった .... '%p' expects void* but long double*
               // void* でキャストしたらコンパイルは通った。
               printf("pai address is %p \n",(void*)&pai);
               printf("sizeof(pai) is %ld \n", sizeof(pai));    // sizeof(x) ... long unsigned int
            }
            if(2) { // 9.1.2
                /*
                    C は型キャスト（型変換）を比較的自由に行うことができる。
                                            そのためには、新しい型の名前をカッコに入れて、変換したい式の前に書く必要がある。
                */
                puts("型キャスト ---------");
                int a = 4;
                double b = 10.5 * (double)a;
                printf("a is %d \n",a);
                printf("b ... (10.5 * (double)a) is %lf \n",b);
                // いけないことしてる。
                int c = 129;
                char k = (char)c;   // ???
                printf("k is ... %d \n",k);
                /*
                                            通常の char は、範囲が -128 から 127 までの符号付き整数であって、129 という
                                            数は大きすぎて、この範囲に収まらない。C 言語の標準に記述されていないが、典型的なプロセッサとコンパイラの機能を思えば、たぶん結果は 129 の
                                            符号なし表現と同じビットで構成される「負の数」になるだろう。
                */
            }
            if(3) { // 9.1.3
                /*
                    C89 にブール型がないことは、すでに指摘した。けれども C99 でブール型が、_Bool という型名で導入された。stdbool.h をインクルードすれば true false の値と、
                    bool という型をアクセスできるようになる... 中略 ... 極力 _Bool ではなく bool を使おう。
                */
                puts("ブール型 ---------");
                bool bflg = true;
                if(bflg) {
                    puts("you should include stdbool.h");
                }
            }
            if(5) { // 9.1.5
                /*
                                            ポインタ
                                            ここでは void* とデリファレンスについて学んだ。int* であれば そのポインタの参照先のデータの型は、int であることは自明といえる。
                                            確かに、void* だった場合、デリファレンスは困難、自明とはいかない。
                                           
                */
                puts("ポインタ ---------");
                int a = 10;
                void* pa = &a;
                // このようなことが事前に分かっていたら次のように書ける。
                printf("pa is %d \n",*((int*)pa));
            }
            if(6) { // 9.1.6
                /*
                                            配列
                   C の配列（array）は、固定数の同じ型のデータを入れる構造だ。だから配列を扱う上で知る必要があるのは、その先頭アドレスと、１個の要素サイズと、配列の長さ
                                        （格納できる要素の上限）である。配列宣言を２つ、次に示す。
                                            
                */
                puts("配列 ---------");
                int arr[] = {1,2,3,4,5};   // この配列のサイズはコンパイラによって計算される。
                long size = sizeof(arr)/sizeof(arr[0]);
                printf("size is %ld \n",size);
                for(int i=0; i<size; i++) {
                    printf("arr[%d] is %d \n",i,arr[i]);
                }
                
                long array[32] = {0};   // この配列は 0 で初期化される。全体のサイズは 256 バイト（8 * 32）。
                for(int i=0; i<32; i++) {
                    printf("array[%d] is %ld \n",i,array[i]);
                }
            }
            if(7) { // 9.1.7
                /*
                                            関数の引数としての配列
                                            配列を引数として受け取る関数について考えてみよう。
                                            配列の最初の要素を返す（もし配列が空ならば、-1 を返す）。
                */
                puts("関数の引数としての配列 ---------");
                int arr[] = {1,2,3,4,5,6};
                // size_t これは  aka long unsigned int 
                size_t sz = sizeof(arr)/sizeof(arr[0]);    // この記述は配列のサイズが決定している場合のみ有効。
                printf("sz is %ld \n",sz);
                int ret = first(arr,sz);
                printf("ret is %d \n",ret);
                ret = first_v2(arr,sz);
                printf("ret is %d \n",ret);
                ret = first_v3(arr,sz);
                printf("ret is %d \n",ret);
                
                int arr2[] = {10,20,30,40,50,60,70,80,90,100};
                sz = sizeof(arr2)/sizeof(arr2[0]);
                printf("sz is %ld \n",sz);
                puts("関数定義において無意味な例");
                ret = first_v4(arr2,sz);    // この関数定義は無意味だということ。
                printf("ret is %d \n",ret);
                puts("関数定義において意味あり");
                ret = first_v5(arr2,sz);    // C99 で導入された配列の範囲を規定したもの。
                printf("ret is %d \n",ret);
                
            }
            if(8) { // 9.1.8
                // C99 で導入された配列の面白い初期化方法の例
                puts("C99 で導入された配列の面白い初期化方法");
                int a[8] = {[1]=15,[5]=29}; // 要素数 1 は 15 で 要素数 5 は 29 で初期化され他は 0 で初期化される。
                for(int i=0; i<8; i++) {
                    printf("a[%d] is %d \n",i,a[i]);
                }
                
                // 配列の初期化の順序は意味を持たない。これは列挙値やキャラクタの値をインデックスとして使うときに便利。
                int whitespace[32+1] = {
                    [' ' ] = 1,
                    ['\t'] = 2,
                    ['\f'] = 3,
                    ['\n'] = 4,
                    ['\r'] = 5
                };
                for(int i=0; i<33; i++) {
                    printf("whitespace[%d] is %d \n",i,whitespace[i]);
                }
                puts("--- colors");
                enum colors {
                    RED,
                    GREEN,
                    BLUE,
                    MAGENTA,
                    YELLOW
                };
                
                int good[5] = {[RED]=1,[MAGENTA]=4};
                printf("good[RED] is %d \n",good[RED]);
                printf("good[MAGENTA] is %d \n",good[MAGENTA]);
            }
            if(9) { // 9.1.9 型の別名
                puts("型の別名");
                typedef unsigned short int mytype_t;   // _t で終わる名前は、すべて POSIX 標準によって予約されているためいい名前とは言えない
                mytype_t a = 65535;
                printf("a is %d \n",a);
                // size_t ... unsigned long の別名なので、Intel 64 では符号なし 8 バイトの整数になるのが典型である。
                // 配列のインデックスにはこれを利用し、int を使用すべきではない。書籍の中ではもっと激しい言い方だった『配列のインデックスに int を使うな！』。
                // 私はインクルードしてはいないが、stddef.h などの標準ライブラリをインクルードして利用する場合もある。
            }
            if(10) {    // 9.1.10 main 関数の引数
                puts("main 関数の引数");
                // 実行時に与えられた全部の引数を、それぞれ別の行でプリントする。
                int i;  // 前の項目で size_t を使えと言っときながら、ここでは int を使っている本書が少し面白い：） つまりはその常識的な範疇で判断せよってことかな。
                for(i=0; i<argc; i++) {
                    puts(argv[i]);
                }
            }
            if(11) {    // 9.1.11 sizeof 演算子
                puts("sizeof 演算子");
                long array[] = {1,2,3};
                // 配列の全体のサイズを求めることができる。
                // 書式指定子 %zu これ知らなかった。C99 から size_t のために %zu という指定子が使えるようになった。
                // それより前のバージョンでは unsigned long を意味する %lu を使うべきである。
                printf("array is %zu \n",sizeof(array));
                // 配列の一個のサイズを求めることもできる。
                printf("arra[0] is %lu \n",sizeof(array[0]));
                
                // 次の問題は経験則から知っていたこと。関数の仮引数では上記と同様のことはできない ... ポインタは全部同じサイズにしかならない。
                // gcc -o ../bin/main -std=c11 -pedantic-errors -Wall -Werror chapter_9.c
                // warning も error になるのでこれを確認するためにはコンパイルオプションを変更しないとできない。次のようにコンパイルオプションを変更した。
                // gcc -o ../bin/main -std=c11 -pedantic-errors -Wall chapter_9.c
                const int arr[] = {1,2,3,4};
                sub_test_sizeof(arr);
                
                /**
                                            課題
                    sizeof(void) を調べる。
                    void は調べられなかった、コンパイルエラー。
                */
                printf("sizeof(void*) is %zu \n",sizeof(void*));
                /**
                                            課題
                    sizeof(0) を調べる。
                */
                printf("sizeof(0) is %zu \n",sizeof(0));
                /**
                                            課題
                    sizeof('X') を調べる。
                */
                printf("sizeof('X') is %zu \n",sizeof('X'));
                printf("sizeof('x') is %zu \n",sizeof('x'));
                /**
                                            課題
                    x の値はどうなるだろうか ... int だから 4 だと思う。
                    int x = 10;
                    size_t t = sizeof(x=90);
                */
                if(160) {
                    int x = 10;
                    size_t t = sizeof(x=90);
                    printf("t is %zu \n", t);
                }
                /**
                                            課題
                                            配列に含まれている要素の数を、 sizeof を使って計算する方法は？
                                            はい、これも経験則で知っている。
                */
                if(161) {
                    int array[] = {1,2,3,4,5,6,7,8,9,10};
                    size_t sz = sizeof(array)/sizeof(array[0]);
                    printf("array size is %zu \n",sz);
                }
                
            }
            if(11) {    // 9.1.12 定数型
                puts("9.1.12 定数型 ========= ");
                if("9-20") {
                    puts("9-20 --- ");
                    int a;  // 宣言だけして初期化はなし。
                    a = 42; // ここで代入している。これは問題なし、OK。
                    printf("a is %d \n",a);
                    // const int b // これはコンパイルエラーになる。定数は、必ず初期化する必要がある。
                    
                    const int c = 36;
                    // c = 99;        // コンパイルエラー、定数は変更できない。
                    printf("c is %d \n",c);
                    
                    // const int === int const
                    const int d = 33;   // 私はこっちが好きだし、見慣れている。
                    int const f = 66;
                    printf("d is %d \n",d);
                    printf("f is %d \n",f);
                    
                    /**
                                                    この const という修飾子とアスタリスク（*）修飾子との関係は、注目に値する。
                                                    型は右から左に向けて読む規則があるので、const 修飾子も、アスタリスクも、この順序で適用される。
                                                    その選択肢をあげる。
                                                    
                       int const* x は、「変更不可能」な int への、変更可能なポインタ x という意味だ。
                                                    したがって、 *x = 10 は許されないが、 x そのものの変更は許される。代替の構文は、const int* x である。
                                                        
                    */
                    int g = 9;
                    int h = 10;
                    const int* pg = &g;
                    printf("*pg value is \t %d address is \t %p \n",*pg,(void*)pg);
                    printf("g value is   \t %d address is \t %p \n",g,(void*)&g);
                    // *pg = 10;    // コンパイルエラーになる。
                    pg = &h;        // これは問題ない、OK。
                    printf("*pg value is \t %d address is \t %p \n",*pg,(void*)pg);
                    printf("h value is   \t %d address is \t %p \n",h,(void*)&h);
                    
                    /**
                        int* const x = &y; の x は、「変更可能な  int y への、変更不可能なポインタ」である。
                                                       言い換えると、x は y 以外のものを指し示すことができない。
                    */
                    if(1) {
                        int y = 300;
                        int yy = 600;
                        int* const x = &y;
                        printf("*x value is \t %d address is \t %p \n",*x,(void*)x);
                        // x = &yy;    // コンパイルエラーになる。
                        *x = 301;      // これは問題なし、OK。
                        printf("*x value is \t %d address is \t %p \n",*x,(void*)x);
                    }                    
                    /**
                                                    上 2 つのケースを重ねた、int const* const x = &y; は、「変更不可能な int y への、変更不可能なポインタ」を作る。
                    */
                    if(1) {
                        int y = 303;
                        int yy = 606;
                        // この書き方のほうが好きなんだけど。
                        const int* const x = &y;
                        printf("*x value is \t %d address is \t %p \n",*x,(void*)x);               
                        // x = &yy;    // コンパイルエラーになる。
                        // *x = 304;   // コンパイルエラーになる。
                        
                    }   
                }
                /**
                                            単純なルール
                    const が * の左にあれば、そのポインタが指すデータが保証される。
                    * の右に const があれば、そのポインタが保証される。
                    
                                            変数を const で修飾しても、絶対安全ではない。それを変更する方法はあるのだ。
                    const int x という変数について、それを示す。
                    - それを指すポインタを作る、その型は、const int* となる。
                    - このポインタを、int* にキャストする。
                    - 新しいポインタをデリファレンスする。これで新しい値を x に代入できる。
                */
                if("9-21") {
                    puts("9-21 --- ");
                    const int x = 10;
                    printf("befor x value is %d \n",x);
                    // Dereference
                    *((int*)&x) = 30;
                    printf("after x value is %d \n",x);
                }
            }
        }
    }
    return 0;
}
/*
    配列の最初の要素を返す（もし配列が空ならば、-1 を返す）。
*/
int first(int array[], size_t sz) {
    if(sz == 0) return -1;
    return array[0];
}

/*
    配列の最初の要素を返す（もし配列が空ならば、-1 を返す）。
    上の関数の第１仮引数をポインタで表現しただけ、振る舞いは同じ。
*/
int first_v2(int* array, size_t sz) {
    if(sz == 0) return -1;
    return *array;
}
/*
    配列の最初の要素を返す（もし配列が空ならば、-1 を返す）。
    上の関数の第１仮引数をポインタで表現しただけ、振る舞いは同じ。
  first 関数と first_v2 関数の混在させたもの。
    配列は内部でポインタを利用した特殊な型とも言える。
*/
int first_v3(int* array, size_t sz) {
    if(sz == 0) return -1;
    return array[0];
}
/*
        そもそも配列は、実行時にもコンパイル時にも、範囲チェックを実行しない。（バッファオーバーフロー）
        次の関数の記述は単なるコメントに過ぎない。
*/
int first_v4(int array[10], size_t sz) {
    if(sz == 0) return -1;
    return array[0];
}
/*
    C99 で導入された特別な構文を利用したもの。
        このように記述すると、コンパイラは、その約束を前提とした特別な最適化を実行できるようになる。  
*/
int first_v5(int array[static 10], size_t sz) {
    if(sz == 0) return 0;
    return array[0];
}
/*
        関数が仮引数として受け取った配列のサイズを sizeof 演算子を用いて求めることは
        できないという例題サンプル。
*/
void sub_test_sizeof(int const arr[]) {
    printf("arr is %zu \n",sizeof(arr));        // 64 ビット機では 8 が出力される。
    printf("arr[0] is %zu \n",sizeof(arr[0]));  // 4 が出力される。
}

