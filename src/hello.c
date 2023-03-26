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
    printf("--------------- test_strncpy \n");
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
// 気分転換でエディタを替えてみた、少しだけ、vim 使ってみる。
//
// すぐに、vim の賢さを知り驚く、何この子：）
// 

/*
 * 自然数の和
 * e.g. (1+100)*100/2 = 5050
 * 公式は次のもの 1/2n(n+1)
 *
 * 関数にしてみる。
 *
 * n は自然数を指定する。
 * */
int sum_of_natural_numbers(int n) {
    return (n+1)*n/2;
}
void test_Sum_Of_Natural_Numbers() {
    print_template("---------------- test_Sum_Of_Natural_Numbers");
    
    int d = sum_of_natural_numbers(100);
    debug_print_d("自然数100までの和は？",d);

}
// 実数、（浮動小数点方式）numbers Floating point method
// 実数の計算は整数の計算より遅い、コンピュータの苦手分野だ。
void sample_Numbers_Floating_Point_Method() {
    printf("--------------------- sample_Numbers_Floating_Point_Method \n");
    printf("10.0 + 3.0 = %f .\n",10.0+3.0);
    printf("10.0 - 3.0 = %f .\n", 10.0 - 3.0);
    printf("10.0 X 3.0 = %f .\n", 10.0 * 3.0);
    printf("10.0 / 3.0 = %f .\n", 10.0 / 3.0);

    printf("10.0 + 3.0 = %F .\n", 10.0 + 3.0);
}
/**
 * 40 / 13 を計算し、式と商と余りを表示するプロブラムを作成せよ。
 *
 * 16 / 5 = 3 あまり 1
 * e.g. 16 = 5 X 3 + 1
 * この時の3が商で1が余りと呼ばれるもの。
 * */
void handson_3_1() {
    printf("--------------------- handson_3_1\n");
    // 40 / 13
    int calc = 40 / 13;
    int remainder = 40.0 - (calc * 13);
    const char* result = "40 = 13 X %d + %d \n";
    printf(result,calc,remainder);
}
/**
 * 1.03 X 9 これはコンピュータでは実数として扱われる。
 * なるほど、実数と整数が混ざった計算において、その結果は実数だと。
 * 試してみる。
 * */
void coffee_break() {
    print_template("-------------------- coffee_break");
    printf("1.03 X 9 = %f\n", 1.03 * 9);
    print_template("次の出力は指定子を整数にしたもの、どんな変化になるのかな？");
    // コンパイルエラーとなった、コンパイラにはdouble を予期してたのに、int だと叱られた。
    // printf("1.03 X 9 = %d", 1.03 * 9);

}
int main(void) {
    printf("START =============== \n");
    printf("Hello C. \t I had came back. \n");

    print_template("これ動くぞ。");
    debug_print_d("これが俺のやり方だ。", 9);
    debug_print_s("これをいちいち作らなアカンのか？");
    test_strncpy();

    // web リファレンスを少しやってみる。
    // ここで気づく、vim はTab、VS Code は半角スペース4つだったと。
    // これは、表示領域の問題から、半角スペース4を取りたい。
    printf("a + b, (100 + 200) is %d \n",100+200);
    // 1から100までを足していく公式があるのか。それをやってみる。
    printf("1から100まで足した結果は？ %d .\n", (1+100)*100/2);
    // 公式は調べていない、が次のものなのかな？
    printf("%d\n",(1+200)*200/2);

    test_Sum_Of_Natural_Numbers(100);
    sample_Numbers_Floating_Point_Method();
    handson_3_1();
    coffee_break();

    printf("=============== END \n");
    return 0;
}


