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

int main(void) {
  puts("START void ポインタについて ===");
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
  puts("===   void ポインタについて   END");
  return 0;
}
