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




/**
  Linked List 
  
  void* を利用したものを考えてみる。
    データ構造は  value と next で表現できるはず。
  add() で追加、remove() で削除する。
*/

struct tree {
  void* value;
  struct tree* next;
};

typedef void* H_TREE;

/**
    ツリーハンドラの作成。
*/
H_TREE createTree() {
  puts("--------- createTree");
  struct tree* pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = NULL;
  pt->next = NULL;
  return (H_TREE)pt;
}

/**
    ツリーハンドラの次の値を返却する。
*/
H_TREE hasNext(H_TREE _tree) {
  return (H_TREE)((struct tree*)_tree)->next;
}

/**
    ツリーハンドラのポインタを最後尾に移動する。
*/
H_TREE moveLast(H_TREE _tree) {
  puts("--------- moveLast");
  struct tree* last = (struct tree*)_tree;
  while(last != NULL) {
    if(last->next != NULL) {
      last = last->next;
    } else {
      break;
    }
  }
//  printf("last addr is \t%p\n", (void*)last);
  return (H_TREE)last;
}

/**
    ツリーハンドラの要素数と根の合計数を返却する。
*/
size_t countTree(H_TREE _root) {
  puts("--------- countTree");
  struct tree* current = (struct tree*)_root;
  size_t i = 0;
  while((current = hasNext(current)) != NULL) {
    i++;
  }
  i += 1;     // これは root も含めて返却している。
  return i;
}

/**
    ツリーハンドラの全要素の削除を行う。
    根も削除する。
    ※ もし、H_TREE が管理する value が動的にメモリ確保されたもので、H_TREE 以外そのアドレスを知り得ない場合
    この関数を value 解放前に行うとメモリリークを引き起こす：）
*/
void clearTree(H_TREE _root, size_t count) {  // このことは「肝に銘じよ」C 言語では削除する対象のサイズを先に計算しろ。
  puts("--------- clearTree");
  H_TREE array[count];    // この配列の宣言のやり方は GCC 以外でもできるのかな？ 添字に変数を利用しているんだよね。
  struct tree* current = (struct tree*)_root;
  array[0] = current;
  size_t i = 1;
  while((current = hasNext(current)) != NULL) {
    array[i] = current;
    i++;
  }
  for(i=0; i<count; i++ ) {
//    puts("------------ D");
    free(array[i]);
  }
}

/**
    ツリーハンドラに値を追加する。
*/
H_TREE pushTree(H_TREE _root, void* value) {
  puts("--------- pushTree");
  struct tree* pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = value;
  pt->next = NULL;
  struct tree* last = (struct tree*)moveLast(_root);
  if(last == (struct tree*)_root) {
//      printf("------------ SAME\n");    
    ((struct tree*)_root)->next = pt;
  } else {
    last->next = pt;
  }
//  printf("pt addr is \t%p\n", (void*)pt);
  return (H_TREE)pt;
}

void* getValue(H_TREE current) {
  puts("--------- getValue");
  if(current != NULL) {
    return ((struct tree*)current)->value;
  } else {
    return NULL;
  }
}

/**
    最後尾にある値の取り出しとそのツリーハンドラの削除を行う。
  Stack と同じ動作、最初にツリーハンドラに登録した値は、最後に取り出される（First-in Last-out）。
*/
void* popStack(H_TREE _root) {
  puts("--------- popStack");
  // 前方アドレスの付け替え後、削除する。
  void* value = NULL;
  struct tree* last     = (struct tree*)moveLast(_root);
  struct tree* current  = (struct tree*)_root;
  if(current == last) {
    // ignore
    return NULL;
  } 
  else
  if(current->next == last) {
//    printf("------------ F2 SAME\n");
    value = last->value;
    current->next = NULL;
    free((void*)last);
  } 
  else {
    while((current = (H_TREE)hasNext((H_TREE)current)) != NULL) {
      if( ((struct tree*)current)->next == last ) {
//        printf("------------ SAME\n");
        value = last->value;
        ((struct tree*)current)->next = NULL;
        free((void*)last);
        break;
      }
    }
  }
  return value;
}

