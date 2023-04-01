/**
 18 章　マクロ　のはず：）
 
 OK、ここからエディタを gedit にしてみる。
 VS CODE ではなくGEdit にしたのは、CODEは C++ で使ってたので、そのイメージ
  が付き纏うのを避ける目的がある。
 また、VIMを止めたのは、他の一般的なエディタの操作に弊害が出始めたからだ。
 VIM マスタ になりたいわけではないからね：）
 
 不変の値の取り扱い 
 初めから終わりまで不変の値 
 
 実行中は変化しない値を定数と呼びます。
 これまで、プログラム中に直接書き込んできた数値は、すべて定数です。
 直接書き込まれた文字列も定数で、文字列リテラルと呼ばれます。
 
 数値に名前をつける 
 C言語には、数値に名前をつける方法が用意されています。
 それが、＃define(ディファイン)疑似命令です。
 ＃define疑似命令の使い方は次の通りです。
 ```
 ＃define疑似命令 
 ```
 
 その他の方法による定数 
 const定数 
 
 const定数とは、値を変更出来ない変数のことです。
 変数を宣言する時、その先頭でconstを指定すると、
 その変数は宣言時に代入された初期値を変更することが出来なくなります。
 次のプログラムは、前節の消費税プログラムをconst定数に書き換えた例です。
 
  定数を配列の要素数にする
 C言語では、const定数を配列の要素数にできませんが、
 C++やC99では可能になっています。なお、#define疑似命令ならどちらでも可能です。
 
 enum定数 
 C言語には、＃defineやconstの他に、enum(エナム)定数があります。
 enum定数の宣言の仕方は次の通りです。
 ```
 enum {
    名前,
    名前,
    名前
 };
 ```
 enum定数では、数値を指定する必要はなく(指定することもできる)、
 名前だけで自動的に数値がつけられるので、大量の定数を宣言する場合に便利です。
 
 enum定数は、主にフラグ定数として使用されます。
 たとえば、RPGゲームにおいて、キャラの状態を表す場合、
 0 正常
 1 毒
 2 マヒ
 3 呪われ 
 
 
 ＃defineの場合
 #define STATE_NORMAL 0 // 正常 
 #define STATE_POISON 1 // 毒 
 #define STATE_NUMBLY 2 // マヒ 
 #define STATE_CURSE 3  // 呪われ 


 enumの場合
 enum {
    STATE_NORMAL,  // 通常 
    STATE_POISON,  // 毒 
    STATE_NUMBLY,  // マヒ 
    STATE_CURSE    // 呪われ 
 };
 
 この様に便利なenumですが、残念なことに、enumは整数値しか扱えません。
 実数値を扱う場合には、＃defineかconst定数にするしかありません。
 また、文字列も扱えません。
 
 enumの名前の後につける，は、正式には最後の名前にはつけませんが、
 実際にはつけても問題なく動作します。
 したがって、次のように書くと、名前の追加や修正が楽になります。
 
 enum {
     STATE_NORMAL,
     STATE_POISON,
     STATE_NUMBLY,
     STATE_CURSE, // ここにも，がある
 };
 
 次は、数値を指定したenum定数の例です。
 enum {
    ENUM_0,
    ENUM_1,
    ENUM_5 = 5,
    ENUM_6,
    ENUM_7,
    ENUM_9 = 9,
 };
 
 
 簡易的な関数の実現 
 ＃define疑似命令による定数は、単なる置き換えによって実現されていますが、
 これを利用すると特殊な処理を行わせることも可能です。
 たとえば、変数の中身を画面に表示するにはprintf文を次のように使用します。
 
 
 enumに数値を指定
 printf("temp = %d\n", temp);
 
 しかし、変数tempの値をあちこちで表示する必要がある場合に、
 この文を毎回打ち込むのが面倒であれば、
 ＃define疑似命令で置き換えることができます。
 
 #define PRINT_TEMP printf("temp = %d\n", temp)
 
 うん、ひとつ試してみるか。
 オレは余り他の言語でも利用しない、グローバル変数というもので、これを実装してみるよ。
 
 マクロ関数だったかな？
 これは、あらゆるプログラムを強引にまとめることができる、非常に強力な機能です。
 しかし、上記のテクニックを乱用すると、プログラムが省略表現だらけになってしまって、
 最初にプログラムを書いた人にしか読めなくなってしまうので、十分に注意して使用する
 必要があります。
 
 余談、オレが C++ で AOP を調べていた時にこのマクロ関数で AOP の代替にしていたと記憶
 している。確かに、これなら AOP いらないかとも思った。意味合いは、ポイントカットなので
 後付がいくらでもできる。どんな処理をポイントカット先で行いたいのか？といことなので
 使い方は実装者次第だ。
 
 C++ は C との互換がある、したがって、プログラマが C 寄りか OOP クラスを多用するかで
 その景色はガラリと変わる。C には無論クラスなどという概念はない、故に、AOPの必要性
 もない。AOP はOOP の継承構造を邪魔せず、共通の処理を派生クラスでキレイに実現するもの
 だと認識している。（GoF を利用すれば、解決できることもあろう、が根本的にAOPとOOPは
 その目的、実装が異なると解釈している。）
 懐かしいなJava Aspect ：）
 Java Aspect これはいつ頃のものだ？C/C++が基盤であれば、その時の技術の上で成立して
 いるはずだよね。それともこれは、Java オリジナルなのか？　後で調べてみるかな。
 忘れてなかったらね。
 
 
【マクロ】
 #define疑似命令による置き換えで式などを簡単に表現すること。
 マクロでは、使用している場所のプログラムそれ自体が置き換わり、
 呼び出しなどの作業が必要ないため、若干高速になります。
 
 しかし、マクロを使う場所すべてが置き換わるので、あまり巨大なマクロを作ると、
 その為にプログラムのサイズが極端に大きくなることもあります。
 
 その為、一般的には、マクロは、決まり切った数式などに利用されます。
 
 残念、単にマクロであってたのか orz
 
 
 副作用の恐怖 
 #define疑似命令によるマクロは手軽で便利なのですが、
 使い方を間違えると思わぬ現象に遭遇することがあります。
 たとえば、前回の台形の面積を求めるプログラムに置いて、
 なんらかの事情で、高さを常に+3しなければならない場合を考えてみます。
 次のプログラムは、そのように変更してみた例です。
 （おっとこれは、写経必須ですね。）

 
*/
#include "stdio.h"

