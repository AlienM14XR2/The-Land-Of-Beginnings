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


以上、ブレスト終了。
*/

#include "stdio.h"
#include "stdlib.h"
#include "memory.h"
#include "string.h"

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

void test_debug_unknown_types(void* unknown) {
    println("---------------------- test_debug_unknown_types");
//    if(typeof()) {
//    }
}

int main(void) {
    println("START c1 ===============");
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
        int i = 0;
        test_debug_unknown_types(&i);
    }
    println("=============== c1 END");
    return 0;
}

