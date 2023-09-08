# Start at 2023-09-08

# LOW-LEVEL PROGRAMMING （低レベルプログラミング）

この本の内容に沿って学習を進めるためのもの。

ただし、第 2 部  プログラミング言語 C からとする。

初っ端から非常に面白いことが記述されていたのでそれをここに記載する（コンパイルオプションに関するもの）。
```
-std=c89 あるいは -std=c90 で C89 または C90 の標準を選択する。

-pedantic-errors で、非標準の言語拡張を禁止する。

-Wall で、すべての警告（all warnings）を重要さに関わらす表示させる。

-Werror で、警告をエラーに変換する。これによって警告を含むコードがコンパイルされるのを防ぐ。
```
e.g. コンパイル 1
```
gcc -o main -ansi -pedantic-errors -Wall -Werror file.c file2.c
```
e.g. コンパイル 2
```
// 普段、私が何気なくよく利用しているコンパイル方法
gcc float_reinterpret.c -o ../bin/main

// 今回の学習を経て上記のコンパイルオプションを利用した場合
gcc -o main -ansi -pedantic-errors -Wall -Werror float_reinterpret.c
```
「コンパイル 2」 のコンパイルオプションを付けたものはエラーとなり実行ファイルは作られない。

