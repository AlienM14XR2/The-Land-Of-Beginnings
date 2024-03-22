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

void debug_int(const char* message, const int* debug) {
  printf("DEBUG: %s\t%d\taddr is %p\n",message, *debug, (void*)debug);
}

void debug_fp(const char* message, const double* debug) // 浮動小数点 の直訳は floating point.
{
  printf("DEBUG: %s\t%lf\taddr is %p\n",message, *debug, (void*)debug);
}

/**
  問題、C 言語での正しい設計が分からない：）
  
  単純に CRUD を考えた場合、データごとに対応した関数を用意すれば、それで終わり。
  必要に応じて READ 系の関数を随時実装していくという、誰でも思いつくものになる。
  これではテーブル数 x 4 の実装が必要になり、非常にダルい。できればそれは避けた
  い。人的リソースに余裕があればそれでいいのかも知れないが、私はひとりだ。更に
  言えば、もっといい方法（洗練された設計）があるのではないのかと考えてしまう。
  発想が オブジェクト指向（OO）なので、テンプレートやクラス、カプセル化やポリモ
  ーフィズムは浮かぶ、しかし、C 言語でそれを実現する術を知らない。現状の私のス
  キルでもできそうなものは、関数は CRUD の 4 つのみ データの型を共通化するという
  ものだ。やっぱり C 言語はやり甲斐があるな（C++ はよくできてる）。
  
  今思い返すと、最後に設計したものも データ x 4 の実装という意味では同じだった。
  だたし、あちらはカプセル化とポリモーフィズムで Tx とも分離でき、私の中では満足
  いくものになった、単純なベタ書きとは訳が違う。
  
  ひとまず、ベタ書きで CRUD の一部だけ実装してみるか、設計を先に試すのかは考えて
  おこう。C 言語は自由で難しい。
  
  モジュールを .c ファイル、インタフェースを .h と捉えてみる。
  前方宣言を任意の型（テンプレート）、定義を実体と考えてみる。
*/


struct Data {
  const char* col;
  const char* type;
  const char* val;
  const char* constraint;
};


void printData(const struct Data* d) {
  printf("col: %s\ttype: %s\tval: %s\tconstraint: %s\n", d->col, d->type, d->val, d->constraint);
}

int test_Data() {
  puts("====== test_Data");
  struct Data d = {"id", "long", "1", "PRIMARY KEY"};
  // TODO atoi() atol() atof() で val を数値型に変換してみる、変換対象は type で判断できるはず。
  printData(&d);  
  return 0;
}

int main(void) {
  puts("START 課題  PostgreSQL と C 言語 ===");
  if(0.01) {
    const double pi = 3.141592;
    printf("pi is %lf\n", pi);
    debug_fp("pi is", &pi);
    int x = (int)pi;
    debug_int("x is", &x);
    assert(x == 3);
  }
  if(1.00) {
    int ret = 0;
    ret = test_Data();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
  }
  puts("=== 課題  PostgreSQL と C 言語  END");
  return 0;
}
