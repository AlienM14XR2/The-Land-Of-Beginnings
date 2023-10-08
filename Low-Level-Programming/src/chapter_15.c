/**
        第１５章    共有オブジェクトとコードモデル
    
    ```    
    gcc -O2 -std=c11 -pedantic-errors -Wall -Werror chapter_15.c -o ../bin/main
    ```
        
*/
#include "stdio.h"

int main(void) {
    puts("=== 第１５章    共有オブジェクトとコードモデル");
    /**
        15.2 再配置とPIC
        PIC（Position-Independent Code：位置に依存しないコード。いわゆる「位置独立コード」）
        
        -fPIC というオプションが、位置独立コード（PIC）の生成を強制する。
        ldd を使って、実行ファイルの依存関係が調べられる。
        ```
        ldd main
        ```        
    */
    /**
        15.3 例：C の動的ライブラリ
        
        GOT（Global Offset Table） と PLT（Program Linkage Table） について学ぶ前に
        C で最小のライブラリを作っておく。
        @see mainlib.c dynlib.c
    */
    return 0;
}
