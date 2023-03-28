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
#include "stdbool.h"

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
    // printf("len is %d \n",len);
    // int size = len;
    // char buff[size];
    // for(int i = 0; i < size ; i++) {
    //     buff[i] = '\0';
    // }
}

void println(const char* message) {
    print_template(message);
}
// DEBUG 用もほしい。

/**
 * デバッグ int を出力する。
*/
void debug_print_d(const char* message, int debug) {
    printf("DEBUG: %s\t %d\n",message, debug);
}

void debug_d(const char* message, int debug) {
    debug_print_d(message, debug);
}

/**
 * デバッグ double を出力する。
 * */
void debug_print_f(const char* message, double debug) {
    printf("DEBUG: %s\t %f\n",message, debug);
}

void debug_f(const char* message, double debug) {
    debug_print_f(message, debug);
}

/**
 * デバッグ const char* を出力する。
*/
void debug_print_s(const char* debug ) {
    printf("DEBUG: %s\n",debug);
}
void debug_s(const char* debug) {
    debug_print_s(debug);
}
// だいたいここで気づく、これどうにかならないかなと。
// つまり、型ごとにデバッグ出力用の関数を用意するのダルに普通はなる。
// だから、みんな、printf 関数をそのまま使ってるんだね。
// なんかもっといい方法あると思うけど、今はまだダメだな。
//
// 気分転換でエディタを替えてみた、少しだけ、vim 使ってみる。
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
    // なら、cast だな、これでどうなるか見てみよう。
    printf("1.03 X 9 = %d\n", (int)(1.03 * 9));
    print_template("これが出力されていれば、それは cast によるためだ。");
}

/**
 * 数字の桁数の printf 関数における表現方法です。
 * 
 * - 5 桁で表現してみる。
 * - 数値の余分な桁を任意の文字で埋める。
 *
 * */
void sample_number_of_digits() {
    print_template("--------------- sample_number_of_digits ");
    int a = 10000, b = 500, c = 3;

    printf("a is %5d \n",a);
    printf("b is %5d \n",b);
    printf("c is %5d \n",c);

    printf("a is %05d \n",a);
    printf("b is %05d \n",b);
    printf("c is %05d \n",c);

    // 実数の場合、%6.2f では、整数部分が3桁、少数点が1桁、少数部分
    // が2桁の6桁と解釈される。
    double pi = 3.14159;
    printf("src is 3.14159 but...\t  %6.2f \n",pi);
    printf("src is 3.14159 but...\t 123456 \n");
}

/**
 * 1本198円の清涼飲料水1本と、1本138円の牛乳2本を購入し
 * 千円で払った場合のお釣りを求めよ。
 * ただし、5% の消費税を追加し、お釣りの額は整数とする。
 * 消費税を四捨五入するかどうかは自由とする。
 *
 * 2つ作って確認してみる。 upper, lower
 *
 * */
void handson_5_3_1() {
    print_template("------------ handson_5_3_1");
    int juice = 198;
    int milk  = 138;
    
    int sum = juice + (milk*2);
    debug_print_d("sum is ",sum);
    double tax = sum * 0.05;
    debug_print_f("tax(double) is ",tax);
    int tax_low = (int)tax;
    debug_print_d("tax_low is ",tax_low);
    debug_print_d("sum(tax_low) is ",sum + tax_low);
    debug_d("answer is ", 1000 - (sum + tax_low));

    int rem = (int)((tax - tax_low)*100);
    debug_print_d("rem is ",rem);
    if( rem > 40 ) {
         tax_low++;
	 debug_d("sum(tax_up) is ",sum + tax_low);
	 debug_d("answer is ", 1000 - (sum + tax_low));
    }
}

/**
 * シグマ計算
 * 1 + 2 + 3 + 4 + 5 + ..... 100 などを計算するのがシグマです。
 * 公式は次のもの。
 * (min + max) X (max - min + 1) / 2
 *
 * 2つの値（整数）は、scanf 関数で入力を受け付ける。
 *
 * */
void handson_6() {
    print_template("---------------- シグマ簡易計算  handson_6");
    print_template("最小値と最大値（整数）を , で区切って入力してね：）");
    int min = -1, max = -1, sum = -1;
    int inleft = -1;

    scanf("%d , %d", &inleft, &max);
    if( inleft > max ) {
        min = max;
	max = inleft;
    } else {
        min = inleft;
    }

    sum = (min + max) * (max - min + 1) / 2;
    printf("%d から %d までの合計値は %d です。\n", min, max, sum);
}


/**
 * 文字コード表を引っ張り出したよ。
 * これをつかったら、scanf を利用しても多少はましなプロブラムになるかな。
 * 0を先頭に入力した際は8 進数の扱いに コンピュータではなるのだが、それは
 * 無視します：）
 *
 * 10 進数　16進数　文字
 * 48	    0x30	0
 * 49	    0x31	1
 * 50	    0x32	2
 * 51	    0x33	3
 * 52	    0x34	4
 * 53	    0x35	5
 * 54	    0x36	6
 * 55	    0x37	7
 * 56	    0x38	8
 * 57	    0x39	9
 * */

