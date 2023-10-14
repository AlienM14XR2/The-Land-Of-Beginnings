/**
    17.9    セマフォ
    
        セマフォは、共有される整数型のカウンタ変数で、次の３つの演算を実行できる。
        
    init：初期化する。引数 N を取り、値を N にセットする。
    wait（enter）：もし値がゼロでなければデクリメントする、ゼロなら、誰かがインクリメントするまで待ってから、デクリメントする。
    post（leave）：値をインクリメントする。
    
    ```
    gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.9.c -o ../bin/main
    ```
*/
#include "semaphore.h"
#include "pthread.h"
#include "inttypes.h"
#include "unistd.h"
#include "stdio.h"


sem_t sem;

uint64_t counter1;
uint64_t counter2;

pthread_t t1, t2, t3;

void* t1_worker(void* _) {
    while(counter1 < 10000000) {
        counter1++;
    }
    sem_post(&sem);
    return NULL;
}

void* t2_worker(void* _) {
    while(counter2 < 20000000) {
        counter2++;
    }
    sem_post(&sem);
    return NULL;
}

void* t3_worker(void* _) {
    sem_wait(&sem);
    sem_wait(&sem);
    printf("End: counter1 is %"PRIu64"\tcounter2 is %"PRIu64"\n",counter1,counter2);
    return NULL;
}

int main(void) {
    puts("17.9\tセマフォ");
    
    sem_init(&sem, 0, 0);
    pthread_create(&t3, NULL, t3_worker, NULL);
    sleep(1);
    
    pthread_create(&t1, NULL, t1_worker, NULL);
    pthread_create(&t2, NULL, t2_worker, NULL);
    
    sem_destroy(&sem);
    pthread_exit(NULL);
    
    return 0;
}

