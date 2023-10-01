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
/**
    10.6 課題：連結リスト
*/
struct node {
    int value;
    struct node* pre;
    struct node* next;
};
/**
        整数を受け取る、連結リストの新しいノード（node）を作って、それへのポインタを返す。
*/
struct node* list_create(int val) {
    struct node* new_node = malloc(1 * sizeof(struct node));
    new_node->value = val;
    new_node->pre = NULL;
    new_node->next = NULL;
    return new_node;
}
/**
        整数と、連結リストへのポインタへのポインタを受け取る。
        受け取った数で作った新しいノードを、リストの先頭へ追加する。
        例えば、前のリストが (1,2,3) で、数が 5 なら、新しいリストは (5,1,2,3)になる。
        
    list_add_front
*/
/**
        要素をリストの末尾に追加する。
        シグネチャは list_add_front と同じ
        
    list_add_back
*/
/**
        指定されたインデックスの要素を返す。もしインデックスが
        リストの境界外なら 0 を返す。
        
    list_get
*/
/**
        リストの全要素に割り当てられているメモリを解放する。
        
    list_free
*/
/**
        リストを受取その長さを計算する。
        
    list_length
*/
/**
        リストとインデックスを受け取り、そのインデックスに相当する
        ノードのリスト構造体へのポインタを返す。もしインデックスが大きすぎたら、NULL を返す。
        
    list_node_at
*/
/**
        リストを受け取り、要素の合計を返す。
        
    list_sum
*/
int test_list_create(int val) {
    puts("--- test_list_create");
    struct node* pnode = list_create(val);
    printf("value is %d\tpre is %p\tnext is %p\n",pnode->value,(void*)pnode->pre,(void*)pnode->next);
    return 0;
}
int main(void) {
    if("10.5.1") {
        puts("動的メモリ割り当て（紹介）---------");
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
    if("10.6.1 課題") {
        puts("課題：連結リスト ---------");
        int n = 3;
        printf("Play and Result ... test_list_create(%d) is %d\n",n,test_list_create(n));
    }
    return 0;
}
