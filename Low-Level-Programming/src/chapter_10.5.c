/**
    10.5 例：動的配列の要素の和
    malloc と free
*/
#include "stdio.h"
#include "malloc.h"

int main(void) {
    if("10.5.1") {
        puts("動的メモリ割り当て（紹介）");
        int* array;
        // malloc は割り当てたメモリの開始アドレスを返す。
        // 引数はバイトサイズであり、その場合は
        // 要素数に要素のサイズを掛けたもの。
        array = malloc(10 * sizeof(int));
        
        // ここでメモリ領域の割り当てを解放する。
        free(array);
    }
    return 0;
}
