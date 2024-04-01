/**
  課題
 
 H_TREE のブラッシュアップとその動作確認用ソース。
 最終的には H_TREE を宣言と定義に切り出すこと。
 
 e.g. compile
 gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror h_tree_proto.c -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <setjmp.h>



/**
  Linked List 
  
  void* を利用したものを考えてみる。
    データ構造は  value と next で表現できるはず。
  push() で追加、pop() で削除する。
*/

struct tree {
  void* value;
  struct tree* next;
};

typedef void* H_TREE;

/**
    ツリーハンドラの作成。
*/
H_TREE createTree();

/**
    ツリーハンドラの次の値を返却する。
  
  _tree： カレントツリー
*/
H_TREE hasNextTree(H_TREE _tree);

/**
    ツリーハンドラのポインタを最後尾に移動する。
  
  _tree： カレントツリー
*/
H_TREE moveLast(H_TREE _tree);

/**
    ツリーハンドラの要素数と根の合計数を返却する。
    根（root）は要素を持たないツリーだが、countTree() は根も
    含めてそのサイズを返却する。つまり、その値は根 + 要素数と
    なる。
  
  _root： ルートツリー
*/
size_t countTree(H_TREE _root);

/**
    ツリーハンドラの全要素の削除を行う。
    根も削除する。
    ※ もし、H_TREE が管理する value が動的にメモリ確保されたもので、H_TREE 以外そのアドレスを知り得ない場合
    この関数を value 解放前に行うとメモリリークを引き起こす：）
  
  _root： ルートツリー
  count： ルートツリーを含めた、全要素数
*/
void clearTree(H_TREE _root, size_t count);

/**
    ツリーハンドラに値を追加する。
  
  _root： ルートツリー
  value： ツリーに追加する値
*/
H_TREE pushTree(H_TREE _root, void* value);

/**
    ツリーハンドラに設定した値の取得。
  
  _current： カレントツリー
*/
void* treeValue(H_TREE _current);

/**
    最後尾にある値の取り出しとそのツリーハンドラの削除を行う。
  Stack と同じ動作、最初にツリーハンドラに登録した値は、最後に取り出される（First-in Last-out）。
  
  _root： ルートツリー
*/
void* popStack(H_TREE _root);

/**
    起点の次、仮の先頭の値の取り出しとそのツリーハンドラの削除を行う。
  queue と同じ動作（First-in First-out）。
    
  _root： ルートツリー
*/
void* popQueue(H_TREE _root);









//
// H_TREE 以外の宣言、定義はここから
//


//static jmp_buf jb;

void debug_int(const char* _message, const int* _debug) {
  printf("DEBUG: %s\tval: %d\taddr: %p\n", _message, *_debug, (void*)_debug);  
}

void debug_double(const char* _message, const double* _debug) {
  printf("DEBUG: %s\tval: %lf\taddr: %p\n", _message, *_debug, (void*)_debug);  
}

void debug_long(const char* _message, const void* _debug) {
  // -Werror=array-bounds これになる可能性がある、warning だけど、コンパイルオプションで エラーにしている：）
  // 例えば、実引数に int 型の変数を指定した場合。
  size_t* psz = (size_t*)_debug;
  printf("DEBUG: %s\tval: %lu\taddr: %p\n", _message, *psz, _debug);
}


int test_debug_prints() {
  puts("=== test_debug_prints");
  int    i    = 3;
  size_t size = 6;
  double pi   = 3.141592;
  debug_int("i \tis "    , &i);
  debug_long("size \tis ", &size);
  debug_double("pi \tis ", &pi);
  return EXIT_SUCCESS;
}

int test_H_TREE_basic_usage_stack() {
  puts("=== test_H_TREE_basic_usage_stack");
  H_TREE root = createTree();
  
  int n1 = 3;
  pushTree(root, &n1);
  int n2 = 6;
  pushTree(root, &n2);
  int n3 = 9;
  pushTree(root, &n3);
  
  H_TREE tmp = root;
  while((tmp = hasNextTree(tmp)) != NULL) {
    int* rn = (int*)treeValue(tmp);
    debug_int("rn is ", rn);
  }
  
  int* pn = NULL; 
  pn = (int*)popStack(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popStack(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popStack(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popStack(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  } else {
    printf("pn is NULL.\n");
  }
  size_t size = countTree(root);
  assert(size == 1);
  debug_long("size is ", &size);
  clearTree(root, size);
  return EXIT_SUCCESS;
}

int test_H_TREE_basic_usage_queue() {
  puts("=== test_H_TREE_basic_usage_queue");
  H_TREE root = createTree();
  
  int n1 = 3;
  pushTree(root, &n1);
  int n2 = 6;
  pushTree(root, &n2);
  int n3 = 9;
  pushTree(root, &n3);
  
  H_TREE tmp = root;
  while((tmp = hasNextTree(tmp)) != NULL) {
    int* rn = (int*)treeValue(tmp);
    debug_int("rn is ", rn);
  }
  
  int* pn = NULL; 
  pn = (int*)popQueue(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popQueue(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popQueue(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  }
  pn = (int*)popQueue(root);
  if(pn != NULL) {
    debug_int("pn is ", pn);
  } else {
    printf("pn is NULL.\n");
  }
  size_t size = countTree(root);
  assert(size == 1);
  debug_long("size is ", &size);
  clearTree(root, size);
  return EXIT_SUCCESS;
}




int main(void) {
  puts("START H_TREE のブラッシュアップとその動作確認 ===");
  if(0.01) {
    int ret = 0;
    printf("Play and Result ... \t%d\n", ret = test_debug_prints());
    assert(ret == 0);
  }
  if(1.00) {
    int ret = 0;
    printf("Play and Result ... \t%d\n", ret = test_H_TREE_basic_usage_stack());
    assert(ret == 0);
    printf("Play and Result ... \t%d\n", ret = test_H_TREE_basic_usage_queue());
    assert(ret == 0);
  }
  puts("===   H_TREE のブラッシュアップとその動作確認  END");
  return 0;
}


H_TREE createTree() {
  puts("--------- createTree");
  struct tree* pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = NULL;
  pt->next = NULL;
  return (H_TREE)pt;
}

H_TREE hasNextTree(H_TREE _tree) {
  return (H_TREE)((struct tree*)_tree)->next;
}

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

size_t countTree(H_TREE _root) {
  puts("--------- countTree");
  struct tree* current = (struct tree*)_root;
  size_t i = 0;
  while((current = hasNextTree(current)) != NULL) {
    i++;
  }
  i += 1;     // これは root も含めて返却している。
  return i;
}

void clearTree(H_TREE _root, size_t count) {  // このことは「肝に銘じよ」C 言語では削除する対象のサイズを先に計算しろ。
  puts("--------- clearTree");
  H_TREE array[count];    // この配列の宣言のやり方は GCC 以外でもできるのかな？ 添字に変数を利用しているんだよね。
  struct tree* current = (struct tree*)_root;
  array[0] = current;
  size_t i = 1;
  while((current = hasNextTree(current)) != NULL) {
    array[i] = current;
    i++;
  }
  for(i=0; i<count; i++ ) {
//    puts("------------ D");
    free(array[i]);
  }
}

H_TREE pushTree(H_TREE _root, void* _value) {
  puts("--------- pushTree");
  struct tree* pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = _value;
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

void* treeValue(H_TREE _current) {
  puts("--------- treeValue");
  if(_current != NULL) {
    return ((struct tree*)_current)->value;
  } else {
    return NULL;
  }
}

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
    while((current = (H_TREE)hasNextTree((H_TREE)current)) != NULL) {
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

