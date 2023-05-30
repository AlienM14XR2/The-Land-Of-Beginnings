/**
    CLI (Command Line Interface) 
    C 標準入出力、主に出力にフォーカスして、学習を進める。
    
         参考にするのは、MySQL, PostGreSQL の表現とする。
    　基本は、コマンドになる、コマンド、イコール、関数であろう。
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

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

int handler(char*);
int cmd_exit(void);
int upper_str(const char*, char*);
int init_cmd(char*);
int monitoring() {
    char cmd[256]={'\0'};
    char cmd_upper[256]={'\0'};
    printf("ORx2> ");    
    scanf("%s", cmd);
    while(1) {
        upper_str(cmd,cmd_upper);
//        ptr_str_debug("cmd_upper is",cmd_upper);
        if( handler(cmd_upper) == 1 ) {   // 1 が返却された時はループを抜ける。
            break;
        }
        printf("ORx2> ");    
        init_cmd(cmd);
        init_cmd(cmd_upper);
        scanf("%s", cmd);
    }
    return 0;
}
int init_cmd(char* cmd) {
    for(int i = 0; i < sizeof(cmd)/sizeof(cmd[0]); i++) {
        cmd[i] = '\0';
    }
}
int upper_str(const char* in, char* out) {
    int i = 0;
    while(in[i] != '\0') {
        out[i] = toupper(in[i]);
        i++;
    }
    return 0;
}
int handler(char* cmd) {
    if(strcmp("EXIT",cmd) == 0) {
        cmd_exit();
        return 1;
    } else if(strcmp("CREATE",cmd) == 0) {  // ここからはTrim して半角スペースの除去が必要かもしれない。
        
        println("It's create.");
    }
    return 0;
}
int cmd_exit(void) {
    println("bye.");
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
