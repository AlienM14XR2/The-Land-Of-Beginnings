/**
        第１３章    良いコードをかくには
        
    ```
    // stack.c をここで検証する場合は次のようにコンパイルする。
    
    gcc -c -std=c11 -pedantic-errors -Wall -Werror stack.c
    gcc -c -std=c11 -pedantic-errors -Wall -Werror chapter_13.c
    gcc -o ../bin/main chapter_13.o stack.o
    
    // chapter_13.c のみの実行ファイルを作成する場合は次のようにコンパイルする。
    gcc -std=c11 -pedantic-errors -Wall -Werror chapter_13.c -o ../bin/main
    
    // chapter_13.c のみの実行ファイルを作成し、アサートを無効にする。
    gcc -std=c11 -pedantic-errors -Wall -Werror -D NDEBUG chapter_13.c -o ../bin/main
    ```
*/
#include "stdio.h"
#include "malloc.h"
#include "assert.h"

#include "stack.h"

static void div_by_zero(const int x, const int y) {
    fprintf(stderr, "ERROR: Division by zero: %d / %d\n",x,y);
}

/**
    第１仮引数：分子
    第２仮引数：分母
    戻り値：分子 / 分母の結果
    例外発生時は 0 を返す。
*/
int div(int x,int y,void (onerror)(int,int)) {
    if(y != 0) {
        return x/y;
    } else {
        onerror(x,y);
        return 0;
    }
}

//
// 13-15
//
enum stat {
    STAT_OK,
    STAT_ERR_OPEN,
    STAT_ERR_CLOSE,
    STAT_ERR_WRITE
};

static enum stat dump(FILE* f) {
    if( fprintf(f,"this is the dump %d",333) ) {
        return STAT_OK;
    } else {
        return STAT_ERR_WRITE;
    }
}

static enum stat func(void) {
    enum stat dump_stat;
    FILE* f;
    f=fopen("dump.txt","w");
    if(!f) {
        return STAT_ERR_OPEN;
    }
    
    dump_stat = dump(f);
    
    if(dump_stat != STAT_OK) {
        return dump_stat;
    }
    if( fclose(f) != 0 ) {      // fclose は成功時 0 を返却する ... 書籍が間違ってた。
        return STAT_ERR_CLOSE;
    }
    return STAT_OK;
}
int main(void) {
    puts("第１３章    良いコードをかくには");
    if("13.6 アサート") {
        puts("--- 13.6 アサート");
        int x = 0;
        printf("x is %d\n",x);
        assert(x != 0); // assert マクロの利用 ... 期待値を設定する、つまりこの場合はアサーションになる。@see gcc -std=c11 -pedantic-errors -Wall -Werror -D NDEBUG chapter_13.c -o ../bin/main
        
        // アサートは、プログラムの状態に一貫性がないことを示すような「ありえない条件に」のチェックに使うべきだ。
        // ユーザ入力のチェックにアサートを使ってはいけない。
    }
    if("13.7 エラー処理") {
        puts("--- 13.7 エラー処理");
        /**
            C におけるエラーに対処する方法は、主に次の３つである。
            1. リターンコードを使う。結果を返さないサブルーチンの場合なら、ポインタを引数に追加して結果を返す。
        */
        
        /**
            2. コールバックを使う。
        */
        int x = 10,y = 2;
        printf("div(%d,%d) is %d\n",x,y,div(x,y,div_by_zero));
        y = 0;
        printf("div(%d,%d) is %d\n",x,y,div(x,y,div_by_zero));
        /**
            3. longjmp を使う ... これは高度なテクニックなので、14.3 節で説明する。
        */
        
        // さらに goto を利用した古典的なものもある ... 筆者はメモリリークを例に挙げ、そのメンテナンス性の悪さを指摘していた。
    }
    if("13.9 柔軟性について") {
        puts("--- 13.9 柔軟性について");
        printf("func_result is %d\n",func());
    }
    return 0;
}
