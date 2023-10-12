/**
    17.8.4 例：約数の個数を分散処理で求める
    ```
    gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.8.4.c -o ../bin/main
    ```
*/
#include "pthread.h"
#include "unistd.h"
#include "inttypes.h"
#include "stdio.h"
#include "malloc.h"

#define THREADS    8

/*
uint64_t factors(uint64_t num) {
    uint64_t result = 0;
    for(uint64_t i = 0; i <= num; i++) {
        if(num % i == 0) {
            result++;
        }
    }
    return result;
}
*/

struct fact_task {
    uint64_t num;
    uint64_t from, to;
    uint64_t result;
};

void* fact_worker(void* arg){
    struct fact_task* const task = arg;
    task->result = 0;
    for(uint64_t i=task->from; i < task->to; i++) {
        if(task->num % i == 0) {
            task->result++;
        }
    }
    return NULL;
}
// thread_num < num を前提とする。
uint64_t factors_mp(uint64_t num, size_t thread_count) {
    struct fact_task* tasks = malloc(thread_count*sizeof(*tasks));
    pthread_t* threads = malloc(thread_count*sizeof(*threads));
    
    uint64_t start = 1;
    size_t step = num / thread_count;
    
    for(size_t i=0; i < thread_count; i++) {
        tasks[i].num = num;
        tasks[i].from = start;
        tasks[i].to = start + step;
        start += step;
    }
    tasks[thread_count-1].to = num+1;
    
    for(size_t i=0; i < thread_count; i++) {
        pthread_create(threads + i, NULL, fact_worker, tasks + i);
    }
    
    uint64_t result = 0;
    for(size_t i=0; i < thread_count; i++) {
        pthread_join(threads[i], NULL);
        result += tasks[i].result;
    }
    
    free(tasks);
    free(threads);
    return result;
}

int main(void) {
    /**
                実行時間をテストする、time ユーティリティ（シェルのビルトインコマンドではないほ方）を使う。
                シェルのビルトインではなく、必ずそのプログラムが実行されるように、頭にバックスラッシュを 1 個付けておく。
        ```
        gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.8.4.c -o ../bin/main && \time ../bin/main
        ```
    */
    puts("例：約数の個数を分散処理で求める");
    uint64_t input = 2000000000;
    printf("Factors of %"PRIu64" : %"PRIu64"\n",input,factors_mp(input,THREADS));
    return 0;
}

