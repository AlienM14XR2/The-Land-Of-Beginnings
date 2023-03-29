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
#include "string.h"

void println(const char* message) {
    printf("%s \n", message);
}

void debug_d(const char* message, const int digit) {
    printf("DEBUG: %s \t %d \n",message, digit);
}

void debug_f(const char* message, const double f) { 
    printf("DEBUG: %s \t %f \n",message, f);
}

void debug_c(const char* message, const char c) {
    printf("DEBUG: %s \t %c \n", message, c);
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

void sample_sprintf(void) {
    println("------------ sample_sprintf");
    // 思い出してきた。こいつは、確かに便利だよね。
    char result[256];
    for(int i=0; i < 256 ;i++){
        result[i] = '\0';
    }

    char dragon[12] = "Dragon";
    char quest[]    = "Quest";
    int number      = 3;
    // なるほど、先生はその世代か。
    sprintf(result, "%s%s %d\n", dragon, quest, number);
    //printf(result);	// 先生の書き方は warning になったよ。
    printf("result is %s",result);
    // うん、うん、こいつは便利だね：）
}

// プロトタイプ宣言教えてもらったのに使ってない：）
void sample_strcmp(void) {
    println("---------- sample_strcmp");
    char dragon[] = "Dragon";
    char sample[] = "dragon";
    char sample2[] = "Dragon";
    
    if( strcmp(dragon, sample) == 0 ) {
        printf("%s, %s is same.\n", dragon, sample);
    } else {
	printf("%s, %s is not same.\n",dragon, sample);
    }
    if(strcmp(dragon, sample2) == 0) {
        printf("%s, %s is same.\n", dragon, sample2);
    } else {
        printf("%s, %s is not same.\n", dragon, sample2);
    }
}

/**
 * ２つの文字列を仮引数にとり、結合して表示する関数です。
 * */
int handson_14_3_1(const char*, const char*);
/**
 * 上記関数のテスト関数ですな。
 * どうだ、プロトタイプ宣言使ってぞ：）最後だしな。
 * */
void test_handson_14_3_1(void);
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
    // 配列のコピーを行ってくれる。
    // memory.h が必要。
    //
    sample_sizeof();
    sample_memcpy();
    handson_13_3_1();
    
    //
    // 14 章　文字列
    //
    // マルチバイトつまり、日本語には wchar_t型が用意されている。
    // しかし、先生は厳格だ、まずは基本ということでここでは扱わないといっている。
    // 
    // ctype.h を #include
    // isalnum A-Z a-z 0-9
    // isdigit 0-9
    // isxdigit A-F a-f 0-9
    // isalpha A-Z a-z
    // isupper A-Z
    // islower a-z
    // ispunct 記号 !"#$
    // isspace 0x09-0x0D 0x20:
    //
    // stdlib.h を #include
    // atoi 関数　文字列を数値に変換した結果を返す。
    // atof 関数　文字列を実数に変換した結果を返す。
    //
    // string.h を #include
    // strcpy(dest,src);
    // strncpy(dest,src,size); // この関数はEOS '\0' ヌル文字が入らない可能性があるので注意が必要だったね。
    // strcat(元の文字列が記憶された配列、追加する文字列の記憶された配列)
    //
    // 文字列リテラルであれば"Foo""Bar" で連結できる。
    //
    // 文字列が混乱を来す要因の一つがそれが示すものが複数ある点だろうな。
    // 上記で言えば、数値も扱えてします。
    //
    // stdio.h
    // sprintf(結果を記憶する配列、書式文字列、各種変数・・・)
    // 確かにこんなのあったな、完全に忘却の彼方にあったが。
    // これは、サンプリングしてみよう。
    //
    // scanf 関数で、変数に & をつけない理由について、
    // 以下、先生の言葉。
    // 配列は、C言語の本質であるポインタそのものであるからです。
    // これはC言語の根底をなす重要なことであるため、
    // 後々じっくりと時間をとって、たっぷりと説明いたします。
    //
    // これだよ、俺がC++ で感じた違和感、C++ はもっと厳密的に型をみていると思う。
    // 実を言えば俺も先生と同じ考え、同じ教えを最初の C で学んだ。
    // 配列がC++でしっくりこなかったのもおそらくこれじゃないかな。
    // 配列使わないで、コンテナ使おって思ったし。
    // C はその辺がニアリーイコールで C++ は違うもの。というのが今の自分の見解。
    // いや、自分の理解がC/C++双方で弱いと感じたのが配列なのだね。 
    // やはり、圧倒的なコード量が足らないか、配列は。
    // 忘れないとは思うが、念の為に。
    // TODO 配列のポインタで次を確認すること。これは、ポインタの章が楽しみだ。
    // char doragon[] = "Dragon";
    // char* pc = dragon;
    // char* pc2 = &dragon[0];
    // pc と pc2 が同じアドレスを指しているのか？
    // 予想は同じだ。
    //
    // char str[32];
    // scanf("%32s", str);
    // こんなテクニックあったのか、これでオーバーフローしないよね。
    // 問題点もあるのか、うん、スペースの入力ができないのね。
    //
    // strlen string.h
    // 文字列の長さを返却する。
    //
    // strcmp string.h
    // 文字列を比較する。
    // うん、これはサンプリングする。
    //
    debug_c("これで私はcharもデバッグできるようになったぞ。A is ",'A');
    debug_d("こんなこともできたはずだ。A is ",'A');
    sample_sprintf();
    sample_strcmp();
    test_handson_14_3_1();
    return 0;
}

int handson_14_3_1(const char* lc, const char* rc) {
    println("---------------- handson_14_3_1");
    // strcat, strcpy, strncpy, sprintf || 完全自作 どれを採用しよ：）
    // strcat でやってみる。バッファオーバーフローに注意と。
    int llen = strlen(lc);
    int rlen = strlen(rc);
    debug_d("llen is ", llen);
    debug_d("rlen is ", rlen);
    int size = llen + rlen + 1;
    char buff[size];
    for(int i = 0; i < size ;i++) {
        buff[i] = '\0';
    }

    strcat(buff,lc);
    strcat(buff,rc);
    printf("result is %s\n",buff);

    return 0;
}

void test_handson_14_3_1(void) {
    println("------------------------------ test_handson_14_3_1");
    handson_14_3_1("Alice","RedGrave");
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
