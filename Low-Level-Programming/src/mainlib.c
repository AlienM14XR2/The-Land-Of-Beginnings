// ライブラリ関数宣言
extern void libfun(int value);  // これは通常コンパイルされたライブラリとともにヘッダファイルに入れて出荷される。

int global = 300;

int main(void) {
    libfun(42);
    return 0;
}
