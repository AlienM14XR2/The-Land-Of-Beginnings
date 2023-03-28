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
    //
    //
    return 0;
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
