/**
        第１７章    マルチスレッド
        
    ```
    gcc -O3 -std=c11 -pthread -pedantic-errors -Wall -Werror chapter_17.c -o ../bin/main
    ```
*/
#include "stdio.h"
#include "pthread.h"
#include "unistd.h"

void* thread_impl(void* arg) {
    for(int i = 0; i < 10; i++) {
        puts(arg);
        sleep(1);
    }
    return NULL;
}

void* worker(void* param) {
    for(int i=0 ; i < 3; i++) {
        puts((const char*)param);
        sleep(1);
    }
    return (void*)"done.";
}

int main(void) {
    puts("=== 第１７章    マルチスレッド");
    if("17.7") {
        puts("--- メモリバリア");
    }
    if("17.8") {
        puts("--- pthreads の紹介");
    }
    if(0) {
        puts("--- 17.8.2 スレッド作成");
        pthread_t t1, t2;
        /**
                        第１引数は、初期化する pthread_t インスタンスへのポインタだ。
                        第２引数は、属性のコレクションへのポインタだが、これらについては後述する。
                        スレッド起動時の関数 start_routine は、ポインタを受け取りポインタを返す仕様である。
                        受け取るのは引数への void* 型ポインタで、これは１個の引数しか受け取れないが、構造体や配列
                        で複数の引数をカプセル化し、それへのポインタを渡すことができる。 start_routine の戻り値は、
                        やはりポインタで、スレッドが仕事をした結果を返すのに使える（ただし、ローカル変数のアドレスを返してはいけない）。                       
        */
        pthread_create(&t1, NULL, thread_impl, "fizz");
        pthread_create(&t2, NULL, thread_impl, "buzzzzz");
        /**
                        まだ、他のスレッドが存在していたら、メインスレッドは待つべきなのだ、
                        それがメインスレッドからの pthread_exit が行うことである。
                        このときは、他のスレッドが終了するのを待ってから、そのプログラムを終了させる。
                        それに続くコードは実行されないから "bye" というメッセージは stdout に出力されることはない。
        */
        puts("waiting ...");
        pthread_exit(NULL);
        int foo = 3;
        (void)foo;  // unused variable の警告あるいはエラーがなくなる：）
        puts("bye");
    }
    if("17.8.3") {
        /**
                           もっとも単純な同期は、スレッドの合流（joining）である。
            pthread_t のインスタンスについて pthread_join を呼び出すと、現在のスレッドは、その別
                           スレッドが終了するまで待ち状態に入る。
            thread_join は２つの引数を受け取る、スレッドそのものと、そのスレッドの実行結果によって後に初期化される
            void* 型変数のポインタだ。
        */
        puts("--- 17.8.2 スレッド管理");
        pthread_t t;
        void* result;
        pthread_create(&t, NULL, worker, (void*)"I am worker.");
        pthread_join(t, &result);
        puts((const char*)result);
    }
    return 0;
}
