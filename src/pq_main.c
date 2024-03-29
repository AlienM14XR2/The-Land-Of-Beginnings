/**
    課題  PostgreSQL と C 言語
  - PostgreSQL に C で接続する。
  - クエリ発行する。
  
    興味散漫で申し訳ないが、これはこれでいつかやってみたい。
  C++ で pqxx を利用してクエリ発行（INSERT 文）した際に xdevapi より遅かったことが興味の発端だ。
    つまり、C ならもっと速いんじゃなかろうかという疑問。

  # 日付型に関して
  
  ## MySQL
  MySQL 日付には DateTime を使う（Timestamp は範囲が狭い、MySQL 5 系の話）
  Datetime はタイムゾーンなし、Timestamp はあり、よってグローバルサービスは Timestamp を利用すべきとも言える。

  次のようにすれば、明示的に 日付型を登録する必要がない。
  ```
  CREATE TABLE t1 (
    ts TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
    dt DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
  );
  ```

  ## postgres C言語 接続
  ### Postgresql Create Table 日付型 自動登録
  Postgres はトリガを利用する必要がある。

  https://qiita.com/ruemura3/items/7bdca11243c8f1b49ae2
  https://www.postgresql.jp/document/8.2/html/libpq-example.html

  
  e.g. compile
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror -I/usr/include/postgresql/ -L/usr/lib/x86_64-linux-gnu/ pq_main.c -lpq -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <time.h>
#include "libpq-fe.h"

/**
  遠回りしながら進める（色々忘れている）。
 大事なデバッグ方法について考えてみたい。
 assertion 等も忘れた：）... C++： #include <cassert> C： #include <assert.h> だと思う。
*/

void debug_int(const char* message, const int* debug) {
  printf("DEBUG: %s\t%d\taddr is %p\n", message, *debug, (void*)debug);
}

void debug_long(const char* message, const long* debug) {
  printf("DEBUG: %s\t%ld\taddr is %p\n", message, *debug, (void*)debug);
}

void debug_double(const char* message, const double* debug) // 浮動小数点 の直訳は floating point.
{
  printf("DEBUG: %s\t%lf\taddr is %p\n", message, *debug, (void*)debug);
}

void debug_string(const char* message, const char* debug) {
  printf("DEBUG: %s\t%s\taddr is %p\n", message, debug, debug);
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
  const char* col;          // カラム名
  const char* type;         // C における型(int, long, double)
  const char* val;          // 値
  const char* constraint;   // PosgreSQL における型とその制約
};


void printData(const struct Data* d) {
  printf("col: %s\ttype: %s\tval: %s\tconstraint: %s\n", d->col, d->type, d->val, d->constraint);
}

long dataTol(const struct Data* d) {
  if(strcmp(d->type, "long") == 0) {
    return atol(d->val);
  } else {
    printf("Error: in dataTol()\n");
    exit(1);
  }
}

int dataToi(const struct Data* d) {
  if(strcmp(d->type, "int") == 0) {
    return atoi(d->val);
  } else {
    printf("Error: in dataToi()\n");
    exit(1);
  }
}

double dataTof(const struct Data* d) {
  if(strcmp(d->type, "double") == 0) {
    return atof(d->val);
  } else {
    printf("Error: in dataTof()\n");
    exit(1);
  }
}

size_t dataSize(const char* tableName, const struct Data list[], const size_t listSize) {
  // メモリのサイズ計算
  size_t total = 0ul;
  size_t tbl_name_size  = strlen(tableName);
  total = tbl_name_size;
  for(size_t i=0; i<listSize; i++) {
      printData(&list[i]);
      size_t col_size   = strlen(list[i].col);
      total += col_size;
      size_t const_size = strlen(list[i].constraint);
      total += const_size;
      printf("col_size is %ld\tconst_size is %ld\n", col_size, const_size);
  }
  return total;
}

