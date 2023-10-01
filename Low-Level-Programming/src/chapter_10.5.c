/**
    10.5 例：動的配列の要素の和
    malloc と free
*/
#include "stdio.h"
#include "malloc.h"

int init_array(int* array, size_t size) {
    size_t i;
    for(i = 0; i < size; i++) {
        array[i] = 0;
    }
    return 0;
}
int main(void) {
    if("10.5.1") {
        puts("動的メモリ割り当て（紹介）");
        int* array;
        size_t size = 10;
        // malloc は割り当てたメモリの開始アドレスを返す。
        // 引数はバイトサイズであり、その場合は
        // 要素数に要素のサイズを掛けたもの。
        array = malloc(size * sizeof(int));
        
        init_array(array,size);
        for(size_t i = 0; i < size; i++) {
            printf("array[%lu] is %d\taddress is %p\n",i,array[i],(void*)&array[i]);
        }
        // ここでメモリ領域の割り当てを解放する。
        free(array);
    }
    return 0;
}