// tax_consumption 消費税、Google翻訳丸コピ
#define TAX_CONSUMPTION 0.10
#define AUTHOR "AlienM14xR2 Jack"
#define PRINT_OUTER_HEAVEN printf("OUTER_HEAVEN is %d\n", OUTER_HEAVEN);
// これなら引数も渡せるのか。
#define PRINT_D(X) printf("X is %d\n", X)
// 台形の面積を求めるマクロ。
#define GET_TRAPEZOID_AREA(A, B, H) (A + B) * H / 2

//
// グローバル
//
int static OUTER_HEAVEN = 100;

// あっいいかも：）gedit
// 忘れてたこと、勘違いしていたこととして、C 言語には関数のオーバーロードはないぞ。
// 欲しけりゃ自分で作るんだな、うん。

void println(const char* message){
    // オレンジが見づらいね。OK、設定、フォントと色「Yaru-dark」ならいいかも。
    // ダメだ、vim が抜けない：）
    printf("%s\n",message);
}

void debug_d(const char* message, const int debug) {
    printf("DEBUG: %s\t%d\n",message,debug);
}

void debug_f(const char* message, const double debug) {
    printf("DEBUG: %s\t%f\n",message,debug);
}

void debug_s(const char* message, const char* debug) {
    printf("DEBUG: %s\t%s\n",message,debug);
}

