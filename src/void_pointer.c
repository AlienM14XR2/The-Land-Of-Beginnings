/**
  課題
 void ポインタについて
 
 gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror void_pointer.c -o ../bin/main
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

typedef void* H_FOO;                                         // 何らかのデータのハンドリングを表現したもの
H_FOO creatFoo(const size_t id, const char* email);          // ハンドラ生成（メモリの動的取得）
void freeFoo(H_FOO foo);                                     // ハンドラのメモリ解放
int doSomething(H_FOO foo);                                  // ハンドラを利用した何らかの処理

struct foo {
  size_t id;
  char email[256];
};

H_FOO createFoo(const size_t id, const char* email) {
  puts("--------- createFoo");
  printf("sizeof(struct foo): \t%lu\n", sizeof(struct foo));
  struct foo* pf = (struct foo*)malloc(sizeof(struct foo));
  pf->id = id;
  
  memset(pf->email, '\0', 256);
  size_t size_email = strlen(email);
  printf("size_email is %lu\n", size_email);
  if(size_email < 256) {
    strcat(pf->email, email);
  }
  printf("H_FOO addr is \t%p\n", (void*)pf);
  return (H_FOO)pf;
}

int doSomething(H_FOO foo) {
  puts("--------- doSomething");
  printf("id is \t%lu\n"   , ((struct foo*)foo)->id);
  printf("email is \t%s\n" , ((struct foo*)foo)->email);
  return 0;
}

void freeFoo(H_FOO foo) {
  puts("--------- freeFoo");
  printf("H_FOO addr is \t%p\n", foo);
  free(foo);
}

int test_FOO_Handler() {
  puts("====== test_FOO_Handler");
  H_FOO hf = createFoo(3ul, "foo@loki.org");
  doSomething(hf);
  freeFoo(hf);
  return 0;
}

/**
    上記のように void* を利用すれば、独自の型（なんでもあり）を表現でき、ハンドラ関数ではその独自型の実体、上例では
  struct foo* としてアクセスし、カプセル化を実現できる。だたし、これは C 言語なので、紳士協定違反はいくらでも可能
    であろう。
*/

/**
    別件だが、void* を利用すれば、debug 出力が楽に書けないだろうか。
    という疑問。
    結論、long 系以外はやはり別途用意するしかなさそうだ。
*/


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


struct sample {
  int  i;
  long l;
  char array[256];
  char* cp;
};


int test_memset(void) {
  /**
        汎用ポインタとして「void型ポインタ」を使っている代表的なライブラリ関数
    void* memset(void* dst, int val, size_t size);
        
  */    
  puts("====== test_memset");
  char moji[256];
  void* ret = memset(moji, '\0', 256);   // 内部で、各型のポインタで型キャストしている。
  strcat(moji, "foo");
  printf("moji is %s\taddr is %p\n", moji, (void*)moji);
  printf("void* ret \taddr is %p\n", ret);
  printf("sizeof(moji) is %lu\n", sizeof(moji));
  printf("sizeof(ret) is %lu\n", sizeof(ret));
  return 0;
}

int test_sizeof() {
  puts("====== test_sizeof");
  puts("M14xR2 Ubuntu 64 bits.");
  printf("sizeof(int)            is %lu\n", sizeof(int));
  printf("sizeof(unsigned int)   is %lu\n", sizeof(unsigned int));
  printf("sizeof(long)           is %lu\n", sizeof(long));
  printf("sizeof(unsigned long)  is %lu\n", sizeof(unsigned long));
  printf("sizeof(double)         is %lu\n", sizeof(double));
  printf("sizeof(char)           is %lu\n", sizeof(char));
  printf("sizeof(unsigned char)  is %lu\n", sizeof(unsigned char));
  printf("sizeof(int*)           is %lu\n", sizeof(int*));
  printf("sizeof(long*)          is %lu\n", sizeof(long*));
  printf("sizeof(double*)        is %lu\n", sizeof(double*));
  printf("sizeof(char*)          is %lu\n", sizeof(char*));
  printf("sizeof(void*)          is %lu\n", sizeof(void*));

  // int, long, char[] 256, char*  
  // 4 bytes, 8 bytes, 256 bytes, 8 bytes ... 276  
  struct sample s_1 = {0, 1l, "s_1", NULL};
  struct sample* sp = &s_1;
  printf("sizeof(s_1)            is %lu\n", sizeof(s_1));
  printf("sizeof(sp)             is %lu\n", sizeof(sp));
  printf("sizeof(struct sample)  is %lu\n", sizeof(struct sample));
  printf("sizeof(struct sample*) is %lu\n", sizeof(struct sample*));
  /**
        私の環境ではポインタは 8 bytes
  */
  return 0;
}



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



