/**==============================================================================

クラスとは、それがどんなものなのか。
あるいは、何を優先するのか。
オレの実力と理解と趣味。

- コンストラクタ、デストラクタ（これは一対）。
- カプセル化
- 継承
- ポリモーフィズム

制御ループ、当たり判定とか。
ソースファイルが１つのクラス。
struct で表現。
スコープとは、private protected public をどのように考え、表現できるのか。


メモリ解放を安全に行いたい。
解放忘れは防げるのか、その場合は監視ループが必要だよね、きっと。
少なくとも、使われていないことを知る必要がある。
Java GC はどんなことを内部で行っているのか。
使っている側が通知、フラグを立てるだと、根本的な解決にはならないのか。
Java ではプログラマはノータッチ。
監視して、管理しているのは基盤のはず、JRE かもしれないのか。


https://qiita.com/e_tyubo/items/48398391a8ef0f24c1be
メモリ内のデータを精査し、参照があれば有効なデータとして残し、参照が無ければ
不要だと判断して解放します。

%p ポインタが見ている変数の動向がわかるかも。



if(1) {
    // something.
}
これって、分かりやすい、一番手っ取り早いスコープ、アクセス制限なのかも。

if( Private_ ) {
    // private scope.
}
if( Protected_ ) {
    // protected scope.
}
if( Public_ ) {
    // public scope.
}

One File One Class の考え方に落ちてくな。
コンストラクタもデストラクタも関数でしかない。
メンバ関数もC ではやはり、関数でしかない。
スコープの概念はC にもある。それを、どう分割してやるのか。
ファイルやそのパスは分かりやすい、スコープのひとつ。

#include #define #ifdef #ifndef
これらで継承のスコープを制御できないかな。


クラスとメモリ制御、取得と解放はいったん切り離して考えてもいいかも。
これも、まずは単純に考えれば、制御ループと関数とマクロかな。
少し、簡単なメモリの取得と解放、malloc free を使って、実装してみるか。


以上、ブレスト終了。

*/

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

void c_version(void) {
    printf("C supported version __STDC_VERSION__ is %ld\n",__STDC_VERSION__);
}

void println(const char* message) {
    printf("%s\n",message);
}

// これは、変数の値が分かるだけ。
// こっちに、%p を追加してやるだけで、相当便利な気がしてきた。
// それではダメだ、それだと変数のコピーなんだよ、分かるよな、オレ。：）
// ここで、アドレスみても、コピーのアドレスだろ。したがって、意味ないよ。
void debug_d(const char* message, const int debug) {
    printf("DEBUG: %s\tvalue = %d\n",message,debug);
}

void debug_f(const char* message, const double debug) {
    printf("DEBUG: %s\tvalue = %f\n",message,debug);
}

// これでポインタが見ているアドレスが分かるよね。
// こっちは、%d を追加してやるだけで、やっぱり便利な気がする：）
// C 言語に参照はない、あくまで、ポインタとアドレスだ。
// これが手引になるのか？ 使いそうな型についてもこれを用意してみるかね。
void debug_ptr_d(const char* message, const int* debug) {
    printf("DEBUG: %s\tvalue = %d\taddress = %p\n",message,*debug,debug);
}

// double
void debug_ptr_f(const char* message, const double* debug) {
    printf("DEBUG: %s\tvalue = %f\taddress = %p\n",message,*debug,debug);
}

// long
void debug_ptr_ld(const char* message, const long* debug) {
    printf("DEBUG: %s\tvalue = %ld\taddress = %p\n",message,*debug,debug);
}

// char[]
void debug_ptr_s(const char* message, const char* debug) {
    printf("DEBUG: %s\tvalue = %s\taddress = %p\n",message,debug,debug);
}

typedef struct {
    long id;
    int age;
    double points;
    char name[256];
} MockPerson;

void test_debug_types(void);
void test_debug_unknown_types(void* mockPerson);
void test_debug_sizeof_types(void);

// 今のところ、使う予定なし、思考錯誤中だからさ。
typedef int* Int;

// 気持ちは分かるけど、定義してる場所ね。
#define INT_HEAP_SIZE 100

int* int_array_;
int int_array_index_ = 0;

// アプリで利用するHeap を事前に確保しておく。
void born(void) {
    println("-------- born");
    int_array_ = (int*)malloc(sizeof(int*)*INT_HEAP_SIZE);
}
void death(void) {
    println("-------- death");
    free(int_array_);
}
// int new これが、デフォルトの New。
int* new_int(void);
// int new 値を代入、初期化を可能にしたもの。
int* new_int_val(const int);

