/**
LOW-LEVEL PROGRAMMING 第８章

制御の流れ ... 
if 文 
while 文
for 文
goto 文
switch 文

e.g. compile
```
gcc -o ../bin/main -std=c11 -pedantic-errors -Wall -Werror chapter_8.c
```
@author jack
*/
#include "stdio.h"

/**
    最初の約数を見つける。
    引数 n をを受取、1 より大きく n 以下の整数から、n を割り切れる最小の数 r を探す。
    因みにもし r = n ならそれは当然素数である。
*/
int first_divisor(int n) {
    int i;
    if(n == 1) return 1;
    for(i=2 ; i<=n; i++) {
        if(n%i==0) return i;
    }
    return 0;
}
int main(void) {
    // For 文
    if(8.33) {
        puts("For 文 ---------");  // 改行コードもいれてくれるのか：）
        for(int i=0; i<=10; i++) {  // このFor 文内での変数宣言は note: use option ‘-std=c99’, ‘-std=gnu99’, ‘-std=c11’ or ‘-std=gnu11’ to compile your code ということだ。
            if(i%2) {continue;}
            printf("%d は偶数です。 \n",i);
        }
    }
    // 例：約数
    if(8.36) {
        puts("約数 ---------");
        for(int i=1; i<11; i++) {
            printf("n is %d ... first divisor is %d\n",i,first_divisor(i));
        }
    }
    return 0;
}