/**
  SQL CREATE TABLE 文の作成。
    内部で動的にメモリを確保している、利用後は解放すること（これを書いていて何か虚しい：）。
    
    これを多少はよくできる方法。
  
  - struct Data のサイズ計算は他でも利用するので、別関数に切り出す。
  - 外部で確保された動的メモリに対して書き込みを行う、この関数の引数にする。
  - この関数での動的メモリ取得は行わない：）
  
  ... DONE. dataSize() で先にサイズ計算を行い内部でのメモリ動的確保は止めた。
  @see test_createTableSql()

*/
void createTableSql(const char* tableName, const struct Data list[], const size_t listSize, char* sql) {
  puts("--------- createTableSql");
  // SQL 文の作成
  char step_1[] = "CREATE TABLE ";
  strcat(sql, step_1);
  strcat(sql, tableName);         // 元は一時変数、文字列リテラルだけど、関数内で利用するのは問題ないのかな。
  char step_2[] = "(";
  char space[] = " ";
  char comma[] = ",";
  char step_3[] = ")";
  strcat(sql, step_2);
  for(size_t i=0; i<listSize; i++) {
    strcat(sql, list[i].col);
    strcat(sql, space);
    strcat(sql, list[i].constraint);
    if(i+1 < listSize) {
      strcat(sql, comma);      
    }
  }
  strcat(sql, step_3);
}

/**
e.g.
R"(
  CREATE TABLE company ( 
    id      BIGINT       NOT NULL PRIMARY KEY
  , name    VARCHAR(128) NOT NULL
  , address VARCHAR(256) NOT NULL 
 )
)";
*/




static void
exit_nicely(PGconn *conn)
{
        PQfinish(conn);
        exit(1);
}







int test_createTableSql() {
  puts("====== test_createTableSql");
  // どっちでもいいや：）
//  size_t s = atol("9223372036854775807");
//  long s   = atol("9223372036854775807");
//  printf("s is %ld\n", s);
    struct Data list[] = {{"id",      "long",   "0", "BIGINT PRIMARY KEY"}
                         ,{"name",    "string",  "", "VARCHAR(128) NOT NULL"}
                         ,{"address", "string",  "", "VARCHAR(256) NOT NULL"}};
    size_t listSize = sizeof(list)/sizeof(list[0]);
    assert(listSize == 3);
    printf("listSize is %ld\n", listSize);
    // struct Data のサイズ計算
    size_t bufSize = dataSize("company", list, listSize);
    bufSize*=3;   // テーブルの構成要素、カラム名、型、制約が相当小さくない限りは、これで充分だと思う。
    printf("bufSize*3 is %ld\n", bufSize);
    char* create_tbl_sql = (char*)malloc(bufSize);
    create_tbl_sql[0] = '\0';
    // CREATE TABLE 文の作成
    createTableSql("company", list, listSize, create_tbl_sql);
    debug_string("sql is ", create_tbl_sql);
    free((void*)create_tbl_sql);
  return 0;
}

