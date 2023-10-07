/**
        第１４章    変換処理の詳細
        
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_14.c -o ../bin/main
    ```

*/

#include "stdarg.h"
#include "setjmp.h"
#include "stdio.h"

#include "inc.h"

extern inline int inc(int x);   // @see inc.h

void printer(unsigned long argcount, ... ) {
    va_list args;
    unsigned long i;
    va_start(args, argcount);
    for(i=0; i < argcount; i++) {
        printf("%d\n", va_arg(args, int));
    }
    va_end(args);
}

int main(void) {
    puts("第１４章    変換処理の詳細 === ");
    if("14.1.5") {
        /**
                            標準ライブラリの一部として、可変引数リストを持つ関数宣言する
                            ポータブルな機構がある（それぞれのプラットフォームで、この機構を独自に実装している）。
                            
            stdarg.h をインクルードする。
            - va_list - 引数群の構造を格納する構造体。
            
            - va_start - va_list を初期化するマクロ。
            
            - va_end - va_list の初期化を終えるマクロ。
                        
            - va_arg - va_list と引数の型を受け取って、引数リストから次の引数を取り出すマクロ。
        */
        puts("--- 14.1.5 可変引数リスト");
        if("14-7") {
            printer(10, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0);
        }
    }
    if("14.2") {
        /**
            C の計算モデルはフォン・ノイマン型である。プログラムを並行して実行するためのサポートがない。
                            そしてコンパイラは通常、プログラムの振る舞いを目に見えて変えることなく、できるだけ多くの最適化を
                            試みる。けれども、volatile 変数の読み書きは、必ず発生する。演算の順序も変えずに維持される。
                            主なケースは次のものだ。
             - メモリマップトI/O 領域の読み書きで、外部デバイスとの通信を行うとき。たとえばビデオメモリに文字を書くのは、それが
                                スクリーンに表示されるのだから、意味がある。
                                
             - スレッド間のデータ共有。もし他のスレッドとの通信手段としてメモリを使うなら、
                                  そこでの読み書きは、決して省略されたくないはずだ。
             
                            もちろん、volatile にするだけでスレッド間の堅牢な通信を行えるわけではない。
                            ポインタの場合、const 修飾子と同じく volatile も、ポインタそのものだけでなく、それが指し示すデータにも適用することができる。
                            ルールも同じで、アスタリスクの左にある volatile は、ポインタが指すデータに作用し、右側にあればポインタそのものに作用する。
                            
            ```
            e.g.
            objdump -t ../bin/main
            ```
        */
        puts("--- 14.2 volatile 変数");
        puts("--- 14.2.1 遅延メモリ割り当て");
        if("14-11") {
            int ordinary = 0;
            volatile int vol = 4;
            ordinary++;
            vol++;
            printf("ordinary is %d\n",ordinary);
            printf("vol is %d\n",vol);
        }
        
    }
    if("14.3") {
        /**
                            非局所的なジャンプと setjmp
                            その例外
             - 外の世界に関係するもの（たとえばオープンしたファイルのディスクリプタ）
             - 浮動小数点のコンテクスト（状態フラグ）
             - ローカル変数の値
             
                             先コンテクストを保存しておき、後で戻りたくなったとき、そこに跳躍して戻ることが可能になる（ジャンプは同じスコープの関数に限定されない）。
             setjmp.h をインクルードすると、下記の機構を利用できる。
             - jmp_buf は、コンテクストを保存できる変数の型である。
             - int setjmp(jmp_buf env) は、jmp_buf のインスタンスを受け取り、その中に現在のコンテクストを保存する関数だ。デフォルトでは 0 を返す。
             - void longjmp(jmp_buf env, int val) は、jmp_buf 型の変数に保存されたコンテクストに戻るために使う。
             
             longjmp から本当に戻るときに setjmp が返すのは 0 とは限らず、longjmp に与えられた引数 val の値が返される。
             
            volatile と setjmp
            
                            正しくコーディングするために、次のことを覚えておこう。longjmp の後は、volatile ローカル変数だけが、定義した値を格納している。
                            元の値が書き戻されるわけではない、jmp_buf はスタックの変数を保存せず、longjmp までスタックに残っていた値が、そのまま使われるのだ。
                            
            ```
            gcc -O0 最適化なし
            gcc -O2 最適化あり
                                     
            gcc -O0 -std=c11 -pedantic-errors -Wall -Werror chapter_14.c -o ../bin/main
            gcc -O2 -std=c11 -pedantic-errors -Wall -Werror chapter_14.c -o ../bin/main
            ```
                            以下のサンプルは、コンパイルの最適化あり・なしによって結果がことなる ... はず。
            
        */
        if("14-15") {
            puts("--- 非局所的なジャンプと setjmp、volatile と setjmp");
            jmp_buf buf;
            if(1) {
                int var = 0;
                volatile int b = 0;
                setjmp(buf);
                if(b < 3) {
                    b++;
                    var++;
                    printf("var is %d\tb is %d\n",var,b);
                    longjmp(buf,1);
                }
            }
        }
    }
    if("14.4") {
        /**
            static を用いて C99 以前は関数のインライン化を行っていた。
                            具体的には、ヘッダファイルの宣言ではなく、関数の完全な定義を入れる際に、static 修飾を行う。
                            そのヘッダファイルを複数の変換単位にインクルードする。それぞれ生成されたコードのコピーを受け取るが、
                            対応するシンボルが「オブジェクトローカル」なので、リンカはそれらを衝突する複数定義とみなさない。
                            これなら、本当に関数をインライン化できる。
                            
                            コンパイラが、関数をインライン化しないと ... メモリ上のイメージだけでなく実行ファイルも膨張する。
             inline キーワードは、この問題に対処するためにある。
             
             @see inc.h
        */
        puts("--- inline 関数");
        printf("inc(8) is %d\n",inc(8));       
    }
    return 0;
}
