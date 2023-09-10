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
int first_v4(int array[10], size_t sz);
int first_v5(int array[static 10], size_t sz);
int main(void) {
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
                
                // C99 で導入された配列の面白い初期化方法の例
                puts("C99 で導入された配列の面白い初期化方法");
                int a[8] = {[1]=15,[5]=29}; // 要素数 1 は 15 で 要素数 5 は 29 で初期化され他は 0 で初期化される。
                for(int i=0; i<8; i++) {
                    printf("a[%d] is %d \n",i,a[i]);
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

