/**

19 章　malloc/free のはず　：）

よし、気を引き締めて行くよ。
イニD でのお遊び、デバッグ用関数の確認は終わりだ。
いってみよう。

配列を自由自在に作る 

配列の最大の欠点は、要素数をプログラム中で変更出来ないことです。

変更できる環境
GCCというコンパイラでは独自の拡張により、
要素数をプログラム中で変更できるようになっています。
また、C99というより新しいC言語でも同様の機能が追加されています。
（ヤッホーイ、オイラ GCC、そして既にこの機能は使っている、配列の要素数に変数入れてる場所あるし。えっ？汎用性がなくなる？Windows で動かない？　うん、そんなん知らね。Linux、もっと限定的に言えば、オイラの持ってるマシンで動けばそれでいいよ：）

メモリの確保 

自由に配列を作るmalloc(エムアロック)関数が用意されています。
なお、malloc関数を使うには、<stdlib.h> を #include する必要があります。
malloc関数の使い方は、次の通りです。

malloc関数

ポインタ変数 = malloc(必要なメモリのバイトサイズ);

（マロックって呼んでた、これからもそう呼ぶ、きっとね。）

malloc関数で指定できるのは、バイト単位のサイズなので、
任意の要素数の配列を確保するには、sizeof演算子を使用します。
なお、malloc関数で確保したメモリを、ヒープと呼ぶことがあります。
また、ヒープに確保された配列を、動的配列と呼ぶことがあります。
なお(深刻なメモリ不足などが原因で)メモリ確保に失敗するとNULLが返されます。
これをそのまま使用すると強制終了してしまうので、
malloc関数の戻り値は必ずチェックする必要があります。

malloc関数によって確保されたメモリは、プログラムが終了するまで残りますが、
そのメモリが不要になった場合、free(フリー)関数を使って解放します。
これを忘れると、ムダなメモリが残り続けることになるため、
malloc関数を使ったら、必ずfree関数を呼び出します。
free関数の使い方は次の通りです。

malloc関数

free(ポインタ変数);


終了時のfree関数
free関数は必ず呼び出すと説明しましたが、例外もあります。
プログラムが終了する直前では、free関数を使わなくても、
プログラム終了と同時にOSがメモリを解放します。
しかし、free関数 は常に呼び出す癖をつけておいてください。


malloc関数が返すアドレスは、void型のポインタです。
この型は、どんなポインタ変数にも代入できるという型なので、
本当は(int *)にキャストする必要はないのですが、
C++コンパイラではキャストしないとエラーがでます。
（C++ が型に厳格なのは身を持って経験した、まだまだだけど。）

exit関数はプログラムを終了させる関数です。
なお、exit関数を使うには、<stdlib.h> を #include する必要があります。
ちなみに、エラーによる強制終了の時はabort関数を使うこともあります。


malloc関数の実態
malloc関数は、好きなように好きなサイズの動的配列を作ることができるので、
非常に便利ですが、実は、その仕組みは、メモリにマークをつけているだけです。

これは、冷蔵庫に入っているお菓子に名前を書いておくのと同じことで、
家族みんながその名前に従い、他人のお菓子を食べなければ問題はありませんが、
勘違いによって他の人にお菓子が食べられてしまう可能性は十分あります。

malloc関数にも似たような性質があり、うまく使うのは意外に難しいのです。
したがって、プログラムの時は、できる限り普通の配列を使うようにして、
どうしても必要な部分だけmalloc関数を使うようにした方が良いでしょう。

配列の要素数を変更出来ない、
という問題は、完全に解決されたとは言いません。
そこで、要素数を変更する、realloc(リアロック)関数が用意されています。
realloc関数の使い方は、次の通りです。



 realloc関数

新しいポインタ変数 = realloc(以前のポインタ変数, 必要なメモリのバイトサイズ);

以前のポインタ変数には、malloc関数で確保したメモリのアドレスを指定します。
realloc関数は、中身を維持したまま、新しいサイズのメモリを確保します。
新しいポインタ変数には、拡張されたメモリのアドレスが返されますが、
特別な理由がなければ、以前のポインタ変数と同じ変数を指定できます。

呼び出し回数を減らそう
realloc関数を何回も呼び出すとメモリが散らかってきます。
この様な状態をフラグメンテーションと呼び、不安定になります。
初めのmalloc関数である程度大きめに確保しておき、
realloc関数を呼び出す場合も、一回で大きめに確保するべきです。



メモリリークとの戦い 
実のところ、malloc関数について、説明することはこれしかありません。
malloc関数で必要な大きさの配列を作り、不要になったらfree関数で解放する、
たったこれだけです。しかし、これこそが、C言語最大の問題でもあるのです。

メモリリーク
皆さんも、長時間コンピュータを使っているうちに、
だんだん動作が遅くなってきて、再起動することになる、という経験があると思います。
実は、あの現象の原因が、まさにfree関数の呼び出し忘れなのです。
動的メモリの開放を忘れてしまうことをメモリリークと呼びます。

これの解決策のひとつがクラスのコンストラクタ、デストラクタなのだと解釈している。
無論これでも、基底クラスのデストラクタの virtual のつけ忘れなどにより、派生クラス
で正しくデストラクタが呼ばれず、メモリリークの根本解決には至っていない。
プログラマが気を付けるという意味では、C と同じだ。
Rust では上手くやってるよってなことをWebでは見る、本当なのだろうか。
（さして興味はない。
何か上手いやり方を各自工夫する必要があるのだろうね、注意する以外にね。

使われているメモリと、もう不要になったメモリを区別することは、極めて困難なのです。
事実上、C言語やその拡張版のC++言語ではこの問題をスマートに解決することは
できておらず、膨大かつ徹底したテストによって、なんとか対策しているのが現状です。

そのため、Java言語など、ガベージコレクションという、
自動的にメモリを解放する機能をそなえたプログラミング言語が登場し、
幅広く使用されています。


ガベージコレクション
使用されているメモリを自動的に監視することで、メモリリークを解決する機能。
ほとんどのメモリリークを自動的に解決してくれるため、
現代のアプリ開発では、この機能をそなえた言語を使用することが多くなりました。

ただし、メモリの利用効率上のムダが多くなってしまう弱点も抱えています

いや、そもそも、その GC もちゃんと機能しているのか怪しい。

Rust言語という、メモリの自動解放と、メモリの効率利用を両立できる言語も登場しました。
Rust言語は、今もっとも期待されているプログラミング言語でもあります。


Rust言語
所有権システムにより、メモリリークに対して、根本的な対策を行った言語。
とても雑に言えば「メモリリークするプログラムは、コンパイルエラーになる」言語。

メモリの利用効率をまったくムダにすることなく、ほぼ完全なメモリリーク対策ができるが、
ちょっとしたミスでもコンパイルできなくなってしまうため、
プログラムを記述するのがかなり疲れるプログラミング言語です。

しかし、メモリリーク問題に対して、現時点でもっとも優れた言語には間違いありません。
今後のOSやシステムアプリは、Rust言語で開発されるものが多くなることでしょう。

いや、先生：）ちちょっ待てよ。（キムタク風に）
まさか、先生からRust に変わるかもという話を聞こうとは、それ程にプロの現場でのC/C++
の開発、テストが大変だと解釈してしまうが。今まさに湾岸、最高速、速度厨のオレにそれは
ないよ。：）やろーぜ、最高速。

あぁでもそゆことなら Rust が C++ より高速ってのも合点がいくな。C++ は実行中も監視して
るんだよね、きっと。いつメモリ解放してやろうかと（デストラクタ等）。Java の GC とは
違うが、言語仕様の中で C よりメモリに関する監視が働いていると思ってる。
でも、Rust はコンパイル時に全てを検査してる、ん？　
じゃコンパイル時間半端ないんじゃないの。あぁなるほどね、そこはトレードオフでよい
と、ふーーーん。いいよ、何でも速い方がさ：）

*/

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"

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