bool check_6_3_1(const char* in) {
    print_template("--------- 入力値が数値かどうかを判定する。 check_6_3_1");
    debug_s(in);
    int len = strlen(in);
    debug_d("len is ",len);
    int size = len + 1;
    char buff[size];
    strncpy(buff,in,size);
    debug_s(buff);
    
    bool is_digit = 1;
    for(int i = 0; i < len ;i++) {
	debug_d("buff is ",(int)buff[i]);
        if( buff[i] < 48 || buff[i] > 57) {
	   is_digit = 0; 
	}
    }
    return is_digit;
}

void test_check_6_3_1() {
    print_template("---------- test_check_6_3_1 ");
    printf("result is %d \n",check_6_3_1("1000"));

    if( check_6_3_1("1000") ) {
        int digit = atoi("1000");
	debug_d("digit is ", digit);
    }
}

void fatal_attack() {
     printf("ドゴッ　ボゴッ　ダガガ　瞬　極　殺　！！！ \n");
}

void handson_6_3_1(const char* your_in) {
    print_template("----------------- handson_6_3_1");
    print_template("定価を入力すると、1割引、3割引、5割引、8割引の値段を一覧表示するプロブラムを作成せよ。");

    // 金額は整数の表示が望ましい、とのこと。
    print_template("定価を入力してくださね。文字列とか止めてね、ブッ飛ばしますよ：）");
    if(1) {
        int len = strlen(your_in);
	if(len > 8) {
	    fatal_attack();
	}
    }
    int sale_1 = -1, sale_3 = -1, sale_5 = -1, sale_8 = -1;
    int in = -1;
    char input[9];
    for(int i = 0; i < 9 ;i++) {
        input[i] = '\0';
    }

    // scanf("%s",input);	// 章が進んでいちいち入力するのがウザくなった。
    strncpy(input,your_in,8);
    int len = strlen(input);
    debug_d("len is ", len);
    if( len ) {
       if(check_6_3_1(input)) {
          int in = atoi(input);
	  debug_d("in is ",in);
	  sale_1 = (int)(in * 0.1);
	  debug_d("sale_1 is ",sale_1);
	  sale_3 = (int)(in * 0.3);
	  sale_5 = (int)(in * 0.5);
	  sale_8 = (int)(in * 0.8);
	  printf("sale1 is %d, sale3 is %d, sale5 is %d, sale8 is %d \n",in-sale_1,in-sale_3,in-sale_5,in-sale_8);

       } else {
           fatal_attack();
       }
    } else {
        fatal_attack();
    }
}
/**
 * 7_3_1
 *
 * 西暦年を入力すると、その年にオリンピックが開かれるか、表示する
 * プログラムを作成せよ。
 * 可能なら、夏季と冬季の区別も表示できればなお良い。
 * ヒント：シドニー五輪（夏）は2000年開催であった。
 *
 * 条件がややこしくなるので、以前夏季と冬季が同じ年だった時期のことは無視する。
 * 
 * うん、色々と想像できる。

 4年毎に開催される。

 1896 年、ギリシャのアテネ　これが初開催、つまりこれ以前はなかった。
 1924 年	シャモニー・モンブラン　これが初開催、これ以前はなかった。

 関数は2つ作ろう。
 
 先生ごめん、おれはもう scanf 関数は使わないよ。実行時の入力がダルいから。
 
 calc_summer_olympic
 calc_winter_olympic
 定数を変えれば使い回せるかも。
 1994 このとしから、冬季オリンピックの数え方が変わってる、ちくしょーー。
 * */
int calc_olympic_year(const int start, const int year) {
    print_template("-------------- calc_olympic_year ");
    if(year < start) {
        print_template("ブッブー、間違ってるよ。その年はまだ開催されてないよ。");
        return -1;
    }
    int calc = -1;
    if(start == 1924 && year >= 1994) {	// 冬季オリンピックめ、何変えてくれてんだよ。
        calc = 1994;
    }else {
	calc = start;
    }
    while(calc < year) {
        calc += 4;
    }
    debug_d("your input year is ", year);
    debug_d("calc is ",calc);
    if(calc == year) {
        print_template("Yes Correct Answer, It's a Olympic year.");	// 今さらなんだけど、なんでこの関数名 println にしなかったのかな。
    } else {
        print_template("No.");
    }
    return 0;
}
void test_calc_olympic_year() {
    print_template("-------------------------- test_calc_olympic_year ");
    const int start_summer = 1896;
    const int start_winter = 1924;
    calc_olympic_year(start_summer, 1002);
    calc_olympic_year(start_summer, 1896);
    calc_olympic_year(start_summer, 2000);
    calc_olympic_year(start_summer, 2020);
    calc_olympic_year(start_winter, 1924);
    calc_olympic_year(start_winter, 1928);
    calc_olympic_year(start_winter, 1992);
    calc_olympic_year(start_winter, 1994);
    calc_olympic_year(start_winter, 2022);
}

