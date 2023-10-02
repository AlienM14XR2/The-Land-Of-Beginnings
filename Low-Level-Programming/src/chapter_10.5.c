/**
    10.5 例：動的配列の要素の和
    malloc と free
    
    10.6 課題：連結リスト
      
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_10.5.c -o ../bin/main
    ```
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
int list_free(struct node* top);
struct node* list_node_first(const struct node* const current);
struct node* list_node_last(const struct node* const current);

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
int test_list_create(int val) {
    puts("--- test_list_create");
    struct node* pnode = list_create(val);
    printf("value is %d\town is %p\tpre is %p\tnext is %p\n",pnode->value,(void*)pnode,(void*)pnode->pre,(void*)pnode->next);
    list_free(pnode);
    return 0;
}
/**
        整数と、連結リストへのポインタへのポインタを受け取る。
        受け取った数で作った新しいノードを、リストの先頭へ追加する。
        例えば、前のリストが (1,2,3) で、数が 5 なら、新しいリストは (5,1,2,3)になる。
        
    list_add_front
*/
struct node* list_add_front(int val, struct node* current) {
    if(current != NULL) {
        // これは、この関数内で top node までポインタを移動させる必要がある。
        current = list_node_first(current);
        struct node* new_node = list_create(val);
        printf("value is %d\taddress is %p\n",new_node->value,(void*)new_node);
        current->pre = new_node;
        new_node->next = current;
        return new_node;
    } else {
        return NULL;
    }
}
struct node* test_list_add_front(int val,struct node* pnode) {
    puts("--- test_list_add_front");
    printf("value is %d\taddress is %p\n",pnode->value,(void*)pnode);
    struct node* current = list_add_front(val,pnode);
    puts("... after add");
    printf("value is %d\tcurrent->pre is %p\tcurrent->next is %p\n",current->value,(void*)current->pre,(void*)current->next);
    printf("value is %d\tpnode->pre is %p\tpnode->next is %p\n",pnode->value,(void*)pnode->pre,(void*)pnode->next);
    return current;
}
/**
        要素をリストの末尾に追加する。
        シグネチャは list_add_front と同じ
        
    list_add_back
*/
struct node* list_add_back(int val, struct node* pnode) {
    // リストの終端までポインタを移動する。
    struct node* current = list_node_last(pnode);
    // 最後のノードに新たに作成したノードを追加する。
    struct node* new_node = list_create(val);
    new_node->pre = current;
    current->next = new_node;
    return new_node;
}
struct node* test_list_add_back(int val, struct node* pnode) {
    puts("--- test_list_add_back");
    struct node* bottom = list_add_back(val,pnode);
    printf("DEBUG: value is %d\t%p\tpre is %p\tnext is %p\n",bottom->value,(void*)bottom,(void*)bottom->pre,(void*)bottom->next);
    return bottom;
}
/**
        指定されたインデックスの要素を返す。もしインデックスが
        リストの境界外なら 0 を返す。
        
    list_get
*/
struct node* list_get(const size_t n, struct node* list) {
    struct node* result = 0;
    // 最初に現在のノード数がいくつあるのか知る必要がある。
    return result;
}
/**
        リストの全要素に割り当てられているメモリを解放する。
        
    list_free
*/
int list_free(struct node* top) {
    if( top != NULL ) {
        puts("--- list_free");
        // ポインタをリストの終端へ移動する。
//        struct node* current = top;
//        while(1) {
//            if(current->next != NULL) {
//                current = current->next;
//            } else {
//                break;
//            }
//        }
        const struct node* current = list_node_last(top);
        printf("value is %d\taddress is %p\n",current->value,(void*)current);
        // メモリ解放を行う。
        struct node* pre = NULL;
        while(1) {
            if(current->pre != NULL) {
                pre = current->pre;
                printf("DEBUG: free target is %p\t value is %d\n",(void*)current,current->value);
                free((void*)current);
                current = pre;
            } else {
                if(current != NULL) {
                    printf("DEBUG: passed break root.\n");
                    printf("DEBUG: free target is %p\t value is %d\n",(void*)current,current->value);
                    free((void*)current);
                }
                break;
            }
        }
        printf("... DONE free.\n");
    }
    return 0;
}
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

//
// ここからは、課題で具体的には示されていない関数、個人的に必要だと思ったもの。
// 考え方はシンプルに DRY の原則だ。
//

/**
        第一仮引数に 任意のノードのポインタを受け取り
        リストの終端のノードのポインタを返却する。
*/
struct node* list_node_last(const struct node* const current) {
    const struct node* last = current;
    if(last != NULL) {
        while(1) {
            if(last->next != NULL) {
                last = last->next;
            } else {
                break;
            }
        }
        
    }
    return (struct node*)last;
}
/**
        第一仮引数に任意のノードのポインタを受け取り
        リストの先頭のノードのポインタを返却する。
*/
struct node* list_node_first(const struct node* const current) {
    const struct node* first = current;
    if(first != NULL) {
        while(1) {
            if(first->pre != NULL) {
                first = first->pre;
            } else {
                break;
            }
        }
    }
    return (struct node*)first;
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
        struct node* list = list_create(n);
        int a = 6;
        struct node* current = test_list_add_front(a, list);
        printf("Play and Result ... test_list_add_front(%d,list) current is %p\n",a,(void*)current);
        int b = 9;
        current = test_list_add_back(b, list);
        printf("Play and Result ... test_list_add_back(%d,list) current is %p\n",b,(void*)current);
        int c = 33;
        current = test_list_add_front(c, list);
        printf("Play and Result ... test_list_add_front(%d,list) current is %p\n",c,(void*)current);
        
        list_free(current);
    }
    puts("=== END 10.5");
    return 0;
}
