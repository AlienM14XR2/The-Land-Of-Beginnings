/**
20 章　ソースとヘッダファイル

だったね。
関数ポインタ、Makefile は出てくるかな。予想、たぶんでてこないかなと。


【ヘッダーファイル】

関数や変数の宣言のみが記述されたファイル。
拡張子は .h にすることが慣習となっている。

これに対して、実際にプログラムを記述するファイルをソースファイルと呼びます。
今までに記述してきたのはすべてソースファイルです。なお、拡張子は .c とします。


【ソースファイル】

プログラムが記述されたファイル。
拡張子は .c にすることが慣習となっている。

ソースファイルとヘッダーファイルは、通常、1対1で対応するように作成します。
ソースファイルの中から宣言の部分を抜き出して、
同じ名前(拡張子だけ変える)にして、ヘッダーファイルを作成します。


【インクルード】

#include疑似命令でヘッダーファイルを取り込むこと。

e.g.)

sum.h
```
// sum.h
int sum(int min, int max);
```


e.g. )
```
#include "sum.h"
#include <stdio.h>

int main(void)
{
    int value;
    value = sum(50, 100);
    printf("%d\n", value);
    return 0;
}
```


extern宣言 

変数は宣言と定義を同時に行うため、複数回宣言できないことを説明しました。
この問題を解決するには、宣言だけを複数回行い、定義は1回で済ませる必要があります。
その場合、宣言だけを行うextern(エクスターン)宣言が用意されています。


【extern宣言】

宣言だけを行い定義は行わない宣言方法。


extern宣言

// sum.h
extern int sum(int min, int max);
extern int Public;

このextern宣言を使うと、異なるソースファイルで変数を共有することができます。
これで、変数Publicは sum.h をインクルードしているすべてのソースファイルで
共有できます。
しかし、これだけでは定義がされていないため、変数Publicは作られていません。
そこで、どこか1つのソースファイルの中で普通の宣言を行って実体を作成します。

 sum.c

// sum.c
int Public; // 変数の実体の作成

int sum(int min, int max)
{
    int num;
    num = (min + max) * (max - min + 1) / 2;
    return num;
}

これで、変数Publicは main.c からも sum.c からも使えるようになります。
次のプログラムは、それを実際に試してみた例です。


main.c

// main.c
#include "sum.h"
#include <stdio.h>

int main(void)
{
    int value;
    value = sum(50, 100);
    printf("%d\n", Public);
    return 0;
}


sum.c

// sum.c
int Public;

int sum(int min, int max)
{
    int num;
    num = (min + max) * (max - min + 1) / 2;
    Public = 100;
    return num;
}

このプログラムの実行結果は次の通りになります。

実行結果
100 


必要最低限に
変数の共有は大変便利なテクニックですが、あまり乱用しないでください。
本来、複数のファイルに分割するのは、機能毎に独立させるためです。
しかし、変数の共有を使用すると、同じ変数が使えるようになってしまい、
機能毎に独立させる意味合いが薄れてしまいます。

したがって、可能な限り関数の引数や戻り値を利用し、
変数の共有は、どうしても必要な場合にのみ使用してください。



 ヘッダーファイルの重複防ぎ
ここまでは、extern宣言を使用して、重複して定義されることを回避してきましたが、
実は、ヘッダーファイルの重複インクルードそれ自体を防ぐ方法もあります。
それには、#ifndef～#endif疑似命令を使用します。

#ifndef～#endif疑似命令は、ある記号が定義されていなかった場合だけ、
その間に挟まれたプログラムをコンパイルするという記号です。
この性質を利用して、次のようなヘッダーファイルを作成できます。

sum.h 

#ifndef _INCLUDE_SUM_
#define _INCLUDE_SUM_

int sum(int min, int max);

#endif


このヘッダーファイルでは、最初に、記号_INCLUDE_SUM_が定義されているか調べて、
定義されていなかった場合だけ、その後のプログラムをコンパイルします。
ここでは、後にコンパイルされるプログラムの中で、#define疑似命令を使って、
記号_INCLUDE_SUM_ を定義しているので、このヘッダーファイルが2回目に呼び出された場合、
記号_INCLUDE_SUM_ がすでに定義されていることになり、コンパイルは行われません。

この様にすれば、同じ宣言を何度も行うことがなくなります。
2回目以降はコンパイルされないのでは、1つしか使えなくなるようにも思えますが、
最終的にはすべてのソースファイルは結合されるので、1回コンパイルすれば十分です。

なお、一般には、extern宣言も組み合わせて、次のようにします。
さらに、この様なコメントを入れると、より良いヘッダーファイルが完成します。
この書き方であれば、トラブルが起こりにくいため、常にこの書き方をすることをオススメします。


sum.h
```
// sum.h
#ifndef _INCLUDE_SUM_
#define _INCLUDE_SUM_

//
// min～max間の合計値を計算する関数
// int min 最小値
//int max 最大値
//戻り値 int 合計値
//
extern int sum(int min, int max);

#endif
```
これがお約束の書き方、宣言ということ。


自動でできそうな気もするが・・・
ヘッダーファイルは書き方が決まり切っているため、
ソースファイルから自動的に生成することができるような気もします。
実際、他の多くの言語では、自動でやってくれるため、ヘッダーファイルは不要です。

しかし、ヘッダーファイルにはソースファイルの設計書という意味もあります。
先にヘッダーファイルを作り、それに合わせてプログラムを作っていくわけです。
また、ソースファイルには、ヘッダーファイルに書く必要のない、
そのソースファイル固有の関数や変数が使われていることも良くあるため、
自動生成で不要な宣言までヘッダーにしてしまうと、ある種のムダが出てしまいます。

C言語はプログラマーが意識しなければならないことが多いかわりに、
意識して行えば、ムダを大きく減らせるようになっています。

*/

#include "stdio.h"
#include "stdlib.h"

void println(const char* message) {
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

int main(void) {
    println("START ソートとヘッダファイル =============== ");
    println("=============== ソートとヘッダファイル END");
    return 0;
}