/**
  struct tree* を新規作成し、next に NULL を設定する。 
    第一仮引数に NULL を許可し、その場合は Tree 構造の始まりとする。
  
  _trunk： Tree 構造の開始地点
  _value： 値
    戻り値： 新規作成された  tree のアドレス
*/

struct tree* tree_add(struct tree* _trunk, void* _value) {
  puts("--------- tree_add");
  struct tree* pt = NULL;
  pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = _value;
  pt->next = NULL;
  if(_trunk != NULL) {
    _trunk->next = pt;    
  }
  return pt;
}

struct tree* tree_move_last(struct tree* _trunk) {
  puts("--------- tree_move_last");
  struct tree* next     = NULL;
  struct tree* current  = NULL;
  current = _trunk;
  next    = _trunk->next;
  while(next != NULL) {
    if(next->next != NULL) {
      current = next;
      next    = next->next;
    } else {
      break;
    }
  }
  // DEBUG
  debug_int("current  value is ", (int*)current->value);
  printf("current addr is \t%p\n", (void*)current);
  if(next != NULL) {
    debug_int("next value is ", (int*)next->value);
    printf("next addr is \t%p\n", (void*)next);
  }
  // RESULT
//  if(next == NULL) {
//    return current;
//  } else {
//    return next;
//  }
  return next;
}

/**
    最初の struct tree* を削除する。
    削除対象の value を返却する。Queue に相当する動き。
  _cursor は DEBUG 用
*/
void* tree_remove_first(struct tree* _trunk, struct tree* _cursor) {
  puts("--------- tree_remove_first");
  struct tree* next   = NULL;
  void*        value  = NULL;
  printf("_trunk addr is \t%p\n", (void*)_trunk);
  if(_trunk != NULL) {
    value = _trunk->value;
    next  = _trunk->next;
    free((void*)_trunk);
    if(next == NULL) {
      printf("next is null.\n");
    } else {
      *_cursor = *next;
    }
  }
  return value;
}

void* tree_remove_last(struct tree* _trunk) {
  puts("--------- tree_remove_last");
  struct tree* next     = NULL;
  struct tree* current  = NULL;
  current = _trunk;
  next    = _trunk->next;
  while(next != NULL) {
    if(next->next != NULL) {
      current = next;
      next    = next->next;
    } else {
      break;
    }
  }
  if(next != NULL) {
    void* value = next->value;
    free((void*)next);
    current->next = NULL;
    return value;
  }    
  return NULL;
}

/**
    すべての struct tree* を削除する。
*/
void tree_clear(struct tree* _trunk) {
}

