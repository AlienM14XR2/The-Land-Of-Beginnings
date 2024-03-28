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

void createBuffer(char* _buffer, size_t _size) {  // この関数を使うのは止める。
  puts("--- createBuffer");
  _buffer = (char*)malloc(_size);    // sizeof(char) は 1 byte だから意味ないかも。
  if(_buffer == NULL) {
    print_error("malloc faile.");    
    exit(EXIT_FAILURE);
  }
  memset(_buffer, '\0', _size);
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
  debug_long("size is ", &size);
  /*
  size_t sz = sizeof(char)*size;
  debug_long("sz is ", &sz);
  buf = (char*)malloc(sz);
  if(buf != NULL) {
    for(size_t i=0; i<sz; i++) {
      buf[i] = '\0';
    }
    char str[1024] = "moji.";
    strcat(buf,str);
    printf("%s\n", buf);
    free((void*)buf);
  }
  */
  createBuffer(buf, size);
  removeBuffer(buf);  
  return EXIT_SUCCESS;
}

void readFile(const char* _filePath, char* _buf) {
  puts("--- readFile");
  FILE*  fp          = NULL;
  char   tmp[1024+1] = "\0";
  size_t readSize    = 0;
    
  fp = fopen(_filePath, "r");
  if(fp != NULL) {    
    // ファイルの読み込みとメモリへの書き込み
    memset(tmp, '\0', 1024+1);
    while((readSize = fread(tmp, 1, 1024, fp)) != 0) {
      strcat(_buf, tmp);
      memset(tmp, '\0', 1024+1);  // この一行がなく、初期化できていなかったのが原因だった。
    }
    printf("\n");
    fclose(fp);
  } else {
    print_error("not file open.");
    exit(1);
  }
}

int test_readFile() {
  puts("=== test_readFile");
  size_t size = getFileSize(FILE_PATH);
  char* buf = (char*)malloc(size+1);
  memset(buf, '\0', size+1);

  readFile(FILE_PATH, buf);   // この関数内で動的にメモリを確保することがよくなかった。
  if(buf != NULL) {
    printf("%s\n", buf);      // これでプログラム上でファイルの中身がみれるようになった。
    
    /**
    '<' タグ名 '>' 欲しい値  '<'/ タグ名 '>'
    INPUT タグなど上記に当てはまらないものは考えないし、ゴミの混入もあり得ると思う。
        しかし、私が欲しいデータは多分上記のパターンのものであってる。自信はないが。
    '<' を検知、タグ名が検索指定されたものか調べる（言葉では簡単だが、これが厄介だと思う）。
        タグ名がヒットした場合は、最初に見つかる '>' の位置を記憶しておく（取得位置）。
        
        記憶した取得位置から、最初に見つかる'<'の一つ手前までが欲しい値ということ。少なくとも、検知
        と取得の 2 回 データの走査が行われるし、1 文字ずつ検査したら時間かかるだろうなと思う：）
        止めようかな：）
    */
//    char tmp[2048];
//    memset(tmp, '\0', sizeof(tmp)/sizeof(tmp[0]));
    int status = 0;
    for(size_t i=0; i<size; i++) {
      if(status == 3) {
        if(buf[i] == '<') {
          status = 0;
          printf("\t");
        } else {
          printf("%c", buf[i]);
        }
      }
      if(buf[i] == '>' && status == 2) {
        status = 3;
      }
      if(buf[i] == 'a' && status == 1) {
        status = 2;
//        printf("%c", buf[i]);
      }
      if(buf[i] == '<' && status == 0) {
        status = 1;
      }
    }
    /**
          欲しい情報が属性、href="ここだったり：）"するのか、ダイレクトに文字列一致の仕組みが必要
          ということになるな。C++ の方がいいような気がしてきたが、まだ遊べるだろ。
    */
    char pattern[] = "href=";
    char* start    = &buf[0];
    char* hitPos   = NULL;
    
    do {
      hitPos = strstr(start, pattern);
      if(hitPos != NULL) {
        printf("%p に %s あり\n", hitPos, pattern);
        start = hitPos + 1;
      }
    } while(hitPos != NULL);
    /**
          当然だよね、現代の Web とは、JSON と JavaScript で構築されている。
          ベタ書きされた静的な HTML などほぼ無いのではなかろうか。つまり、
          ページを復元するにはそれらもトレースする必要がある orz 大昔にも似
          たような問題に当たったよね：）
    */
    
    
    
    removeBuffer(buf);      
  }
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
  if(1.01) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_readFile());
    assert(ret == 0);
  }
  puts("===   文字列の解析  END");
  return EXIT_SUCCESS;
}

