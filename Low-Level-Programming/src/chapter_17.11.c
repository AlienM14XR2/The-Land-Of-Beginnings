/**
    17.11   ロックしないプログラミングとは
    
    CAS 命令はアトミックな命令シーケンスとしての役割を果たす。これと等価な機能をC の
        関数で書くと次のようになる。
    
    ```
    gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.11.c -o ../bin/main
    ```
*/
#include "pthread.h"
#include "stdbool.h"
#include "stdio.h"

bool cas(int* p, int old, int new) {
    if(*p != old) {
        return false;
    }
    *p = new;
    return true;
}

int add(int* p, int add) {
    bool done = false;
    int value;
    while(!done) {
        value = *p;
        done = cas(p, value, value+add);
    }
    return value + add;
}

int main(void) {
    puts("17.11\tロックしないプログラミングとは");
    int n = 0;
    int* pn = &n;
    printf("add(pn,1) is %d\n",add(pn,1));
    printf("add(pn,1) is %d\n",add(pn,1));
    return 0;
}