// これは、理想とは違うんだけどね、ひとまず、確認です。
int* mock_new_int(void);

int main(void) {
    println("START c1 ===============");
    c_version();
    if(1) {
        test_debug_types();
    }
    if(1) {
        MockPerson mock;
        MockPerson* pmock = &mock;
        // typedef で新たに宣言、定義した場合は個々にやった方が効率的かな。
        // void* 受付何でもありだと思ってる。そこで、typeof 演算子で特定する手も
        // あるかも。折角だから、試してみようか。？　typeof ってなんだったっけ：）
        printf("mock is \t%p\n",&mock);
        printf("pmock is \t%p\n",pmock);
        
        // プログラミング言語Cの次期仕様C2x(C23)では、式から型情報を取り出す 
        // typeof演算子(typeof operator) が追加される。 
        // 今は GNU の拡張機能という理解だが。
        // あぁオレの理解が間違っていた。これは、静的型付言語であるC を動的に
        // 振る舞わせると、そゆことでしょ。近いけど、まだ違うな。
        // typeof：オペランドの型情報をそのまま返す。 （これが正しい説明のようだ。
        // 従来からある同名のGCC拡張機能を標準化したもの。
        // typeof(変数1)変数2 という使い方をしてるから結果キャストなだけか。
        // typeof 演算子の本質は型情報をそのまま返すと。
        // void* とこれでなんかいけそうな気がするけどな、どうだろ。
        // クラスの継承に似た利用ができないかなと、子のオーバーライドとか。
        // 設計者であるオレは型が何かわかってるし。
        int i = 0;
        double d = 3.14159;
        debug_ptr_d("i is ",&i);
        debug_ptr_f("d is ",&d);
        // これって i の力（宣言と初期化）を借りて x が定義されてるよね。
        typeof(i)x = 100;
        debug_ptr_d("x is ",&x);
        // 一度使ってしまった変数名は使い回せないのか。
//        typeof(d)x = 5.12345;
        typeof(d)y = 5.12345;
        debug_ptr_f("y is ",&y);
        
    }
    if(1) {
        MockPerson mock;
        mock.id = 100000L;
        test_debug_unknown_types(&mock);
    }
    if(1) {
        // typeof 演算子が変数を利用した、新たな変数の宣言なのは分かった。
        // void* が何でもありの仮引数を定義していることも分かった。
        // C には C++ の typeid に相当する型がなんなのか知るすべがないのか？
        // sizeof 演算子でサイズから類推するしかないのかな。
        test_debug_sizeof_types();
    }
    if(1) {
        // メモリの解放忘れをなくせるのか、取得、解放を楽に簡単にできるのか。
        // そもそも、メモリの取得とはなんなのか。Heap に配置される。
        // 型とサイズ、なんの型で幾つ必要なのか。
        int* heap_i = NULL;
        
        // %p は void* これはコアダンプ、実行時エラーになるよ。コンパイラが分かれば
        // warning で教えてくれる。
//        printf("heap_i %d\taddress %p\n",*heap_i);
        heap_i = (int*)malloc(sizeof(int*)*30);  // このサイズ、30 を調べる術はあるのかな
        // do something.
        
        // 利用が終わったら解放
        free(heap_i);
        
    }
    if(1) {
        println("=== new_int 関数のテスト、動作検証、アドレスは同じか？。");
        // ここで、現状気になることを確かめたい。
        // - new_int 関数内、ローカル変数とその戻り値のアドレスの確認。
        int* heap_i = new_int();
        printf("heap_i address is \t%p\n",heap_i);
        // これを見ると new_int 関数内のローカル変数とその戻り値で初期化された、heap_i のアドレスは同じ。
        // new_int 関数内で動的取得されたメモリをこのアドレスで追跡できるのでは。
        // プロブラム上で必要なHeap はこれらの外で管理する。単純にはブロックスコープ。
        // Step by Step で進めるよ。
        free(heap_i);
    }
    if(1) {
        println("==== new_int 関数のテスト、動作検証、ブロックスコープで管理確認。");
        // ここが、疑似管理スコープね。
        born();
        if(2){
            // ここが、疑似被管理スコープね。
            println("START ブロックスコープ 2 =====");
            int* heap_i = mock_new_int();
            printf("heap_i address is \t%p\n",heap_i);
            *heap_i = 333;
            debug_ptr_d("heap_i\t",heap_i);
            debug_ptr_d("int_array_[0]",&int_array_[0]);
            println("===== ブロックスコープ 2 END");
        }
        death();
        // うん、諸々問題はあるが、このようにすれば、被管理スコープは、メモリの
        // 動的な取得と解放を考えなくていいよね。        
    }
    println("=============== c1 END");
    return 0;
}
int* mock_new_int(void) {
    if( int_array_index_ < INT_HEAP_SIZE ) {
        int* heap = &int_array_[int_array_index_];
        printf("heap address is \t%p\n",heap);
        int_array_index_++;
        return heap;
    } else {
        // ここで  realloc すればメモリの動的再取得ができるが。
        // この管理方法は素人目に見ても、スレッドセーフではなさそうだよね。
        // 無論今はそこまで、考慮はしないが。
        return NULL;
    }
}

