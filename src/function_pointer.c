/**
    課題
    関数ポインタとバリエーション・ポイント
    
  GoF を C 言語で表現してみたい。OO のデザインパターンでよく登場するもの、Strategy パターン。
  これは、バリエーション・ポイントを切り出す方法で、よく登場するし、私も利用する。これを C 言語
  で表現するのが目的。
  
  この課題の前に行った、void* の利用や関数ポインタで表現できると考えている。私は C 言語のマクロ
  は詳しくはないので、今回はマクロは控えるが、これでも色々と表現可能だろうと思う。
  
  e.g. compile
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror function_pointer.c -o ../bin/main
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

#define EXIT_SUCCESS 0
#define EXIT_FAILURE 1

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


/**
    先に実装した H_TREE そのスタックとしての振る舞い。
    それをここに移植する。各関数名をその振る舞いに合わせる。
*/

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
  printf("last addr is \t%p\n", (void*)last);
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
    puts("------------ D");
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
      printf("------------ SAME\n");    
    ((struct tree*)_root)->next = pt;
  } else {
    last->next = pt;
  }
  printf("pt addr is \t%p\n", (void*)pt);
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
    printf("------------ F2 SAME\n");
    value = last->value;
    current->next = NULL;
    free((void*)last);
  } 
  else {
    while((current = (H_TREE)hasNext((H_TREE)current)) != NULL) {
      if( ((struct tree*)current)->next == last ) {
        printf("------------ SAME\n");
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
  // TODO 実装
  // 先頭の ツリーハンドラは起点なので無視する
  // 2 番目が対象であり、3 番目がある場合はそのアドレスを起点の next に代入する
  return NULL;
}


int test_tree_stack() {
  puts("=== test_tree_stack");
  H_TREE root = createTree();
  
  int n1 = 3;
  pushTree(root, &n1);
  int n2 = 6;
  pushTree(root, &n2);
  int n3 = 9;
  pushTree(root, &n3);
  int n4 = 12;
  pushTree(root, &n4);
  int n5 = 15;
  pushTree(root, &n5);
  
  H_TREE tmp = root;
  while((tmp = hasNext(tmp)) != NULL) {
    debug_int("value is ", (int*)getValue(tmp));
  }
  
  int* nr = NULL;
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("1 nr is ", nr); }
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("2 nr is ", nr); }
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("3 nr is ", nr); }
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("4 nr is ", nr); }
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("5 nr is ", nr); }
  nr = (int*)popStack(root);
  if(nr != NULL) { debug_int("6 nr is ", nr); }   // これは出力されない
  
  size_t size = countTree(root);
  debug_long("size is ", &size);
  clearTree(root, size);
  return EXIT_SUCCESS;
}


int main(void) {
  puts("START 関数ポインタとバリエーション・ポイント ===");
  if(1.00) {
    int ret = 0;
    printf("play ane Result ... %d\n", ret = test_tree_stack());
    assert(ret == 0);
  }
  puts("===   関数ポインタとバリエーション・ポイント   END");
  return EXIT_SUCCESS;
}
