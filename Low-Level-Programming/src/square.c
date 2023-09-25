/**
        グローバル変数が他の .c ファイルで定義されていて、それにアクセスしたいときは、その変数を
    extern キーワードで宣言することが望ましい（必須ではない）。extern 変数を初期化してはいけない
    （もしそうしたらコンパイラが警告を発する）。
*/
extern int z;   // @see chapter_10.c

int square(int x) {
    return x*x;
}

int square_v2(int x) {
    return x * x + z;
}

