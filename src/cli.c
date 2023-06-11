/**
    CLI (Command Line Interface) 
    C 標準入出力、主に出力にフォーカスして、学習を進める。
    　参考にするのは、MySQL, PostGreSQL の表現とする。
    　基本は、コマンドになる、コマンド、イコール、関数であろう。
    
    　もし、CREATE DATABASE に相当するものが、これで必要な場合は、それは、アプリの初期値の
    　設定だと思う、無論、今今の話ではない。
    
    　便利だと思ったのはMySQL に存在（PostgreSQL にもある）する、上下、↑、↓による、記憶
    　された、コマンドの表示だ。
    　
    　住所録や電話帳、個人情報といったものを当初管理することをイメージしていた。
    　したがって、次のデータをテストサンプルとする。
    ```　
    　name, email, tel_1, tel_2, tel_3, address, memo
    ```
        これに、アプリ固有の情報を追加する
    ```
      id, create_at, update_at    
    ```
    2023-06-09 現在は上記を正式なカラム名にする。
    
    INSERT 文の仕様を考える。
    ```
    insert into file_name(col_1,col_2,col_3) values ("val_1", "val_2", "val_3");
    ```
    - うん、最初からやり直したいな、仕様を固めて、許可することを予め決めておかないと作れない。
    - "|"" の問題をどうするか？
    - " " の問題をどうするか？    
    - ファイル名は現状空気、別に考慮していない。
    values 以下は""「ダブルクォーテション」で囲むことが必須で、
        （）の入力を許可する。
        カラム名に（）の入力は無効とする。
    - 半角スペースでコマンド分割     DONE.
    - Values より下はダブルクォートと区切り文字「,」の個数のValidation 。
    - Values より下はtoUpper の必要なし 。
        うん、今更だけど、コマンドの仕様をちゃんと決めないと駄目だよね：）
    - カラムと値の抽出保存 。
    
    
    @Author Jack    
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "ctype.h"

#define CMD_SIZE 1024
#define CMD_SPLIT_SIZE 32   // strncpy 結局分割されたコマンドが、このサイズを超えたら、問題がある、Null 文字'\0' が自動挿入されない、だから大きめに設定することを進める、また、サイズ計算を行い、超える場合はしっかりとエラーハンドリングする必要がある。

typedef struct {
    int no;
    char data[CMD_SPLIT_SIZE];
} CMD_DATA; 

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
void ptr_cstr_debug(const char* message, const char* debug) {
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
    return 0;
}
/**
    これでは、問題があることに気付いた。
  Values はユーザの任意なので、これを大文字に強制的に変換してしまうのは違う。
  したがって、別途、Values 以降の（）内の値は無視するものが必要だ。
    
*/
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

