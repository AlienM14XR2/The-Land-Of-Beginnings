/**
        第１４章    変換処理の詳細
        
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_14.c -o ../bin/main
    ```

*/

#include "stdarg.h"
#include "stdio.h"

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
    return 0;
}
