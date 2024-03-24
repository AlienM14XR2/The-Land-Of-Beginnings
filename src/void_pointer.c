/**
  課題
 void ポインタについて
 
 gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror void_pointer.c -o ../bin/main
*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>



int test_memset(void) {
  /**
        汎用ポインタとして「void型ポインタ」を使っている代表的なライブラリ関数
    void* memset(void* dst, int val, size_t size);
        
  */    
  puts("------ test_memset");
  char moji[256];
  void* ret = memset(moji, '\0', 256);   // 内部で、各型のポインタで型キャストしている。
  strcat(moji, "foo");
  printf("moji is %s\taddr is %p\n", moji, (void*)moji);
  printf("void* ret \taddr is %p\n", ret);
  
  return 0;
}

int main(void) {
  puts("START void ポインタについて ===");
  if(1.00) {
    int ret = 0;
    printf("Play and Result ... %d\n", ret = test_memset());
    assert(ret == 0);
  }
  puts("===   void ポインタについて   END");
  return 0;
}
