/**
    17.10 Intel 64 はどのくらい強いのか
    
        ゆるい（弱い）メモリモデルを持つ抽象マシンは、トレースするのが難しい。順序を入れ替えられた書き込み、
        未来からの戻り値、投機的な読み込みなど、本当に混乱する。Intel 64 のモデルは、普通は強いものと考えられる。
        ほとんどの場合、かなり多くの制約が満たされる保証がある。その一部を次にあげる。
        
    ```
    gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.10.c -o ../bin/main
    ```
*/
#include "pthread.h"
#include "semaphore.h"
#include "inttypes.h"
#include "time.h"
#include "stdio.h"
#include "stdlib.h"
#include "stdint.h"


sem_t sem_begin_0, sem_begin_1, sem_end;

int x, y, read_0, read_1;

void* worker_0(void* param) {
    for(;;) {
        sem_wait(&sem_begin_0);
        x = 1;
        // コンパイラによる並び替えだけを防ぐ
        __asm volatile("" ::: "memory");
        // 次のものは、ハードウェアによる並び替えも防ぐ（私の環境では、次のコメントアウトを外すと結果が変わった：）
//        __asm volatile("mfence" ::: "memory");
        read_0 = y;
        sem_post(&sem_end);
    }
    return NULL;
}

void* worker_1(void* param) {
    for(;;) {
        sem_wait(&sem_begin_1);
        y = 1;
        // コンパイラによる並び替えだけを防ぐ
        __asm volatile("" ::: "memory");
        // 次のものは、ハードウェアによる並び替えも防ぐ（私の環境では、次のコメントアウトを外すと結果が変わった：）
//        __asm volatile("mfence" ::: "memory");
        read_1 = x;
        sem_post(&sem_end);
    }
    return NULL;
}

int main(void) {
    puts("=== 17.10 Intel 64 はどのくらい強いのか");
    sem_init(&sem_begin_0, 0, 0);
    sem_init(&sem_begin_1, 0, 0);
    sem_init(&sem_end, 0, 0);
    
    pthread_t t_0, t_1;
    pthread_create(&t_0, NULL, worker_0, NULL);
    pthread_create(&t_1, NULL, worker_1, NULL);
    
    for(uint64_t i=0; i < 100000; i++) {
        x = 0;
        y = 0;
        
        sem_post(&sem_begin_0);
        sem_post(&sem_begin_1);
        sem_wait(&sem_end);
        sem_wait(&sem_end);
        if(read_0 == 0 && read_1 == 0) {
            printf("Reordering happened on iteration ... i is %"PRIu64"\n",i);
            exit(0);
        }
    }
    puts("No reordering detected during 100000 iterations.");   
    return 0;
}
