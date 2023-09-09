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

int main(void) {
    puts("第９章     型システム ===");
    return 0;
}

