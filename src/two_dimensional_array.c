/**
    二次元配列と二重ポインタの学習
    
    これは、やったと思うが完全に記憶にない、やったことないのかもしれない：）
    二次元配列と二重ポインタは別々で扱ったことがあったが、併用したことがないのかな。
    だから、ここではっきりさせる、自分の分からない部分を、そして改善する。
  
    この考え方は面白い：）  
  https://qiita.com/chihayafuru/items/6647bed415121c62c8dd
  二次元配列もポインタで一次元配列のように扱ってしまう。
    
*/
#include "stdio.h"
#include "stdlib.h"
#define ROWS 2
#define COLS 4

void println(const char* message) {
    printf("%s\n",message);
}
void ptr_d_debug(const char* message, int* debug) {
    printf("%s\tvalue is %d\t addr is %p\n",message,*debug,debug);
}
void ptr_str_debug(const char* message, char* debug) {
    printf("%s\tvalue is %s\t addr is %p\n",message,debug,debug);
}
int test_two_dimensional_array() {
    println("-------------------------------------- test_two_dimensional_array");
    int square[ROWS][COLS] = {
        {1,2,3,4},        
        {11,12,13,14}        
    };
    int (*top_of_rows)[COLS];
    int *top_of_cols;
    top_of_rows = square;
    top_of_cols = top_of_rows[1];
    
    ptr_d_debug("square[1][1] is ",&top_of_cols[1]);
    // これは目から鱗ですよ：）
    // 次のものは少し冗長に感じてしまうかもしれないが、ポインタ配列を実践してみる。
    // これも参考サンプルのまんま：）
    return 0;
}
int test_two_dimensional_array_func(int** top_of_cols);
int test_two_dimensional_array_pointer_array() {
    println("-------------------------------------- test_two_dimensional_array_pointer_array");
    int square[ROWS][COLS] = {
        {1,2,3,4},
        {11,12,13,14}
    };
    
    // ポインタ配列
    int *top_of_cols[ROWS];
    top_of_cols[0] = square[0];
    top_of_cols[1] = square[1];
    
    ptr_d_debug("square[0][1]",&top_of_cols[0][1]);
    ptr_d_debug("square[1][1]",&top_of_cols[1][1]);
    
    test_two_dimensional_array_func(top_of_cols);
    
    return 0;

}
int test_two_dimensional_array_func(int** top_of_cols) {
    println("-------------------------------------- test_two_dimensional_array_func");
    ptr_d_debug("square[0][1]",&top_of_cols[0][0]);
    ptr_d_debug("square[1][1]",&top_of_cols[1][0]);
    // 理解したよ、うん、スッキリした。
    return 0;
}
int main(void) {
    println("START TWO DIMENSIONAL ARRAY ===============");
    if(1) {
        int x = 3;
        int* px = &x; 
        ptr_d_debug("px ... ",px);
        char moji[] = {"ABCDEFG."};
        ptr_str_debug("moji ... ",moji);
    }
    if(2) {
        test_two_dimensional_array();
    }
    if(3) {
        test_two_dimensional_array_pointer_array();
    }
    println("=============== TWO DIMENSIONAL ARRAY END");
    return 0;
} 
