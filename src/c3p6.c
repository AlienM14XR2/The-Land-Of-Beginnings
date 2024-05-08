/**
 * パターンの学習
 * 
 * gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror c3p6.c -o ../bin/main
*/
#include "stdio.h"
#include "stdlib.h"

/**
 * アルファベットと数字の種類は
 * アルファベット（26）数字（10）の 36 種類、これは小文字のみ。
 * アルファベット、大文字小文字（52）数字（10）の 62 種類
 * 最初は小文字のみで考えてみる。
*/

void nine_nine() {
    for(int i=1; i<=9; i++) {
        for(int j=1; j<=9; j++) {
            printf("%d\t", i*j);
        }
        printf("\n");
    }
}

/**
 * 疑問：アルファベット（小文字のみ）と数値の全パターンの計算にどれくらいかかるのか？
*/

void ptn_alpha_numeric() {
    puts("--- ptn_alpha_numeric");
    /**
     * アスキーコードを利用した方がいいかな。
     * 並び順は忘れた：）
     * https://webtools-oasis.com/ascii-table
     * 10 進数の 48 が  '0'
     * 10 進数の 57 が  '9'
     * 10 進数の 97 が  'a'
     * 10 進数の 122 が 'z'
    */

    int kind[36] = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
                97,  98,  99,  100, 101, 102, 103,
                104, 105, 106, 107, 108, 109, 110,
                111, 112, 113, 114, 115, 116, 117,
                118, 119, 120, 121, 122 };
    for(int i=0; i<36; i++) {
        printf("%c\t", kind[i]);
    }
    printf("\n");
    puts("上記が今回利用する要素。");
    /**
     * 私のマシンでは最後まで実行できなかった。
     * 次の処理をログに出力するかたちで実行したが i が 0 と ｊ が 4、 k が l、l が k 
     * という序盤の状態で 150 G ディスクを消費していたことは明記しておく（70 G は開始前から消費済：）
     * つまり、何も考えずに無邪気に巨大な計算をしてはいけないということ。
    */
    for(int i=0; i<36; i++) {
        for(int j=0; j<36; j++) {
            for(int k=0; k<36; k++) {
                for(int l=0; l<36; l++) {
                    for(int m=0; m<36; m++) {
                        for(int n=0; n<36; n++) {
                            for(int o=0; o<36; o++) {
                                for(int p=0; p<36; p++) {
                                    printf("%c\t%c\t%c\t%c\t%c\t%c\t%c\t%c\n",kind[i], kind[j], kind[k], kind[l], kind[m], kind[n], kind[o], kind[p]);
                                }
                            }
                        }
                    }
                }
            }
        }
    }
    printf("\n");
}

int main(void) {
    puts("START パターンの学習 ===");
    if(1.00) {
        nine_nine();    
    }
    if(1.01) {
        ptn_alpha_numeric();
    }
    puts("=== パターンの学習   END");
}