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
void ptr_lf_debug(const char* message, double* debug) {
    printf("%s\tvalue=%lf\taddr=%p\n",message,*debug,debug);
}
void ptr_str_debug(const char* message, char* debug) {
    printf("%s\tvalue=%s\taddr=%p\n",message,debug,debug);
}

int monitoring() {
    char cmd[256]={'\0'};
    printf("ORx2> ");    
    scanf("%s", cmd);
    ptr_str_debug("cmd is ",cmd);
}
int cmd_exit() {
    return 0;
}



int main(void) {
    println("START Command Line Interface ===============");
    if(1) {     // デバッグ、動作確認。
        int x = 3;
        double pai = 3.141592;
        ptr_d_debug("x is ",&x);
        ptr_lf_debug("pai is ",&pai);
        int* px = &x;
        double* pp = &pai;
        char str[256] ="I'm Jack.\n";
        ptr_d_debug("px is ",px);
        ptr_lf_debug("pp is ",pp);
        ptr_str_debug("str is ",str);
    }
    // CLI の無限ループ
    monitoring();
    // Command によりループを脱出できる
    println("=============== Command Line Interface END");
    return 0;
}
