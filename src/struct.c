/**
 * 16 章　おそらく、構造体：）
 *
 * ここでひとつ、リファレンスから逸脱するオレのルール。
 * 構造体は C 文化ではなく C++ 文化を尊重したい。正直に言えば、C より C++ の方が
 * 難しいと思う（初心者が学習するにあたり）。それは構造体にも関係することがらで
 * あり、オレが重要視する機能、クラスだ。クラスは C++ でも OOP を実現するために
 * 非常に重要なもので、それはオレが大事にしていることとも一致する。なので、構造体
 * は C++ 文化を尊重し次のように宣言する。
 *
 * struct Foo {		// クラス同様にその名前は大文字からはじめる。
 *     int number;
 *     char[256];
 * };
 *
 * GCC コンパイラに限らず、多くの C コンパイラは C++ もサポートしている。
 * したがって、 class は予約語だよ。GCC なら、 g++ がそれにあたる。
 *
 * C言語では、新しい型を宣言するtypedef(タイプデフ)が用意されています。
 * ```
 * typedef 新しい型の形 新しい型名
 * ```
 *
 * struct student_tag
 * {
 *     int year;       // 学年
 *     int clas;       // クラス
 *     int number;     // 出席番号
 *     char name[64];  // 名前
 *     double stature; // 身長
 *     double weight;  // 体重
 * };
 * typedef struct student_tag student;
 * 次の書き方がよりスマート。構造体タグを省略して、typedef と一緒に構造体を宣言、
 * 定義していまう。
 * typedef struct
 * {
 *     int year;       // 学年
 *     int clas;       // クラス
 *     int number;     // 出席番号
 *     char name[64];  // 名前
 *     double stature; // 身長
 *     double weight;  // 体重
 * } student;
 * 現在では上記の形がほぼ慣用句となっておりますので、この形で覚えてしまって
 * いいと思います。
 *
 * 構造体のポインタ変数経由で要素にアクセス
 * ```
 * (*構造体ポインタ変数名).要素名
 * ```
 * (*)をつけるのは面倒なので、次の書き方で代用できるようになっています。
 * 構造体のポインタ変数経由で要素にアクセス
 * ```
 * 構造体ポインタ変数名->要素名
 * ```
 * アロー演算子の登場か。構造体の要素にポインタ変数経由でアクセスする、ここまで
 * 出番はなかったのか。うん、ないね。
 *
 * 普通に渡すことができる構造体を、ポインタ変数として渡す理由の
 * 1つ目は、普通のポインタ変数と同じく、関数内で値を変更できるようにするためです。
 * ここでは試していませんが、関数内で値を変えると呼び出し元の変数の中身も
 * 変わります。
 *
 * 2つ目は、関数呼び出しの高速化のためです。
 * 構造体を渡す時、その中身はすべてコピーされます。
 * 構造体の中に、大きな配列があれば、その中身までまるごとコピーされます。
 * これは、当然ながらそれなりに時間のかかる処理となります。
 * しかし、ポインタのアドレス値を渡すだけなら、非常に高速です。
 *
 * ここで、C++ の素晴らしさ、MOTHER で出来たらいいなってことのひとつが連想される。
 * void compute_somethig(const int&);
 * これは本当によく出来てる。
 * 先生が言っている遅い方、コピーのパターンでは。
 * void compute_something(const int);
 * 参照という概念を持っているいるプログラム言語は素晴らしいのだよ。
 * Java を含めた感想だよ、もちろん。
 * ポインタを使わずに（内部では利用しているのかもね）高速に関数呼び出しができる。
 * 余談、C++ で関数、メンバ関数でその引数の値をいじらない話はした。
 * その時、具体的な書き方で const にすることもふれたと思う。
 * const int& のさらなる利点、それは一時変数の利用もできるということ。
 * 一時変数とは、なんら宣言、初期化されていない変数、大概は数値リテラルや
 * 文字リテラルをさすと考えている。
 * compute_something(369);    // 数値リテラルで直接、関数に渡している。
 * 別の言い方をすると、const int& にしてないとこの書き方はできない。
 * 便利だよね：）
 *
 * しかし、現代のコンピュータはとても高速なので、値渡しであっても、
 * それほど問題にはなりません。慣れないうちは、値渡しのほうが扱いやすいため、
 * 値渡しで行うことをおすすめします。
 * （優しいね、先生は。：）
 *
 *
 * 構造体変数の配列
 * student data[10];
 *
 * data[1].year = 3;
 * strcpy(data[1].name, "MARIO");
 *
 * そのほかの点も、これまでの配列の使い方と同様です。
 * 別の書き方
 * 構造体の配列があるということは、それは内部ではポインタ変数を使っているという
 * ことです。したがって、前項で説明した以外の書き方、つまり、ポインタ変数風に
 * 書くこともできるのです。すなわち、次の3つは同じ意味になるのです。
 * ```
 * (*data).year
 * data->year
 * data［0］.year
 * ```
 * ところで、この3つがまったく同じ意味であることを説明するには、
 * 構造体とポインタの仕組みをしっかり理解している必要があります。
 * 皆さんの教師や上司はこの３つの違いがわかりますか？
 * 
 * */
