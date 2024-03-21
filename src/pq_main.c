/**
    課題  PostgreSQL と C 言語
  - PostgreSQL に C で接続する。
  - クエリ発行する。
  
    興味散漫で申し訳ないが、これはこれでいつかやってみたい。
  C++ で pqxx を利用してクエリ発行（INSERT 文）した際に xdevapi より遅かったことが興味の発端だ。
    つまり、C ならもっと速いんじゃなかろうかという疑問。
  
  e.g. compile
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror -I/usr/include/postgresql/ -L/usr/lib/x86_64-linux-gnu/ pq_main.c -lpq -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "libpq-fe.h"

/**
  遠回りしながら進める（色々忘れている）。
 大事なデバッグ方法について考えてみたい。
 assertion 等も忘れた：）... C++： #include <cassert> C： #include <assert.h> だと思う。
*/

void debug_number(const char* message, const int* debug) {
  printf("DEBUG: %s\t%d\taddr is %p\n",message, *debug, (void*)debug);
}

void debug_fp(const char* message, const double* debug) // 浮動小数点 の直訳は floating point.
{
  printf("DEBUG: %s\t%lf\taddr is %p\n",message, *debug, (void*)debug);
}


int main(void) {
  puts("START 課題  PostgreSQL と C 言語 ===");
  if(0.01) {
    const double pi = 3.141592;
    printf("pi is %lf\n", pi);
    debug_fp("pi is", &pi);
    int x = (int)pi;
    debug_number("x is", &x);
    assert(x == 3);
  }
  puts("=== 課題  PostgreSQL と C 言語  END");
  return 0;
}