/**
    起点の次、仮の先頭の値の取り出しとそのツリーハンドラの削除を行う。
  queue と同じ動作（First-in First-out）。
*/
void* popQueue(H_TREE _root) {
  puts("--------- popQueue");
  // 先頭の ツリーハンドラは起点なので無視する
  // 2 番目が対象であり、3 番目がある場合はそのアドレスを起点の next に代入する
  void* value = NULL;
  struct tree* second = ((struct tree*)_root)->next;
  if(second != NULL) {
    value                       = second->value;
    ((struct tree*)_root)->next = second->next;
    free((void*)second);
  }
  return value;
}












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
  char   tmp[2048+1] = "\0";
  size_t readSize    = 0;
    
  fp = fopen(_filePath, "r");
  if(fp != NULL) {    
    // ファイルの読み込みとメモリへの書き込み
    memset(tmp, '\0', 2048+1);
    while((readSize = fread(tmp, 1, 2048, fp)) != 0) {
      strcat(_buf, tmp);
      memset(tmp, '\0', 2048+1);  // この一行がなく、初期化できていなかったのが原因だった。
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
    char pattern[]  = "href=\"";
    size_t ptnSize  = strlen(pattern);
    char* start     = &buf[0];
    char* hitPos    = NULL;
    size_t hitCount = 0;
    H_TREE root     = createTree();
    
    do {
      hitPos = strstr(start, pattern);
      if(hitPos != NULL) {
        hitPos += ptnSize;
        hitCount++;
        pushTree(root, hitPos);
        printf("%p に %s あり\n", hitPos, pattern);
        start = hitPos + 1;
      }
    } while(hitPos != NULL);
    debug_long("ptnSize is ", &ptnSize);
    debug_long("hitCount is ", &hitCount);
    
    // 実際の値（URL）を取得する
    H_TREE tmp    = root;
    char url[1025] = "\0";
    int i = 0;
    while((tmp = hasNext(tmp)) != NULL) {
      char* searchPos = (char*)getValue(tmp);
      memset(url, '\0', 1025);
      i = 0;
      while(1) {
        if(*searchPos != '"') {
          url[i] = *searchPos;
        }
        if(i == 1024 || *searchPos == '"') {
          printf("%s\n", url);
          break;
        }
        searchPos++;
        i++;
      }
    }
    printf("\n");
    
    
    /**
          当然だよね、現代の Web とは、JSON と JavaScript で構築されている。
          ベタ書きされた静的な HTML などほぼ無いのではなかろうか。つまり、
          ページを復元するにはそれらもトレースする必要がある orz 大昔にも似
          たような問題に当たったよね：）
          
          まぁひとまず、できることはやってみたが、取得した URL が私が欲しか
          った情報かと問われれば、否である。今回的にしたサイトの場合は、JSON
          に有益、欲しかった情報があると思われる。
          
          上記の仕組みを関数化して、少しだけ汎用性を持たせて、色々調べてみる。
    */
    
    
    clearTree(root, countTree(root));
    removeBuffer(buf);      
  }
  return EXIT_SUCCESS;  
}

void searchProto(char* _buf, const char* _pattern, const char _limitCh/*, H_TREE _dest*/) {
  puts("------ searchProto");
  if(_buf != NULL) {
    size_t ptnSize  = strlen(_pattern);
    char* start     = &_buf[0];
    char* hitPos    = NULL;
    H_TREE root     = createTree();
    size_t hitCount = 0;
    // 検索文字（パターン）に該当する箇所（アドレス）の取得    
    do {
      hitPos = strstr(start, _pattern);
      if(hitPos != NULL) {
        hitPos += ptnSize;
        pushTree(root, hitPos);
//        printf("%p に %s あり\n", hitPos, _pattern);
        start = hitPos + 1;
        hitCount++;
      }
    } while(hitPos != NULL);
    debug_long("hitCount is ", &hitCount);
    // 実際の値を _limitCh 以前で取得する
    H_TREE tmp     = root;
    char url[1025] = "\0";                // 次のステップは、これを返却する仕組みが必要（H_TREE の value その動的メモリでいけるかな、解放忘れ怖いな：）。
    int i = 0;
    while((tmp = hasNext(tmp)) != NULL) {
      char* searchPos = (char*)getValue(tmp);
      memset(url, '\0', 1025);
      i = 0;
      while(1) {
        if(*searchPos != _limitCh) {
          url[i] = *searchPos;
        }
        if(i == 1024 || *searchPos == _limitCh) {
          printf("%s\n", url);
          break;
        }
        searchPos++;
        i++;
      }
    }
    printf("\n");    
    clearTree(root, countTree(root));
  } else {
    printf("_buf is null.\n");
  }
}

int test_searchProto() {
  puts("=== test_searchProto");
  size_t size = getFileSize(FILE_PATH);
  char* buf = (char*)malloc(size+1);
  memset(buf, '\0', size+1);
  readFile(FILE_PATH, buf);
  
  char pattern[]    = "href=\"";
  searchProto(buf, pattern, '"');
  char pattern_2[]  = "videoId\":\"";
  searchProto(buf, pattern_2, '"');
  
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
  if(0) {    // 1.01
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_readFile());
    assert(ret == 0);
  }
  if(1.02) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_searchProto());
    assert(ret == 0);
  }
  puts("===   文字列の解析  END");
  return EXIT_SUCCESS;
}

