/**
  課題
 
 H_TREE のブラッシュアップとその動作確認用ソース。
 最終的には H_TREE を宣言と定義に切り出すこと。
 
 e.g. compile
 gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror -I../inc/ h_tree.c h_tree_proto.c -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <setjmp.h>
#include "h_tree.h"




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



