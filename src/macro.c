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
  
*/
#include "stdio.h"

// tax_consumption 消費税、Google翻訳丸コピ
#define TAX_CONSUMPTION 0.10
#define AUTHOR "AlienM14xR2 Jack"

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
    println("START マクロ ===============");
    debug_d("FD3Sは、",7);
    debug_f("πは、",3.14159);
    debug_s("Je pense, donc je suis", "我思う、故に我在り");
    if(1) {
        int ms09 = 9;
        int* rx78 = &ms09;
        debug_ptr_pd("ジェットストリームアタックだ！！",&ms09);
        debug_s("おれを踏み台に！？","うあぁぁっ（ア");
        debug_ptr_pd("そこだ（キラッ", rx78);
        // うん、オレのなかでポインタとはアムロ・レイそのものだと：）        
    }
    if(1) {
        int sell = -1;
        int* selling = &sell;
        compute_sell(100,selling);
        debug_d("(*selling) is ",*selling);
        debug_d("sell is ",sell);
        debug_s("Code by ", AUTHOR);
    }
    println("=============== マクロ END");
	return 0;
}
