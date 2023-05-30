/**
    CLI (Command Line Interface) 
    C 標準入出力、主に出力にフォーカスして、学習を進める。
    
         参考にするのは、MySQL, PostGreSQL の表現とする。
    　基本は、コマンドになる、コマンド、イコール、関数であろう。
*/
#include "stdio.h"
#include "stdlib.h"

void println(const char* message){
    printf("%s\n",message);
}
void ptr_d_debug(const char* message, int* debug) {
    printf("%s\tvalue=%d\taddr=%p\n",message,*debug,debug);
}
void ptr_f_debug(const char* message, double* debug) {
    printf("%s\tvalue=%f\taddr=%p\n",message,*debug,debug);
}


int main(void) {
    println("START Command Line Interface ===============");
    if(1) {     // デバッグ、動作確認。
        int x = 3;
        double pai = 3.141592;
        ptr_d_debug("x is ",&x);
        ptr_f_debug("pai is ",&pai);
        int* px = &x;
        double* pp = &pai;
        ptr_d_debug("px is ",px);
        ptr_f_debug("pp is ",pp);
    }
    println("=============== Command Line Interface END");
    return 0;
}