#include "stdio.h"


void println(const char* message) {
    printf("%s\n",message);
}

void debug_s(const char* message, const char* debug) {
    printf("DEBUG: %s\t%s\n",message, debug);
}

void debug_d(const char* message, const int debug) {
    printf("DEBUG: %s\t%d\n",message, debug);
}

void debug_f(const char* message, const double debug) {
    printf("DEBUG: %s\t%f\n",message, debug);
}

/**
 * 演習問題
 * 3人分の、名前、年齢、性別、を入力して表示するプログラムを作りなさい。
 * ただし、データは構造体で記憶するこことする。
 * また、データ入力と表示はそれぞれ専用の関数を作って行うこと。
 *
 * input_person()
 * output_person()
 * ゴメンナサイ、先生、例によってオレはscanf関数は使わないよ。（実行時ダルい。
 * test_person()
 * 一旦、この3つの関数でやってみる。
 * */
typedef struct {
    char name[256];
    int age;
    int sex; // 0: 無回答 1: male 2: female
} Person;
int input_person(Person people[], const int size) {
    println("----- input_person");
    // C の配列それを関数に渡す際にはやはりsize指定は必須だな。
    // 自分で作り込んで、EOF、EOS?、のような終端を持つ新しい型を作るなら別だろう
    // が。ポインタからその実体のサイズを推し図るのはオレの技術レベルでは厳しいし
    // 言語仕様としても困難なのでは、だから、使い方を間違えれば、
    // バッファオーバーフローが標準関数でも起こり得る。
    // OK、今はここまで。
    
    // これは コンパイル時に warning 実行時にも期待値は得られない。
    // debug_d("size of people is ",sizeof(people));
    debug_d("size of people(people[0]) is ",sizeof((*people)));

    char buff[256] = {'\0'};
    // sprintf 関数有能だな、これ作ったヒト天才だな。
    // これだよね、みんながほしいものは：）
    sprintf(buff, "Alice-%d",0);
    println(buff);

    for(int i = 0; i < size ;i++) {
      sprintf(people[i].name,"Alice-%d",i+1);
      people[i].age = (i+1)*10;
      people[i].sex = 0;
    }
    debug_s("people[0].name is ",people[0].name);
    debug_s("people[2].name is ",people[2].name);
    return 0;
}
int output_person(Person people[], const int size) {
    println("----- output_person");
    for(int i=0; i < size ;i++) {
        printf("people[%d].name is ",i);
	debug_s(" ",people[i].name);
        printf("people[%d].age is ",i);
	debug_d(" ", people[i].age);
        printf("people[%d].sex is ",i);
	debug_d(" ", people[i].sex);
    }
    return 0;
}
void test_handson_16_2_1(void) {
    println("------------- test_handson_16_2_1");
    Person person[3];
    int nums[3];
    // 少し興味深い、ここから、課題とは無関係なことが続くよ。
    debug_d("size of person is ",sizeof(person));
    debug_d("size of person[0] is ",sizeof(person[0]));
    int person_size = sizeof(person) / sizeof(person[0]);
    debug_d("person_size is ",person_size);

    debug_d("size of nums is ", sizeof(nums));
    debug_d("size of nums[0] is ", sizeof(nums[0]));
    int nums_size = sizeof(nums) / sizeof(nums[0]);
    debug_d("nums_size is ",nums_size);

    input_person(person,3);
    output_person(person,3);
}
int main(void) {
    println("START 構造体 ===============");
    debug_d("減速しない！？こいつコースを知らないのか", 'K');
    debug_f("慣性ドリフト！？",3.14159);
    test_handson_16_2_1();
    println("=============== 構造体 END");
    return 0;
}
