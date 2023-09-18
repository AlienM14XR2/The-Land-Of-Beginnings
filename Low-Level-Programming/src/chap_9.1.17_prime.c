/**
    9.1.17 課題：素数の判定
    
    数が素数がどうかをチェックする関数を書こう。
    この課題のポイントは、数を unsigned long 型にして、stdin から読むということだ。
  - int is_prime(unsigned long n) という関数を書くこと、これが、n という数が素数かどうかをチェックする、もし素数なら、この関数は 1 を返す。
        素数でなければ 0 を返す。
        
  - main 関数は、unsigned long 型の数を 1 つ読んで、それを引数として is_prime 関数を呼び出す。そして結果によって yes か no を出力する。
  
    まずは  man scanf を読もう。 scanf 関数を書く時に書式指定子は %lu を使うこと。 unsigned long を  is_prime は受け取るため。
  
  e.g. compile
  ```
  gcc -std=c11 -pedantic-errors -Wall -Werror chap_9.1.17_prime.c -o ../bin/main
  ```
    
  @author jack    
*/

#include "stdio.h"

int is_prime(const unsigned long n) {
    if(n == 0 || n == 1) {
        return 0;    // 素数ではないから。
    }
    unsigned long i = 0;
    int count = 0;
    for(i=2; i<=n; i++) {
        if(!(n%i)) {    // 余りなく割り切れた場合はカウンタをインクリメントする。
            count++;
        }
        if(count >= 2) {
            break;
        }
    }
    if( count == 1 ) {
        return 1;
    } else {
        return 0;
    }
}
int test_is_prime() {
    puts("test_is_prime ---------");
    unsigned long i = 0;
    int sum = 0;
    for(i=0; i<=100; i++) {
        int ret = is_prime(i);
        if(ret) {
            printf("%lu is prime.\n",i);
            sum++;
        } else {
            printf("%lu is not prime.\n",i);
        }
    }
    printf("sum is %d\n",sum);
    return 0;
}
int ptr_is_prime(const unsigned long* const n) {
    if(*n == 0 || *n == 1) {
        return 0;    // 素数ではないから。
    }
    unsigned long i = 0;
    int count = 0;
    for(i=2; i<=*n; i++) {
        if(!(*n%i)) {    // 余りなく割り切れた場合はカウンタをインクリメントする。
            count++;
        }
        if(count >= 2) {
            break;
        }
    }
    if( count == 1 ) {
        return 1;
    } else {
        return 0;
    }

}
int test_ptr_is_prime() {
    puts("test_ptr_is_prime ---------");
    unsigned long i = 0;
    int sum = 0;
    for(i=0; i<=100; i++) {
        int ret = ptr_is_prime(&i);
        if(ret) {
            printf("%lu is prime.\n",i);
            sum++;
        } else {
            printf("%lu is not prime.\n",i);
        }
    }
    printf("sum is %d\n",sum);
    return 0;
}
int main(void) {
    puts("9.1.17 課題：素数の判定 =========");
    test_is_prime();
    test_ptr_is_prime();
       
    unsigned long x = 0;
    printf("input number ... and enter.\n");
    scanf("%lu",&x);
    int ret = is_prime(x);
    if(ret) {
        printf("%lu is prime.\n",x);
    } else {
        printf("%lu is not prime.\n",x);
    }
    return 0;
}