/**
 * 月（整数値）を入力すると、対応する陰暦の月を表示するプログラムを作成せよ。
 * なお、存在しない月を入力した時にも何らかのメッセージを表示せよ。
 *
 * ヒント：陰暦は1月から順番に、
 * 睦月
 * 如月
 * 弥生
 * 卯月
 * 皐月
 * 水無月
 * 文月
 * 葉月
 * 長月
 * 神無月
 * 霜月
 * 師走
 * 。
 * */
void handson_8_3_1(const int month) {
    println("--------------- handson_8_3_1");
    switch (month) {
        case 1 :
	    debug_d("睦月です。", month);
	    break;
        case 2 :
	    debug_d("如月です。", month);
	    break;
        case 3 :
	    debug_d("弥生です。", month);
	    break;
	case 4 :
	    debug_d("卯月です。", month);
	    break;
	case 5 :
	    debug_d("皐月です。", month);
	    break;
	case 6 :
	    debug_d("月は水無月です。", month);
	    break;
	case 7 :
	    debug_d("文月です。", month);
	    break;
	case 8 :
	    debug_d("葉月です。", month);
	    break;
	case 9 :
	    debug_d("長月です。", month);
	    break;
	case 10 :
	    debug_d("神無月です。", month);
	    break;
	case 11 :
	    debug_d("霜月です。", month);
	    break;
	case 12 :
	    debug_d("師走です。", month);
	    break;
	default :
	    println("そんな月はない。（タモリ風で");
    }
}
void test_handson_8_3_1() {
    println("------------------- test_handson_8_3_1");
    handson_8_3_1(1);
    handson_8_3_1(2);
    handson_8_3_1(3);
    handson_8_3_1(4);
    handson_8_3_1(5);
    handson_8_3_1(6);
    handson_8_3_1(7);
    handson_8_3_1(8);
    handson_8_3_1(9);
    handson_8_3_1(10);
    handson_8_3_1(11);
    handson_8_3_1(12);
    handson_8_3_1(0);
}

/**
 * for 文を使用して、掛け算九九表を表示するプログラムを作成せよ。
 *
 * ヒント： %2d 指定子を使うと表を揃えられる。
 * ヒント： for 文の中でfor 文を使っても良い（優しいね、先生：）
 * 
 **/
void handson_9_3_1() {
    println("--------------九九表（出たな定番：） handson_9_3_1");
    for(int i=1; i < 10 ; i++) {
        for(int j=1; j < 10 ;j++) {
	    printf("%2d |", i*j);
	}
	printf("\n");
    }
}

/**
 * テストの点数を入力するプログラムを作りなさい。
 * ただし、テストの点数は0 から 100 までしかないので、
 * それ以外が入力された場合には再入力させるようにすること。
 *
 * do while 文と scanf関数なんだろうが、前述のように、以降がダルい。
 * したがって、ゴメンナサイ、先生。俺、パターンテストで許してつかーさい。
 * */
int handson_10_3_1(int score) {
    println("----- handson_10_3_1");
    do {
        if(score < 0) {
	    println("0より小さいのダメだよ。（マイナス");
	    return -1;
	} else if(score > 100) {
            println("100 より大きいのダメだよ。（オーバー");
	    return -1;
	}
    } while(0);
    printf("input score is %3d \n",score);
    return 0;
}

void test_handson_10_3_1() {
    println("------------- test_handson_10_3_1");
    // 正常系
    handson_10_3_1(100);
    // 異常系（マイナス）
    handson_10_3_1(-1);
    // 異常系（オーバー）
    handson_10_3_1(1000);
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
    sample_number_of_digits();

    handson_5_3_1();
    //
    // ここから6章
    //
    // handson_6();
    handson_6_3_1("10000000");
    // test_check_6_3_1();
    

    //
    // 7 章
    // 等値演算子、関係演算子、論理演算子
    //
    test_calc_olympic_year();
    
    //
    // 8 章
    // 場合分け処理を行う。
    // if の　else。　else if、switch case 文は変数と整数値の比較にしか
    // 利用できない。
    //
    println("switch (変数): { ");
    println("case 1: ");
    println("    処理1;");
    println("    処理2;");
    println("    break;");
    println("case 2: ");
    println("case 3:");
    println("    ・・・;");
    println("    break;");
    println("default:");
    println("    ・・・;");
    println("    break;");
    println("}");
    
    test_handson_8_3_1();

    //
    // 9 章
    // for ループ
    //
    handson_9_3_1();

    //
    // 10 章
    // while 文
    // do while 文 scanf 関数との併用で入力チェックをスキなだけできる。
    //
    //【これは豆知識】うん、Trivia か。
    // コンピュータの世界では、円周率を3.14159で計算します。
    // これは、その次の桁まで表すと、3.141592、となり、
    // 9と2の間で切り捨てても、誤差が大きくならないからです。
    //
    test_handson_10_3_1();
    printf("=============== END \n");
    return 0;
}