int* new_int(void) {
    int* heap = (int*)malloc(sizeof(int*)*1);
    printf("heap address is \t%p\n",heap);
    return heap;
}

// 基本的な型の値とアドレスの確認方法。
void test_debug_types(void) {
    println("----------------- test_debug_types");
    int a = 3;
    int* pa = &a;
    printf("%p:%p\n",&a,pa);
    debug_d("a is ",a);
    debug_ptr_d("a is ",&a);       
    debug_ptr_d("pa is ",pa);
    
    double pai = 3.14159;
    double* ppai = &pai;
    debug_ptr_f("pai is ",&pai);
    debug_ptr_f("ppai is ",ppai);
    
    long l = 33L;
    long* pl = &l;
    debug_ptr_ld("l is ",&l);
    debug_ptr_ld("pl is ",pl);
    
    char alice[] = "Alice";
    char* palice = alice;
    debug_ptr_s("alice is ",alice);
    debug_ptr_s("palice is ",palice);
}

void test_debug_unknown_types(void* mockPerson) {
    println("---------------------- test_debug_unknown_types");
    // typeof 演算子は宣言なんだね、またひとつ勘違いが解けた。
    typeof(MockPerson*)pmock;
    printf("pmock address is \t%p\n",pmock);
    printf("pmock id is\t%ld\n",pmock->id);
    
    // 次はコンパイルエラー、理由は二重定義だから。
    // 仮引き数の時点で型は void* であるとしているため。
    // でもオレはそれが、MockPerson であることを知っている。
    // だから、キャストは出来る。 
//    typeof(MockPerson*)mockPerson;
    (MockPerson*)mockPerson;
    printf("mockPerson id is\t%ld\n",((MockPerson*)mockPerson)->id);
    debug_ptr_ld("mockPerson id is",&((MockPerson*)mockPerson)->id);
}

void test_debug_sizeof_types(void) {
    println("---------------------- test_debug_sizeof_types");
    debug_d("sizeof(int) is ",sizeof(int));
    debug_f("sizeof(double) is ",sizeof(double));
    printf("----- ここから printf 関数\n");
    printf("sizeof(char) is \t%ld\n",sizeof(char));
    printf("sizeof(short) is \t%ld\n",sizeof(short));
    printf("sizeof(int) is \t\t%ld\n",sizeof(int));
    printf("sizeof(long) is \t%ld\n",sizeof(long));
    printf("sizeof(double) is \t%ld\n",sizeof(double));
    println("long と double は同じ 8 bytes");
    printf("sizeof(float) is \t%ld\n",sizeof(float));
    println("float は使用しないと決めている。");
    println("以下、各型のポインタ のサイズ。");
    printf("sizeof(char*) is \t%ld\n",sizeof(char*));
    printf("sizeof(short*) is \t%ld\n",sizeof(short*));
    printf("sizeof(int*) is \t%ld\n",sizeof(int*));
    printf("sizeof(long*) is \t%ld\n",sizeof(long*));
    printf("sizeof(double*) is \t%ld\n",sizeof(double*));
    printf("sizeof(float*) is \t%ld\n",sizeof(float*));
    
    println("以下、struct のサイズ。");
    printf("sizeof(MockPerson) is \t\t%ld\n",sizeof(MockPerson));
    printf("sizeof(MockPerson*) is \t\t%ld\n",sizeof(MockPerson*));
    MockPerson mock;
    println("以下、struct 内各要素のサイズ。");
    printf("sizeof(mock.id) is long\t\t%ld\n",sizeof(mock.id));
    printf("sizeof(mock.age) is int\t\t%ld\n",sizeof(mock.age));
    printf("sizeof(mock.points) is double\t%ld\n",sizeof(mock.points));
    printf("sizeof(mock.name) is name[]\t%ld\n",sizeof(mock.name));
}

