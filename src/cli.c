/**
    CLI (Command Line Interface) 
    C 標準入出力、主に出力にフォーカスして、学習を進める。
    　参考にするのは、MySQL, PostGreSQL の表現とする。
    　基本は、コマンドになる、コマンド、イコール、関数であろう。
    
    　もし、CREATE DATABASE に相当するものが、これで必要な場合は、それは、アプリの初期値の
    　設定だと思う、無論、今今の話ではない。
    
    　便利だと思ったのはMySQL に存在（PostgreSQL にもある）する、上下、↑、↓による、記憶
    　された、コマンドの表示だ。
    
    @Author Jack    
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define CMD_SIZE 1024
#define CMD_SPLIT_SIZE 32

typedef struct {
    char data[CMD_SPLIT_SIZE];
} FILE_DATA; 

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
int cmd_exit(char*);
int cmd_create(char*);
int upper_str(const char*, char*);
int init_cmd(char*);
int init_io(char*,char*);
int monitoring() {
    char cmd[CMD_SIZE]={'\0'};
    char cmd_upper[CMD_SIZE]={'\0'};
    printf("ORx2> ");    
    scanf("%s", cmd);
    while(1) {
        upper_str(cmd,cmd_upper);
//        ptr_str_debug("cmd_upper is",cmd_upper);
        // handler には必ず、Upper された文字列を実引数にすること。
        if( handler(cmd_upper) == 1 ) {   // 1 が返却された時はループを抜ける。
            break;
        }
        init_io(cmd,cmd_upper);
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
int init_io(char* cmd,char* cmd_upper) {
    printf("ORx2> ");    
    init_cmd(cmd);
    init_cmd(cmd_upper);
    scanf("%s", cmd);
    return 0;
}
int handler(char* cmd) {
    if(cmd_exit(cmd) == 1) {
        return 1;
    }
    cmd_create(cmd);
    return 0;
}
int cmd_exit(char* cmd) {
    if(strcmp("EXIT",cmd) == 0) {
        println("Bye :)");
        return 1;
    }
    return 0;
}
int cmd_create(char* cmd) {
    // ここからはTrim して半角スペースの除去が必要かもしれない。
    if(strcmp("CREATE",cmd) == 0) {
        println("It's create.");
    }
    return 0;
}
/**
    is End of Command.
        入力されたコマンドの終端を検知する。
    0 is no hit.
    1 is hit.
*/
int is_eoc(const char* c) {
    if(*c == ';' || *c == '\0') {
        return 1;
    }
    return 0;
}

//
// ここからテスト用関数です。
//
int test_split_string() {
    println("--------------------------------------- test_split_string");
    // 区切り文字（Delimiter ）は決める必要がある。
    // ひと固まりの文字列がある。
    // Delimiter で分割する。（オリジナルはそのままにしておく、cmd_upper ならそのまま編集してもいいか：）
    // 分割されたものは、各々配列に入れ直す。
    println("INSERT () = ();");
    char cmd_upper[256] = {"INSERT () = ();"};
    int count = 1;
    for(int i = 0;;i++) {
        if(cmd_upper[i] == ' ') {
            count++;
        } else if(is_eoc(&cmd_upper[i])) {
            break;
        }
    }
    ptr_d_debug("count is ",&count);
    FILE_DATA fdata[count];
    // もう一度ループ解析して、今度は、動的に確保したFILE_DATA に分割したコマンドを代入していく。
    
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
    if(2) {     // 細々とした作り込みが必要な場合のテスト、動確のために用意した。
        // 文字列のスプリット、これが非常によかった、考え方のね。
        // https://qiita.com/IKEH/items/5f8a3047cfeee5c74574
        test_split_string();
    }
    if(0) {
        // CLI の無限ループ
        monitoring();
        // Command によりループを脱出できる
    }
    println("=============== Command Line Interface END");
    return 0;
}
