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
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror -I../inc/ h_tree.c string_parse.c -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>

#include "h_tree.h"



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
  char   tmp[10241] = "\0";
  size_t readSize    = 0;
    
  fp = fopen(_filePath, "r");
  if(fp != NULL) {    
    // ファイルの読み込みとメモリへの書き込み
    memset(tmp, '\0', 10241);
    while((readSize = fread(tmp, 1, 10240, fp)) != 0) {
      strcat(_buf, tmp);
      memset(tmp, '\0', 10241);  // この一行がなく、初期化できていなかったのが原因だった。
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
    while((tmp = hasNextTree(tmp)) != NULL) {
      char* searchPos = (char*)treeValue(tmp);
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

void searchProto(H_TREE _dest, size_t _destSize, char* _buf, const char* _pattern, const char _limitCh) {
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
        start = hitPos + 1;
        hitCount++;
      }
    } while(hitPos != NULL);
    debug_long("hitCount is ", &hitCount);
    // 実際の値を _limitCh より前で取得する
    H_TREE tmp     = root;
    size_t i = 0;
    size_t limitSize = ((sizeof(char))*_destSize) - 1;
    while((tmp = hasNextTree(tmp)) != NULL) {
      char* str = (char*)malloc((sizeof(char))*_destSize);  // char は 1 byte だけどね。
      char* searchPos = (char*)treeValue(tmp);
      memset(str, '\0', (sizeof(char))*_destSize);
      i = 0;
      while(1) {
        if(*searchPos != _limitCh) {
          str[i] = *searchPos;
        }
        if(i == limitSize || *searchPos == _limitCh) {
          pushTree(_dest, str);
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
  
  size_t strSize    = 1025;
  H_TREE tmp        = NULL;
  char pattern[]    = "href=\"";
  H_TREE t1 = createTree();
  searchProto(t1, strSize, buf, pattern, '"');
  tmp = t1;
  while((tmp = hasNextTree(tmp)) != NULL) {
    char* str = (char*)treeValue(tmp);
    printf("%s\n", str);
    free((void*)str);
  }
  char pattern_2[]  = "videoId\":\"";
  H_TREE t2 = createTree();
  searchProto(t2, strSize, buf, pattern_2, '"');
  tmp = t2;
  while((tmp = hasNextTree(tmp)) != NULL) {
    char* str = (char*)treeValue(tmp);
    printf("%s\n", str);
    free((void*)str);
  }
  
  clearTree(t1, countTree(t1));
  clearTree(t2, countTree(t2));
  removeBuffer(buf);
  return EXIT_SUCCESS;
}



/**
    少しだけターゲットの解析をしてみた。取得するデータの終端も文字列で検索できないと意味
    がない、あるいは不自由を来すおそれがある。
    e.g. 先頭の文字列 "{\"videoRenderer\"" 終端の文字列 "\"}}}]},\"shortBylineText\""
  上例のような形が JSON であるため。
  これを先に考えてみよう。
*/




void setRange(char* _buf, H_TREE _startPositions, H_TREE _endPositions, const char* _startPattern, const char* _endPattern)
{
  puts("------ setRange");
  if(_buf != NULL) {
    char*  start     = &_buf[0];
    char*  hitPos    = NULL;
    // 先頭検索文字（パターン）に該当する箇所（アドレス）の取得
    do {
      hitPos = strstr(start, _startPattern);
      if(hitPos != NULL) {
        pushTree(_startPositions, hitPos);
        start = hitPos + 1;
      }
    } while(hitPos != NULL);
    // 終端検索文字（パターン）に該当する箇所（アドレス）の取得 
    start     = &_buf[0];
    hitPos    = NULL;
    do {
      hitPos = strstr(start, _endPattern);
      if(hitPos != NULL) {
        pushTree(_endPositions, hitPos);
        start = hitPos + 1;
      }
    } while(hitPos != NULL);
  } else {
    printf("_buf is null.\n");
  }
}

bool isValidRange(H_TREE _startPos, H_TREE _endPos) {
  puts("------ isValidRange");
  if( countTree(_startPos) == countTree(_endPos) ) {
    puts("start end 個数は同じ");
    H_TREE stmp = _startPos;
    H_TREE etmp = _endPos;
    while((stmp = hasNextTree(stmp)) != NULL) {
      char* scp = (char*)treeValue(stmp);
      printf("%p\t%c", scp, *scp);
      etmp = hasNextTree(etmp);
      char* ecp = (char*)treeValue(etmp);
      printf("%p\t%c", ecp, *ecp);
      if(scp >= ecp) {
        printf("ERROR: addr ecp < scp");
        return false;
      }
    }
    return true;
  }
  return false;
}

void checkChar(const char* _src, const char _start, const char _end, size_t* _startCount, size_t* _endCount) {
  puts("------ checkChar");
  size_t len = strlen(_src);
  printf("_src size is %ld\n", len);
  for(size_t i=0; i<len ;i++) {
    if(_src[i] == _start) {
      (*_startCount)++;
    }
    else if(_src[i] == _end) {
      (*_endCount)++;
    }
  }
}

void appendTop(H_TREE _dest, const char* _src, const char* _append, const size_t _chCount) {
  puts("------ appendTop");
  // C 言語での文字列操作、その際のサイズ計算は面倒だし、多少サイズに余裕を持たせるようにする（ヌル文字を忘れる：）。  
  size_t size = strlen(_src) + (strlen(_append) * 2)+1;
  printf("size is %ld\n", size);
  char* str = (char*)malloc(sizeof(char)*size);
  memset(str, '\0', sizeof(char)*size);
  for(size_t i=0; i<_chCount; i++) {
    strcat(str, _append);
  }
  strcat(str, _src);
  pushTree(_dest, str);
}

void appendBottom(H_TREE _dest, const char* _src, const char* _append, const size_t _chCount) {
  puts("------ appendBottom");
  size_t size = strlen(_src) + (strlen(_append) * 2)+1;
  printf("size is %ld\n", size);
  char* str = (char*)malloc(sizeof(char)*size);
  memset(str, '\0', sizeof(char)*size);
  strcat(str, _src);
  for(size_t i=0; i<_chCount; i++) {
    strcat(str, _append);
  }
  pushTree(_dest, str);
}

void search2nd(H_TREE _dest, H_TREE _startPos, H_TREE _endPos, char _beforeLimitPos) 
{
  puts("------ search2nd");
  char* start      = NULL;
  char* end        = NULL;
  size_t sz = countTree(_startPos);       // countTree() は 要素数 + 1 を返却する。 +1 は H_TREE の根（root）。  
  debug_long("sz is ", &sz);
  for(size_t i=0 ; i<(sz-1); i++) {
    start    = (char*)popQueue(_startPos);
    end      = (char*)popQueue(_endPos);
    end += _beforeLimitPos;               // limitCh の直前まで移動
    printf("(end-start) size is %ld\n", end - start);
    size_t msz = (end - start) + 1;
    char* str = (char*)malloc(sizeof(char)*msz);
    memset(str, '\0', sizeof(char)*msz);
    size_t j = 0;
    size_t jlimit = msz-1;
    while(1) {
      str[j] = *start;
      if(j >= jlimit || start == end) {
        pushTree(_dest, str);
        break;
      }
      start++;
      j++;
    }
  }
}


int test_search2nd() {
  puts("=== test_search2nd");
  clock_t start_clock = clock();
  size_t size = getFileSize(FILE_PATH);
  char* buf = (char*)malloc(size+1);
  memset(buf, '\0', size+1);
  readFile(FILE_PATH, buf);
  
  char startPattern[]    = "{\"videoRenderer\":";
  char endPattern[]      = "\"}}}]},\"shortBylineText\"";   // endPattern の中に必ず終端を表現する文字があること。この場合は ','
  printf("startPattern is \t%s\n", startPattern);
  printf("endPattern   is \t%s\n", endPattern);
    
  /**
    search2nd() を実装するにあたり、最初に validation を行う必要がこれはある。
      そもそもが「ヤマカン」であるため、設定するパラメータで正しく機能する保証がないから（JSON として正しいこととは別の話）。
      - 最低限、_startPattern と _endPattern でヒットする数が同じこと。
      - 各 start と end の組み合わせにおいて、アドレスが start < end であること（start >= end は NG）。
  */
  
  H_TREE startPos = createTree();
  H_TREE endPos   = createTree();
  H_TREE dest     = createTree();
  H_TREE fix      = createTree();
  char appendT[] = "{";
  char appendB[] = "}";
  setRange(buf, startPos, endPos, startPattern, endPattern);
  if(isValidRange(startPos, endPos)) {
    search2nd(dest, startPos, endPos, 5);
    H_TREE tmp = dest;
    while((tmp = hasNextTree(tmp)) != NULL) {
      char* str = treeValue(tmp);          // BAD KNOW-HOW ここで pop してはいけない（理由が知りたければ試してみてくれ：）
      /**
                簡易 valid JSON を考えてみる。
        {} の数が同じ、[] の数が同じ、それぞれの位置の問題。
        endPattern から、{} の数だけに注目すればいいと思う、各括弧の位置については考慮しない（それは元データが間違っている）。
        
                 単一責務の原則と処理速度の問題。
                 これは正直悩ましいが原則に従うならば、特定の文字列の Parse とそれが任意のフォーマットに適合するか否かとは分けて考えるべきだ
                 と思う。したがってここでフォーマット適合に関する処理を行う。
      */
      size_t s = 0;
      size_t e = 0;
      checkChar(str, '{', '}', &s, &e);
      debug_long("s is ", &s);
      debug_long("e is ", &e);
      if(s > e) {
        appendBottom(fix, str, appendB, s-e);
      } else {
        appendTop(fix, str, appendT, e-s);
      }
      free((void*)str);
    }
    tmp = fix;
    while((tmp = hasNextTree(tmp)) != NULL) {
      char* str = treeValue(tmp);
      printf("str is \t%s\n", str);
      free((void*)str);
    }
    printf("dest count is \t%ld\n", countTree(dest));   // H_TREE は 根（root）分余計にある。実際の要素数 + 1 になる。
    printf("fix count is \t%ld\n", countTree(fix));   // H_TREE は 根（root）分余計にある。実際の要素数 + 1 になる。
  }
  clearTree(startPos, countTree(startPos));
  clearTree(endPos, countTree(endPos));
  clearTree(dest, countTree(dest));
  clearTree(fix, countTree(fix));
  removeBuffer(buf);
  clock_t end_clock = clock();
  printf("clock: %lf (sec)\n", (double)(end_clock-start_clock)/CLOCKS_PER_SEC);
  return EXIT_SUCCESS;
}

/**
  上記テスト関数で JSON の取得には成功したが、残念ながら、JSON フォーマットとしては正しくない。
  興味があれば、正しい JSON フォーマットへの成形を考えてみる。ここまでやって何なんだが、最終的
  に JSON が欲しいだけであれば、curl 等のリクエスト結果をそのまま返却して、JavaScript で解析
  する方がいいのかもしれない。
  
  Web Scraping を考えてみる。これは対象のページ構成に左右される。ページが刷新されたら Parse 
  する側にも変更が必要になるものと考えるべきだろう。上記のような  search 関数と具体的な対象ページ、
  サービス提供元の情報であることを表現する関数は分離すべきだと思う。C++ でそれは実装しようかな。
*/




int main(void) {
  puts("START 文字列の解析 ===");
  if(1.00) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_getFileSize());
    assert(ret == 0);
    printf("Play and Result ... %d\n", ret = test_Create_Remove_Buf());
    assert(ret == 0);
  }
  if(0) {       // 1.01
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_readFile());
    assert(ret == 0);
  }
  if(1.02) {    // 1.02
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_searchProto());
    assert(ret == 0);
  }
  if(1.03) {    // 1.03
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_search2nd());
    assert(ret == 0);
  }
  puts("===   文字列の解析  END");
  return EXIT_SUCCESS;
}