int test_libpq_connect_create_tbl() {
  // @see https://www.postgresql.jp/document/15/html/libpq-connect.html
  // @see https://www.postgresql.jp/document/8.0/html/libpq-example.html
  puts("====== test_libpq_connect_create_tbl");
  clock_t start_clock = clock();
  
  const char *conninfo = "host=localhost port=5432 dbname=jabberwocky user=derek password=derek1234 connect_timeout=10";
  PGconn     *conn = NULL;
  PGresult   *res  = NULL;
  
  conn = PQconnectdb(conninfo);
  if(PQstatus(conn) != CONNECTION_OK)
  {
    fprintf(stderr, "Connection to database failed: %s",
    PQerrorMessage(conn));
    exit_nicely(conn);
  } else {
    printf("... DONE connected.\n");
  }
  clock_t start_clock_2 = clock();
  /* トランザクションブロックを開始する。 */
  res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  /* 不要になったら、メモリリークを防ぐためにPGresultをPQclearすべき。*/
  PQclear(res);
  // DROP TABLE IF EXISTS company
  res = PQexec(conn, "DROP TABLE IF EXISTS company");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "DROP TABLE command failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  /* 不要になったら、メモリリークを防ぐためにPGresultをPQclearすべき。*/
  PQclear(res);
  
  // CREATE TABLE company
  struct Data list[] = {{"id",      "long",   "0", "BIGINT PRIMARY KEY"}
                       ,{"name",    "string",  "", "VARCHAR(128) NOT NULL"}
                       ,{"address", "string",  "", "VARCHAR(256) NOT NULL"}};
  size_t listSize = sizeof(list)/sizeof(list[0]);
  size_t bufSize = dataSize("company", list, listSize);
  bufSize*=3;
  char* create_tbl_sql = (char*)malloc(bufSize);
  create_tbl_sql[0] = '\0';
  createTableSql("company", list, listSize, create_tbl_sql);
  debug_string("sql is ", create_tbl_sql);
  clock_t start_clock_3 = clock();
  res = PQexec(conn, create_tbl_sql);
  free((void*)create_tbl_sql);
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "CREATE TABLE command failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  /* 不要になったら、メモリリークを防ぐためにPGresultをPQclearすべき。*/
  PQclear(res);
  /* ポータルを閉ざす。ここではエラーチェックは省略した… */
//  res = PQexec(conn, "CLOSE myportal");   // 先に FETCH ALL in myportal が必要
//  PQclear(res);
  /* トランザクションを終了する */
  res = PQexec(conn, "END");
  PQclear(res);
  /* データベースとの接続を閉じ、後始末を行う。 */
  PQfinish(conn);
  clock_t end_clock = clock();
  printf("clock: %lf (sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);
  printf("clock: %lf (sec)\n", (double)(end_clock-start_clock_2)/CLOCKS_PER_SEC);
  printf("clock: %lf (sec)\n", (double)(end_clock-start_clock_3)/CLOCKS_PER_SEC);
  return 0;
}

/**
  嫌な予感がする。libpq と libpqxx 、大差はないのかもしれない：）
  これが事実なら、C 言語で開発する意味は無くなる。
  確認するために、ベタ書きで INSERT 文を発行してみようかな。
*/

int test_libpq_insert_beta() {
  puts("====== test_libpq_insert_beta");
  const char *conninfo = "host=localhost port=5432 dbname=jabberwocky user=derek password=derek1234 connect_timeout=10";
  PGconn     *conn = NULL;
  PGresult   *res  = NULL;
  
  conn = PQconnectdb(conninfo);
  if(PQstatus(conn) != CONNECTION_OK)
  {
    fprintf(stderr, "Connection to database failed: %s",
    PQerrorMessage(conn));
    exit_nicely(conn);
  } else {
    printf("... DONE connected.\n");
  }
  clock_t start_clock = clock();
  
  res = PQexec(conn, "BEGIN");
  if (PQresultStatus(res) != PGRES_COMMAND_OK)
  {
    fprintf(stderr, "BEGIN command failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  const char* paramValues[3];
  paramValues[0] = "0";
  paramValues[1] = "foo.co, ltd.";
  paramValues[2] = "Tokyo";
  PQexecParams(conn,
                     "INSERT INTO company (id, name, address) VALUES ($1, $2, $3)",
                     3,           /* パラメータ数。 */
                     NULL,        /* バックエンドにパラメータの型を推測させる。 */
                     paramValues,
                     NULL,        /* テキストのため、パラメータ長は不要。 */
                     NULL,        /* デフォルトで全てのパラメータはテキスト。 */
                     0);          /* テキスト結果を要求。 */
  /*
  if (PQresultStatus(res) != PGRES_TUPLES_OK)
  {
    fprintf(stderr, "INSERT failed: %s", PQerrorMessage(conn));
    PQclear(res);
    exit_nicely(conn);
  }
  PQclear(res);
  */
  res =PQexec(conn, "END");
  PQclear(res);
  PQfinish(conn);
  clock_t end_clock = clock();
  printf("clock: %lf (sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);
  return 0;
}


int test_Data() {
  puts("====== test_Data");
  struct Data d = {"id", "long", "1", "BIGINT PRIMARY KEY"};    // BIGINT は size_t が妥当ではないのか？  まぁいいや。
  printData(&d);
  // TODO atoi() atol() atof() で val を数値型に変換してみる、変換対象は type で判断できるはず。
  if(strcmp(d.type, "long") == 0) {
    long val = atol(d.val);
    debug_long("val is ", &val);
  }
  long d_val = dataTol(&d);
  debug_long("d_val is ", &d_val);
  struct Data d2 = {"email", "string", "foo@loki.org", "VARCHAR(256) NOT NULL UNIQUE"};
  printData(&d2);
  if(strcmp(d2.type, "string") == 0) {
    debug_string("val is ", d2.val);    
  }
  struct Data d3 = {"age", "int", "24", "INTEGER"};
  printData(&d3);
  if(strcmp(d3.type, "int") == 0) {
    int val = atoi(d3.val);
    debug_int("val is ", &val);
  }
  int d3_val = dataToi(&d3);
  debug_int("d3_val is ", &d3_val);
  struct Data d4 = {"tax", "double", "1.53", "NUMERIC"};
  double d4_val = dataTof(&d4);  
  debug_double("d4_val is ", &d4_val);
  /**
        確かにこの方法なら型の管理はできるが、atoi() atol() atof() をラップした dataToi() dataTol() dataTof() が必要になる。 
    C 言語は強い型付言語ではないが、それでも型に束縛されていく。さらに型にはそれぞれ unsigned もある orz この点は PostgreSQL 
        に存在する型に合わせていく必要があると思われる。
        次のことはいずれ問題になるかもしれない、RDBMS への I/O は struct Data で本当に賄えるのか。入力は共通化できても出力は個々
        の型が必要になるのではないかという疑念がある。
  */
  return 0;
}

/**
  Template Method パターン を考えてみる。
  
    関数ポインタでできないかな。
    これは以前から試してみたかったこと。
*/

void add(const int* lhs, const int* rhs, int* result) {
  *result = (*lhs) + (*rhs);
}

void multi(const int* lhs, const int* rhs, int* result) {
  *result = (*lhs) * (*rhs);
}

void (*calc)(const int* lhs, const int* rhs, int* result);

int test_calc_1() {
  puts("====== test_calc_1");
  calc = add;
  int lhs = 3;
  int rhs = 6;
  int ret = 0;
  calc(&lhs, &rhs, &ret);
  debug_int("ret is ", &ret);
  
  lhs = 3;rhs = 6;ret = 0;
  calc = multi;
  calc(&lhs, &rhs, &ret);
  debug_int("ret is ", &ret);  
  return 0;
}

int test_calc_2(void (*func)(const int*, const int*, int*)) {
  puts("====== test_calc_2");
  int lhs = 3;
  int rhs = 6;
  int ret = 0;
  func(&lhs, &rhs, &ret);
  debug_int("ret is ", &ret);  
  return 0;
}

void template_method_a(
    void (*func_1)(const int*, const int*, int*)
  , void (*func_2)(const int*, const int*, int*)
);

int test_template_method_a() {
  puts("====== test_template_method_a");
  template_method_a(add, multi);
  /**
        関数ポインタの型さえあっていれば、Template Method パターンの実現は可能ということ。
  */
  return 0;
}

int main(void) {
  puts("START 課題  PostgreSQL と C 言語 ===");
  if(0.01) {
    const double pi = 3.141592;
    printf("pi is %lf\n", pi);
    debug_double("pi is", &pi);
    int x = (int)pi;
    debug_int("x is", &x);
    assert(x == 3);
  }
  if(1.00) {
    int ret = 0;
    ret = test_Data();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
    ret = test_calc_1();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
    ret = test_calc_2(add);
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
    ret = test_calc_2(multi);
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
    ret = test_template_method_a();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
  }
  if(1.01) {
    int ret = 0;
    ret = test_createTableSql();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
  }
  if(1.02)   // 1.02 
  {
    int ret = 0;
    ret = test_libpq_connect_create_tbl();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
    ret = test_libpq_insert_beta();
    debug_int("Play and Result ... ", &ret);
    assert(ret == 0);
  }
  puts("=== 課題  PostgreSQL と C 言語  END");
  return 0;
}

void template_method_a(
    void (*func_1)(const int*, const int*, int*)
  , void (*func_2)(const int*, const int*, int*)
) {
  puts("--------- template_method_a");
  int lhs = 3;
  int rhs = 6;
  int ret = 0;
  func_1(&lhs, &rhs, &ret);
  debug_int("ret is ", &ret);
  func_2(&lhs, &rhs, &ret);
  debug_int("ret is ", &ret);  
}