/**
    コマンドの解析
    入力されたコマンドを半角スペースで解析する。
    いつくに分割すべきなのかを予め計算する。
    関数は、基本戻り値はその処理の成功、失敗に用いる。
    よって、引数（ポインタ）で解析結果は返却する。
*/
int cmd_analyze(const char* cmd_upper, int* count) {
    // count の初期化 1 おそらくここは、cmd_upper の有無によりValidation が必要。
    *count = 1;
    for(int i = 0;;i++) {
        if(cmd_upper[i] == ' ') {
            (*count)+=1;
        } else if(is_eoc(&cmd_upper[i])) {
            break;
        }
    }
    return 0;
}
int cmd_cpy(char* dest, const char* src, const int len) {
    int i = 0;
    for(;i < len; i++) {
        dest[i] = src[i];
    }
    dest[i] = '\0';
    return 0;
}
int cmd_segment(const char* cmd_upper, CMD_DATA* fdata) {
    char tmp[CMD_SPLIT_SIZE] ={'\0'};
    int j = 0;
    int k = 0;
    int limit = strlen(cmd_upper);
    for(int i = 0; i < limit ;i++) {
        if(cmd_upper[i] != ' ' && cmd_upper[i] != ';' ) {
            tmp[j] = cmd_upper[i];
            j++;     
        } else {
            // 最後にNull 文字を追加しておく
            tmp[j] = '\0';
            // デバッグ、ここで少し、tmp のサイズが気になった：）
            ptr_str_debug("tmp is ",tmp);
            int len = strlen(tmp);
            ptr_d_debug("\tlen is ",&len);
            if(len > 0) {
                fdata[k].no = k;
                cmd_cpy(fdata[k].data,tmp,len);            
                k++;
            }
            // tmp に関するデータのリセット
            j = 0;
            init_cmd(tmp);            
        }
        if(is_eoc(&cmd_upper[i])) {
            break;
        }
    }
    return 0;
}
/**
    仮引数 in を仮引数out に大文字にして保存する（返却する）関数。
  keyword より先、start 文字からend 文字までは大文字変換を無視する。
*/
int upper_str_ignore(CMD_DATA* cmd_array, char* out, const char* keyword, const char start, const char end) {
    ptr_cstr_debug("keyword is ",keyword);
    // まず、keyword を大文字にして、それでも比較できるようにする。
    char upper_keyword[CMD_SPLIT_SIZE] = {"\0"};
    upper_str(keyword,upper_keyword);
    ptr_cstr_debug("\tupper_keyword is ",upper_keyword);
    
    int ignore = 0;
    for(int i=0;;i++) {
        if( cmd_array[i].no == -1 ) {
            break;
        }
        ptr_str_debug("cmd_array data is ",cmd_array[i].data);
        if( strcmp(keyword,cmd_array[i].data) == 0 || strcmp(upper_keyword,cmd_array[i].data) == 0 ) {
            println("Hit values or VALUES.");
            // フラグ管理になっちった。後、start いらないかも：）
            // うん、ここはもっと考察が必要だな、まだ見当がついていない。
            //　簡単にできる方法を見つける、一文字づつUpper しているので、コマンド改変になるが、変換無効のシステム予約文字みたいのを埋め込むか、それ以外か。少し時間がほしい。
//            out[i] = toupper(in[i]);
            ignore = 1;
        }
    }
    return 0;
}


