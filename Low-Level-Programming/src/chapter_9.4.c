/**
    9.4 C における多相性（ポリモーフィズム）
    
    C 言語は静的で弱い型付け、これに該当する。
    
        多態性とも呼ばれる（私はこっちのほうが馴染みがある）。
        マクロや ##（トークン連結演算子）を駆使すればジェネリック（総称型）みたいな振る舞いが
    C でもできるというはなしだった。
        マクロは苦手だ、本当にそれが必要になったときに、また読み返そうと思う。
        次にあげる例はC における包含である。
        
    ```
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_9.4.c -o ../bin/main
    ```
        
    @author jack
*/
#include "stdio.h"

// @see 9.4.3 多重定義
#define print_format(x) (_Generic( (x), \
    int: "%d", \
    double: "%lf", \
    default: "%x"))     // デフォルトで何をすべきかわからないときは、いっそのこと default のケースを省いて、コンパイルを失敗させるのが、賢明だろう。

#define print(x) printf( print_format(x), x ); puts("");
// うん、上記のようなサンプルは理解できるが、いざ自分で書こうとすると非常に時間がかかる、そもそもそんなに多用したこともない。
// プリプロセッサ、マクロに関しては、軽く読み流したが、もう少し興味がわいたら戻ってやりなおそう。

struct parent {
    const char* field_parent;
};
        
struct child {
    struct parent base;
    const char* field_child;
};

void print_parent(struct parent* this) {
    printf("%s\n",this->field_parent);
    // 以上までがサンプルだが、ここで個人的に気になることを試す。
    printf("field_child is %s\n",((struct child*)this)->field_child);
    // なるほどね、次の操作、ポインタのインクリメントは無駄な操作ということだ。
    // そもそも、実引数で渡しているのは struct child のアドレスだし。
    // どんなデータ、エンティティ、型も受けつることができちゃうね、この関数の仮引数を void* にしたら。
    // その場合はソースの可読性は勿論下がるけど。
    this++;
    printf("this address is %p\n",(void*)this);
    printf("field_child is %s\n",((struct child*)this)->field_child);
}


int main(void) {
    if("9.4.2") {
        /**
            C でポインタ型の包含を達成するのは、とても簡単なことだ。「どの構造体のアドレスも、その第１メンバのアドレスと等しい」
                           というのが、発想の源である。
        */
        puts("9.4.2 包含 =========");
        struct child c;
        c.base.field_parent = "parent";
        c.field_child = "child";
        print_parent((struct parent*)&c);
        
        // 以上がサンプルなのだが、これではもの足りない、色々試したい、そんな気分だから、読まずに試す：）
        printf("c.field_child is %s\t c address is %p\t c.field_child address is %p\n",c.field_child,(void*)&c,(void*)&c.field_child);
    }
    if("9.4.3") {
        /**
                            多重定義の自動化は C11 まで不可能だった。最近まで人々は、基本となる関数名に引数の型名を加えることで、さまざまな
                            「多重定義」を提供していたのである。けれども新しい標準には、引数の型によって展開される特別な「総称型マクロ」が入った、
                            それが _Generic マクロで、広範囲な用途がある。
        */
        puts("9.4.3 多重定義 =========");
        int x = 99;
        double pi = 3.141592;
        char c = 'A';
        print(x);
        print(pi);
        printf("c is %c\tc is %d\tc is %x\n",c,c,c);
        print(c);       // char のケースはない ... default が使われる。
    }
    return 0;
}