void sample_malloc_free(void) {
    println("----------- sample_malloc_free");
    int i = 0;
    int* heap;
    heap = (int*)malloc(sizeof(int)*10);
    if(heap == NULL) {
        debug_s("あ、あの、えぇとですね、誠に申し訳ございません。","メ、メモリが確保できませんでした。");
        exit(1);
    }
    for(i = 0;i < 10; i++) {
        heap[i] = i;
    }
    for(i = 0;i < 10; i++) {
        printf("heap[%d]\t",i);
        debug_d("value is ", heap[i]);
    }
    free(heap);
}

void no_memmory_exit(void) {
    println("奥さん、お宅のメモリ、もうありませんよ。");
    exit(1);
}

void sample_realloc_free(const int first_size, const int resize) {
    println("-------------------- sample_realloc_free");
    int* heap;
    heap = (int*)malloc(sizeof(int)*first_size);
    if( heap == NULL ) {
        no_memmory_exit();
    }
    for(int i=0 ; i < first_size ; i++) {
        heap[i] = (i+1)*2;
    }
    heap = (int*)realloc(heap,sizeof(int)*resize);
    if( heap == NULL ) {
        no_memmory_exit();
    }
    // realloc 関数後に最初の値がどうなっているのか気になった。
    for(int i=0 ; i < first_size ; i++) {
        printf("heap[%d]\t",i);
        debug_d("value is ",heap[i]);
    }
    free(heap);
}

int main(void) {
    println("START malloc/free ===============");
    int z = 33;
    int r = 32;
    int* fc = &r;
    
    debug_d("Z33: 崖を駆けあがった！？",z);
    debug_s("Z33: 理屈じゃないんだ、無理に逆らえばとっちらかって終わる。","F原以上の感覚派、赤城の白い彗星、完全復活！！（Z 池");
    debug_ptr_pd("R32:（回想）バカな女さ、こんな言い方したくないが、後悔することになるよ。",&r);
    debug_f("R32: なぜだ Rスケ、もう32のブレーキは終わってる、FCのブレーキでは止められない、やめてくれ、Rスケ！！",r);
    debug_ptr_pd("FC:くっ　FCのフルブレーキでも減速しない！？（これは、とんだ大誤算だったな、Kスケ w",fc);
    debug_s("Z33:そこまでやられて、見ているだけにはいかないな。", "おれも手を貸すぜ！！（Z 池");
    debug_s("吹っ飛ぶパイロン、駆け抜ける3台","合流所手前でFC、Z33、R32が完全停止。");
    // 以下、創作。
    debug_s("Rスケ：よしっ、死神も倒したし、撤収だ。","山頂にいる松本を残し、群馬へひとり、帰るRスケ。ボォボォボ、ブーーーーン...（一緒に来たことを忘れている。）");
    
    sample_malloc_free();
    sample_realloc_free(10,100);
    println("=============== malloc/free END");
    return 0;
}