/**
 * お勉強を続けますよ。
 * 参考書は次のURLからかな。
 * https://9cguide.appspot.com/11-01.html
 * 
 * 11 章　関数
 *
 * ファイルも新たに、始めてみたい。
 * 前回の hello.c でお気に入りになりつつあった、関数。
 * - println 関数
 * - debug_d 
 * - debug_f
 *
 * この3つの関数はここでも利用したい、したがって、まずこれらを作り直す。
 *
 * */

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

void println(const char* message) {
    printf("%s \n", message);
}

void debug_d(const char* message, const int digit) {
    printf("DEBUG: %s \t %d \n",message, digit);
}

void debug_f(const char* message, const double f){
    printf("DEBUG: %s \t %f \n",message, f);
}

// sum 関数のプロトタイプ宣言
// 関数定義は必ず必要（GCCではコンパイル時に叱られます。
int sum(const int x, const int y);
/**
 * 自然数の和を求める関数です。
 * 1/2n(n+1)
 * e.g. (1+100) X 100/2 = 5050 
 **/
int sum_natural_numbers(const int max);

/**
 * シグマ計算を行う関数です。
 * (min + max) X (max - min + 1) / 2
 * */
int sum_sigma(const int min, const int max);

// 条件は 2000 年からのオリンピックとする。
int easy_calc_olympic_year(int year) {
    println("------------- 課題 11_3_1  easy_calc_olympic_year");
    if( year % 4 == 0 ) {
        debug_d("夏季オリンピック", year);
    } else if(year % 2 == 0 && year % 4 != 0) {
	debug_d("冬季オリンピック", year);
    } else {
        debug_d("オリンピックねーーんだってその年は",year);
    }

    return 0;
}
void test_easy_calc_olympic_year() {
    println("---------------------------------- test_easy_calc_olympic_year");
    easy_calc_olympic_year(2000);
    easy_calc_olympic_year(2020);
    easy_calc_olympic_year(2022);
    easy_calc_olympic_year(2023);
}
/*
 * これが、先生の模範回答。
 * 利用する側は switch case 文になる
 * 1 夏季五輪
 * 2 冬季五輪
 * 3 なし
int olympic(int year)
{
    if (year % 2 == 0) {
        if (year % 4 == 0) {
            return 1;
        } else {
            return 2;
        }
    } else {
        return 0;
    }
}
 * */

// 静的なローカル変数の説明用、リファレンスから流用した。
int count_func(void);

void sample_sizeof(void) {
    println("----------- sample_sizeof");
    int numbers[] = {33,3,9,99,102};
    debug_d("これが、今回のクリティカルヒット。sizeof(numbers) is ", sizeof(numbers));
    debug_d("同じくここもね。sizeof(numbers[0] is )", sizeof(numbers[0]));
    // このように変数に格納して利用すれば無駄が省ける。
    // 先生は今のマシンは高性能と言っていたが、これが大事なこともある。
    // int loop_count = sizeof(numbers)/sizeof(numbers[0]);

    for(int i = 0; i < sizeof(numbers)/sizeof(numbers[0]) ;i++) {
        debug_d("numbers is ", numbers[i]);
    }
}

/* *
 * 注意だよ。
 * memcpy は コピー元の配列がコピー先の配列より長くても、お構いなくコピー
 * しようとする、それを一般にはバッファオーバーフローと呼ぶぞ。
 * さらに、運が悪ければ、バッファオーバランに発展しかねない恐怖があるぞ。
 *
 * そういう所にいると理解しながら、一歩を踏みしめ、前へ進む。
 * */
void sample_memcpy(void) {
    println("---------------- sample_memcpy");
    int nums_1[] = {42,79,13,19,41};
    int nums_2[] = {1,2,3,4,5};
    int loop_nums_2 = sizeof(nums_2)/sizeof(nums_2[0]);
    debug_d("loop_nums_2 is ", loop_nums_2);
    for(int i = 0; i < loop_nums_2; i++) {
        debug_d("before nums_2 is ", nums_2[i]);
    }
    // nums_1 の全要素をコピーする。
    memcpy(nums_2, nums_1, sizeof(nums_1));
    for(int i = 0; i < loop_nums_2; i++) {
        debug_d("after nums_2 is ", nums_2[i]);
    }
}
/**
 * 入力された、10個の数値を最後から表示するプログラムを作成せよ。
 *
 * */
void handson_13_3_1(void) {
    println("----------- handson_13_3_1");
    int nums[10] = {1,2,3,4,5,6,7,8,9};	// 9個しか初期化してない、敢えてね。
    int loop = sizeof(nums)/sizeof(nums[0]);
    debug_d("loop is ", loop);
    
    int i = loop - 1;
    do {
        debug_d("nums is ", nums[i]);
        i--;
    }while(i >= 0);
}

int main(void) {
    //
    // 11 章　関数
    // ここからリスタート。
    //
    println("START =============== ");
    debug_d("これ動くぞ（アムロ",78);
    debug_f("連邦の新兵器か！？（シャア",3.14159);
    println("=============== END");
    if(1) {
        int n = sum(10,100);
	debug_d("n is ",n);
	n = sum_natural_numbers(100);
	debug_d("n is (result of sum_natural_numbers func.)",n);
	n = sum_sigma(0,50);
	debug_d("n is (result of sum_sigma func.)",n);
    }
    test_easy_calc_olympic_year();
    
    //
    // 12 章　変数の寿命
    // ローカル変数の場合。
    // グローバル変数と同名のローカル変数ではローカル変数が優先されるのです。
    // static ローカル変数を学習した。
    //
    count_func();
    count_func();
    count_func();

    //
    // 13 章　配列
    //
    // 正直に言えば、C++で手を焼いた。
    // Cにおけるそれは、どんなものなのか、しっかりと学びたい。
    //
    // ※ いまさら感が半端ないけど、コメント以外のソース部分に全角スペースが
    // あると、もちろんコンパイルエラーとなる、vim を利用しているそこの君、
    // 気をつけ給えよ。
    // 
    // sizeof 演算子
    // sizeof(変数や配列名) 
    // これは実際に使ってみたい。
    //
    // memcpy 関数
    // 配列のコピーを行ってくる。
    // memory.h が必要。
    //
    sample_sizeof();
    sample_memcpy();
    handson_13_3_1();
        
    return 0;
}
int count_func(void) {
    static int count;   /* 静的なローカル変数 初期化しなくても始めの値は0 プログラム終了まで残る。　これが、ローカル static 変数。*/

    // static int count = 0; // これでも動作は問題なかった。
    count++;
    debug_d("static int count is ", count);
    return count;
}

int sum_sigma(const int min, const int max) {
    return (min + max) * (max - min) / 2;
}

int sum_natural_numbers(const int max) {
    return (max+1)*max/2;
}
// sum 関数定義
int sum(const int x, const int y) {
 return x + y;
}