int test_tree() {
  puts("====== test_tree");
  int v1 = 3;
  int v2 = 6;
  int v3 = 9;
  int v4 = 12;
  struct tree* cursor = NULL;
  struct tree  trunk  = {&v1, NULL};
  struct tree* trunk1 = NULL;
  struct tree* trunk2 = NULL;
  struct tree* trunk3 = NULL;
  cursor = &trunk;
  
  trunk1 = tree_add(&trunk, &v2);
  printf("trunk1 addr is \t%p\n", (void*)trunk1);
  trunk2 = tree_add(trunk1, &v3);
  printf("trunk2 addr is \t%p\n", (void*)trunk2);
  trunk3 = tree_add(trunk2, &v4);
  printf("trunk3 addr is \t%p\n", (void*)trunk3);
  if(trunk.next != NULL) {
    if(trunk.next->next != NULL) {
      printf("trunk.next->next->value is %d\n", *(int*)trunk.next->next->value);
    }
  }
  
  cursor = tree_move_last(&trunk);
  printf("cursor value is \t%d\n", *(int*)cursor->value);
  
  int* r3 = tree_remove_last(&trunk);
  debug_int("r3 is ", r3);
  
  int* r1 = tree_remove_first(trunk1, cursor);
  debug_int("r1 is ", r1);
  int* r2 = tree_remove_first(trunk2, cursor);
  debug_int("r2 is ", r2);
  return 0;
}

/**
    適当に作るにも程がある、我ながらイケてないと思うので、次回以降仕様から見直して作り直そう。
  Root をもとに追加、削除ができないと使い物にはならないだろう。
*/

typedef void* H_TREE;

H_TREE createTree(void* value) {
  puts("--------- createTree");
  struct tree* pt = (struct tree*)malloc(sizeof(struct tree));
  pt->value = value;
  pt->next = NULL;
  return (H_TREE)pt;
}

H_TREE hasNext(H_TREE _tree) {
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
  printf("last addr is \t%p\n", (void*)last);
  return (H_TREE)last;
}

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

void* popTree(H_TREE _root) {
  puts("--------- popTree");
  // 前方アドレスの付け替え後、削除する。
  void* value = NULL;
  struct tree* last     = (struct tree*)moveLast(_root);
  struct tree* current  = (struct tree*)_root;
  if(current == last) {
    printf("------------ F1 SAME\n");
    value   = last->value;
    current = NULL;
    free((void*)last); 
  }
  else if(current->next == last) {
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

int test_H_TREE() {
  puts("====== test_H_TREE");
  int a1 = 3;
  H_TREE root = createTree(&a1);
  printf("root addr is \t%p\n", root);
  int a2 = 6;
  pushTree(root, &a2);
  int a3 = 9;
  pushTree(root, &a3);
  int a4 = 12;
  pushTree(root, &a4);
  
  H_TREE current = root;
  debug_int("current->value is ", (int*)((struct tree*)current)->value);    
  while((current = hasNext(current)) != NULL) {
    debug_int("current->value is ", (int*)((struct tree*)current)->value);    
  }
  
  int* pi = popTree(root);
  debug_int("pi is ", pi);
  pi = popTree(root);
  debug_int("pi is ", pi);
  pi = popTree(root);
  debug_int("pi is ", pi);
  pi = popTree(root);
  debug_int("pi is ", pi);
//  pi = popTree(root);   // このコメントアウトを外すと バスエラー (コアダンプ)

  return 0;
}


int main(void) {
  puts("START void ポインタについて ===");
  if(0.01) {
    long x = 33;
    debug_long("x is ", (void*)&x);
    unsigned long xx = 66;
    debug_long("xx is ", (void*)&xx);
    size_t xxx = 99;
    debug_long("xxx is ", (void*)&xxx);
    
    int  y = 6;
    debug_int("y is ", &y);
    double pi = 3.141592;
    debug_double("pi is ", &pi);
  }
  if(1.00) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_memset());
    assert(ret == 0);
    printf("Play and Result ... %d\n", ret = test_sizeof());
    assert(ret == 0);
  }
  if(1.01) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_FOO_Handler());
    assert(ret == 0);
  }
  if(1.02) {  // 1.02
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_tree());
    assert(ret == 0);
  }
  if(1.03) {  // 1.03
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_H_TREE());
    assert(ret == 0);
  }
  puts("===   void ポインタについて   END");
  return 0;
}
