/**
    17.8.5 ミューテックス
    
    ```
    // -O0 でコンパイラによる最適化が行われなくなる。
    gcc -O0 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.8.5.c -o ../bin/main
    
    // -O3 で最適化した場合は上記と結果がことなった、おそらくコンパイラが 20000000 を予め計算した結果と思われる。
    gcc -O3 -pthread -std=c11 -pedantic-errors -Wall -Werror chapter_17.8.5.c -o ../bin/main
    ```
*/
#include "pthread.h"
#include "unistd.h"
#include "inttypes.h"
#include "stdio.h"

pthread_mutex_t mutex;  // ミューテックスを宣言
pthread_t t1, t2;
uint64_t value = 0;

void* worker(void* _ ) {
    for(int i=0; i < 10000000; i++) {
        pthread_mutex_lock(&mutex);     // ロック
        value+=1;
        pthread_mutex_unlock(&mutex);  // アンロック
    }
    return NULL;
}

int main(void) {
    puts("17.8.5 ミューテックス");
    pthread_mutex_init(&mutex, NULL);   // 初期化
    pthread_create(&t1, NULL, worker, NULL);
    pthread_create(&t2, NULL, worker, NULL);
    
    pthread_join(t1, NULL);
    pthread_join(t2, NULL);
    printf("value is %"PRIu64"\n",value);
    return 0;
}
