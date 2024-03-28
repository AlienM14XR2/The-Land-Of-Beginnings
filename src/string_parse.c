/**
    課題
    文字列の解析
    
  C 言語で行うべきか悩ましいが、これも暇つぶし、学びの一環としてまずは C で書いてみる。
  Web Scraping、HTML の解析が目的。現状具体的な解決方法が見えていないので、試行錯誤し
  ながらすすめる。
  
  - サンプルの HTML を用意する
  ```
  curl -o sample.html -X GET https://www.youtube.com/results?search_query=DMC+4+
  ```
  - libtidy を利用して、HTML の整形を行う
  ```
  tidy sample.html > sample-fix.html
  
  ※ 残念これがエラーになった、世の中の Web ページがどれでも正しく整形できるわけではないようだ。
  ```
  - 整形されたファイルを読み込む
  - 解析方法を考える：）
  
  少し調べただけだが、なかなか厄介な分野のようだ REST API のような利用ではないので場合によっては
  偽計業務妨害にあたるかもしれないし、取得したデータの利用も販売等の利益を得るような場合は罪に問
  われる可能性がある。今回は学習目的で、HTML データは利用するが、頻繁にウェブサイトへのアクセスを
  行うわけではないので、どちらも該当しないと思うが。
  
  参考文献
  C++ やスクリプト言語で行う方がいいとは思う。それらには既にライブラリがあるため。
  @see 
  https://brightdata.jp/blog/%E3%82%A6%E3%82%A7%E3%83%96%E3%83%87%E3%83%BC%E3%82%BF/best-languages-web-scraping
  https://brightdata.com/blog/how-tos/web-scraping-in-c-plus-plus#libraries
  
  e.g. compile
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror string_parse.c -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>



void debug_int(const char* _message, const int* _debug) {
  printf("DEBUG: %s\tval: %d\taddr: %p\n", _message, *_debug, (void*)_debug);  
}

void debug_double(const char* _message, const double* _debug) {
  printf("DEBUG: %s\tval: %lf\taddr: %p\n", _message, *_debug, (void*)_debug);  
}

void debug_long(const char* _message, const void* _debug) {
  size_t* psz = (size_t*)_debug;
  printf("DEBUG: %s\tval: %lu\taddr: %p\n", _message, *psz, _debug);
}

void print_error(const char* message) {
  printf("ERROR: %s\n", message);
}


static const char* FILE_PATH = "/home/jack/tmp/sample.html";

/**
    ファイルの読み込み。
    指定サれたファイルをプログラムで利用できるようにする
    
    - ファイルサイズの取得
    - ファイルサイズ + 1 のメモリ取得
    - ファイルの Read
  まずは、以上を達成してみる。
*/


size_t getFileSize(const char* fileName) {
  puts("--- getFileSize");
  struct stat st;
  if(stat(fileName, &st) != 0) {
    return 0ul;
  }
  printf("S_ISREG(st.st_mode) is \t%d\n", S_ISREG(st.st_mode));
  if(S_ISREG(st.st_mode)) {
    return st.st_size;
  } else {
    return 0ul;
  }
}

int test_getFileSize() {
  puts("=== test_getFileSize");
  size_t size = getFileSize(FILE_PATH);
  debug_long("size is ", &size);
  assert(size != 0ul);
  return EXIT_SUCCESS;
}

void createBuffer(char* _buffer, size_t _size) {
  puts("--- createBuffer");
  debug_long("size is ", &_size);
  _buffer = (char*)malloc(_size);
  if(_buffer == NULL) {
    print_error("malloc faile.");    
    exit(EXIT_FAILURE);
  }
  _buffer = '\0';
}

void removeBuffer(char* _buffer) {
  puts("--- removeBuffer");
  free((void*)_buffer);
}

int test_Create_Remove_Buf() {
  puts("=== test_Create_Remove_Buf");
  char* buf = NULL;
  size_t size = getFileSize(FILE_PATH);
  size += 1;
  createBuffer(buf, size);
  removeBuffer(buf);  
  return EXIT_SUCCESS;
}



int main(void) {
  puts("START 文字列の解析 ===");
  if(1.00) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_getFileSize());
    assert(ret == 0);
    printf("Play and Result ... %d\n", ret = test_Create_Remove_Buf());
    assert(ret == 0);
  }
  puts("===   文字列の解析  END");
  return EXIT_SUCCESS;
}