void debug_ptr_pd(const char* message, const int* debug) {
    printf("DEBUG: %s\t%p\n",message,debug);
}

int compute_sell(const int price, int* selling) {
    double tax = price * TAX_CONSUMPTION;
    *selling = price + tax;
    return 0;
}

int main(void) {
    OUTER_HEAVEN -= 1;
    println("START マクロ ===============");
    debug_d("FD3Sは、",7);
    debug_f("πは、",3.14159);
    debug_s("Je pense, donc je suis", "我思う、故に我在り");
    PRINT_OUTER_HEAVEN;
    if(1) {
        int ms09 = 9;
        int* rx78 = &ms09;
        debug_ptr_pd("ジェットストリームアタックだ！！",&ms09);
        debug_s("おれを踏み台に！？","うあぁぁっ（ア");
        debug_ptr_pd("そこだ（キラッ", rx78);
        // うん、オレのなかでポインタとはアムロ・レイそのものだと：）        
        --OUTER_HEAVEN;
    }
    if(1) {
        int sell = -1;
        int* selling = &sell;
        compute_sell(100,selling);
        debug_d("(*selling) is ",*selling);
        debug_d("sell is ",sell);
        debug_s("Code by ", AUTHOR);
        --OUTER_HEAVEN;
    }
    if(1) {
        PRINT_OUTER_HEAVEN;
        PRINT_D(369);
        int ans = GET_TRAPEZOID_AREA(6,9,6);
        debug_d("ans（台形の面積だぜ） is ",ans);
        double ansd = GET_TRAPEZOID_AREA(6.0,9.0,3.0);
        debug_f("ansd（台形の面積だぜ） is ",ansd);
        // 見事だね：）
        // C++ generic lambda と auto を思い出した。
    }
    // マクロの副作用の恐怖。
    if(1) {
        int h = 3;
        int ans = GET_TRAPEZOID_AREA(6,9,h+3);        
        debug_d("ans（台形の面積だぜ） is ",ans);
        // この様に、置き換えで予期しない計算結果になることを
        // マクロの副作用と呼びます。
        // これを解決する方法は2つあります。1つは、呼び出し時にかっこ
        // をつけることです。
        ans = GET_TRAPEZOID_AREA(6,9,(h+3));
        debug_d("ans（台形の面積だぜ） is ",ans);
        // うん、同じだ。
        
        // もう1つの方法は、マクロの方にかっこをつけておく方法です。
        // #define GET_TRAPEZOID_AREA(A, B, H) (((A) + (B)) * (H) / 2)
        // あぁ急に見づらくなったな。
        
        // しかし、気をつけて使用するのは面倒ですし、うっかり忘れてしまうかも
        // しれません。その為、マクロはあまり多用しない方が良いとされています。
        // #define疑似命令は定数の宣言にのみ使用して、数式などの計算にはできる限り
        // 関数を使用する方が良いでしょう。

    }   
    println("=============== マクロ END");
	return 0;
}

/**
オリンピックの問題はもう飽きたのだ。

int olympic(int year);

enum {
    OLYMIPC_NON,
    OLYMIPC_SUMMER,
    OLYMIPC_WINTER,
};

int main(void)
{
    int year, hold;

    scanf("%d", &year);
    hold = olympic(year);

    switch (hold) {
    case OLYMIPC_NON:
        printf("開かれない\n");
        break;
    case OLYMIPC_SUMMER:
        printf("夏季五輪\n");
        break;
    case OLYMIPC_WINTER:
        printf("冬季五輪\n");
        break;
    };

    return 0;
}

int olympic(int year)
{
    if (year % 2 == 0) {
        if (year % 4 == 0) {
            return OLYMIPC_SUMMER;
        } else {
            return OLYMIPC_WINTER;
        }
    } else {
        return OLYMIPC_NON;
    }
}
*/