//
// ここからテスト用関数です。
//
int test_split_string(const char* org_cmd, CMD_DATA* pcmd) {
    println("--------------------------------------- test_split_string");
    // 区切り文字（Delimiter ）は決める必要がある。
    // ひと固まりの文字列がある。
    // Delimiter で分割する。（オリジナルはそのままにしておく、cmd_upper ならそのまま編集してもいいか：）
    // 分割されたものは、各々配列に入れ直す。
    // --- A ここから --- コマンド解析
    ptr_cstr_debug("e.g. ",org_cmd);
    char cmd_upper[CMD_SIZE];           // ここで全てを大文字に変換するのは良くない気がしている、スプリットした後に大文字変換できるものとできないものを区別する必要があるのではないのか？
    upper_str(org_cmd, cmd_upper);
    int count = 0;
    int* pcnt = &count;
    cmd_analyze(cmd_upper, pcnt);
    ptr_d_debug("count is ", &count);
    CMD_DATA fdata[count];
    // CMD_DATA 配列のdata をまとめて初期化する
    for(int i = 0;i < count; i++) {
        fdata[i].no = -1;
        init_cmd(fdata[i].data);
    }
    // --- B ここから --- コマンド分割
    // もう一度ループ解析して、今度は、動的に確保したCMD_DATA に分割したコマンドを代入していく。
    // まずは、分割文字列の取得、表示確認から。
    cmd_segment(cmd_upper, fdata);
    // デバッグ最終確認
    for(int i = 0;i < count; i++) {
//        ptr_str_debug("data is ",fdata[i].data);
        printf("no is %d\tdata is %s\n",fdata[i].no,fdata[i].data);
        pcmd[i].no = fdata[i].no;
        int len = strlen(fdata[i].data);
        cmd_cpy(pcmd[i].data,fdata[i].data,len);
    }
    return 0;
}
int test_split_string_before_upper(const char* org_cmd, CMD_DATA* pcmd) {
    println("----------------------- test_split_string_before_upper");
    // コマンド解析
    ptr_cstr_debug("e.g. ",org_cmd);
    int count = 0;
    int* pcnt = &count;
    cmd_analyze(org_cmd, pcnt);
    ptr_d_debug("count is ", &count);
    CMD_DATA fdata[count];
    // CMD_DATA 配列のdata をまとめて初期化する
    for(int i = 0;i < count; i++) {
        fdata[i].no = -1;
        init_cmd(fdata[i].data);
    }
    // コマンド分割
    cmd_segment(org_cmd, fdata);
    // デバッグ最終確認
    for(int i = 0;i < count; i++) {
        printf("no is %d\tdata is %s\n",fdata[i].no,fdata[i].data);
        pcmd[i].no = fdata[i].no;
        int len = strlen(fdata[i].data);
        cmd_cpy(pcmd[i].data,fdata[i].data,len);
    }
    return 0;
}
int test_get_cols_vals(const CMD_DATA* cmd_array) {
    println("--------------------------------------- test_get_cols_vals");
    // 最終的には三次元配列で管理したい。
    // バイナリファイルに登録される正式なカラム名
    // ユーザ入力されたカラム名
    // ユーザ入力された値、みたいな：）、なんだやっぱり自宅は暑いな：）
    for(int i = 0;;i++) {
        if( cmd_array[i].no == -1 ) {
            break;
        }
        if(strcmp("INTO",cmd_array[i].data) == 0) {
            println("Hit.");
        }
    }
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
        const char foo[] = {"It's Foo.\0"};
        ptr_cstr_debug("const char is foo ",foo);
    }
    if(2) {     // 細々とした作り込みが必要な場合のテスト、動確のために用意した。
        // 文字列のスプリット、これが非常によかった、考え方のね。
        // https://qiita.com/IKEH/items/5f8a3047cfeee5c74574
        CMD_DATA cmd_array[512] = {-1,'\0'};
        test_split_string("insert into   file_name(   col_name_1, col_name_2) values ( val_1, val_2 );",cmd_array);
        test_split_string("insert into file_name(col_1,col_2,col_3) values (val_1, val_2, val_3);",cmd_array);
    }
    if(2.1) {
//        int upper_str_ignore(const char* in, char* out, const char* keyword, const char start, const char end)
//        CMD_DATA cmd_array[512] = {-1,'\0'};
//        test_split_string("insert into file_name(col_1,col_2,col_3) values (val_1, val_2, val_3);",cmd_array);
        char sample[] = {"insert into file_name(col_1,col_2,col_3) values (val_1, val_2, val_3);"};
        CMD_DATA cmd_array[512] = {-1,'\0'};
        for(int i = 0;i < sizeof(cmd_array)/sizeof(cmd_array[0]);i++){
            cmd_array[i].no = -1;
            cmd_array[i].data[0] = '\0';
        }
        println("Yeah here we go. --- upper_str_ignore");
        test_split_string_before_upper(sample, cmd_array);
        char out[CMD_SIZE] = {"\0"}; 
        upper_str_ignore(cmd_array, out, "values", '(', ')');
    }
    if(0) {
        // INSERT INTO を理解して動くものにする。(c1,c2,c3) vlues (v1,v2,v3)
        // Column とValue のデータを正しく抜き出す。
        // 分割文字を引数に持つ、ignore する文字を配列で引数に持つ、関数かな。       
        CMD_DATA cmd_array[512] = {-1,'\0'};
        for(int i = 0;i < sizeof(cmd_array)/sizeof(cmd_array[0]);i++){
            cmd_array[i].no = -1;
            cmd_array[i].data[0] = '\0';
        }
        test_split_string("insert into file_name(col_1,col_2,col_3) values (val_1, val_2, val_3);",cmd_array);
        // デバッグ
        println("33333333333333333333333333333");
        for(int i = 0;;i++){
            if( cmd_array[i].no == -1 ) {
                break;
            }
            ptr_d_debug("cmd_array no is ",&cmd_array[i].no);
            ptr_str_debug("\tcmd_array data is ",cmd_array[i].data);
        }
        test_get_cols_vals(cmd_array);
    }
    if(0) {
        // CLI の無限ループ
        monitoring();
        // Command によりループを脱出できる
    }
    println("=============== Command Line Interface END");
    return 0;
}
