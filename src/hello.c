/**
 * hello.c
 * 
 * - 進め方を考えるが、基本姿勢は初心者であること。（変なプライドは捨てる。
 * - 変数、関数、ポインタ、アドレス、知ってるが忘れる。
 * - C++ もここでは忘れる。
 * - 標準関数を使い倒す。（誤解をなくせるかな。
 * - 飽きたら、設計してみる。
 * - やってみたいことに素直に、正直に、そしてすぐにやってみよう。
 * - 不便を感じた瞬間に作ってみる。
 * - 調べることも重要、しかし今回は試行錯誤を繰り返し、無駄を楽しむ。
 * - これは、悩んだが、書き方は C の作法、C文化を尊重する。
 *   - Member getMember () ではなく、Member get_member() {} で書いてみる。
 *   - 自分が後でも理解できるように、変数名は極力 p, a, b, n, c, cnt, sz, 等の略式は極力避ける。
 * 
 * - 
 *  
 * https://9cguide.appspot.com/r_lib.html
 * 
 * 
 * 
*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"

// 毎回 printf() で 改行コードを入力するのは面倒だ。
// テンプレート出力してくれる関数がほしい、これが欲求だ。
// 欲求に答えるのは自分、すぐに実践、実行する。

// stdio.h
void test_strncpy() {
    printf("--------------- test_strncpy ");
    char buff[256];
    strncpy( buff, "12345",  4);
    printf("strncpy( buff, \"12345\",  4) is ... %s\n", buff);
    strncpy( buff, "12345",  6);
    printf("strncpy( buff, \"12345\",  6) is ... %s\n", buff);
    strncpy( buff, "12345",  256);
    printf("strncpy( buff, \"12345\",  256) is ... %s\n", buff);
    // つまり、こうゆうことか、__src より __n が小さいと'\0' ヌル文字で埋めてくれない。
    // ではやはり、次が必要だろ。
    for(int i = 0; i < 256 ; i++) {
        buff[i] = '\0';
    }
    strncpy( buff, "12345",  4);
    printf("strncpy( buff, \"12345\",  4) is ... %s\n", buff);
}

/**
 * テンプレート出力関数。
 * 
 * const char* message を改行コード付きで出力する。
*/
void print_template( const char* message) {
    printf("%s \n",message);
    // int len = strlen(message);
    // printf("ren is %d \n",len);
    // int size = len;
    // char buff[size];
    // for(int i = 0; i < size ; i++) {
    //     buff[i] = '\0';
    // }
}
// DEBUG 用もほしい。

/**
 * デバッグ int を出力する。
*/
void debug_print_d(const char* message, int debug) {
    printf("DEBUG: %s\t %d\n",message, debug);
}
/**
 * デバッグ const char* を出力する。
*/
void debug_print_s(const char* debug ) {
    printf("DEBUG: %s\n",debug);
}
// だいたいここで気づく、これどうにかならないかなと。

int main(void) {
    printf("START =============== \n");
    printf("Hello C. \t I had came back. \n");

    print_template("これ動くぞ。");
    debug_print_d("これが俺のやり方だ。", 9);
    debug_print_s("これをいちいち作らなアカンのか？");
    test_strncpy();
    printf("=============== END \n");
    return 0;
}