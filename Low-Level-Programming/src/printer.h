/**
    インクルードガードの例
    次のようにすることで、実行ファイル作成時に関数が
    多重定義されることを防ぐことができる。
*/
#ifndef _PRINTER_H_     // _PRINTER_H_ が定義されていなかったら 
#define _PRINTER_H_     // _PRINTER_H_ を定義するし、以下の関数のプロトタイプ宣言が読まれる。

void print_one(void);
void print_two(void);

#endif                  // ifndef ディレクティブの終わり
