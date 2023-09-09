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

int main(void) {
    for(int i=0; i<=10; i++) {  // このFor 文内での変数宣言は note: use option ‘-std=c99’, ‘-std=gnu99’, ‘-std=c11’ or ‘-std=gnu11’ to compile your code ということだ。
        if(i%2) {continue;}
        printf("%d は偶数です。 \n",i);
    }
    return 0;
}

