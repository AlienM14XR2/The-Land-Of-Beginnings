/**
    課題
    文字列の解析
    
  C 言語で行うべきか悩ましいが、これも暇つぶし、学びの一環としてまずは C で書いてみる。
  Web Scraping、HTML の解析が目的。現状具体的な解決方法が見えていないので、試行錯誤し
  ながらすすめる。
  
  - サンプルの HTML を用意する
  ```
  curl -o sample.html -X GET https://www.youtube.com/results?search_query=DMC+4+
  ```
  - libtidy を利用して、HTML の整形を行う
  ```
  tidy sample.html > sample-fix.html
  
  ※ 残念これがエラーになった、世の中の Web ページがどれでも正しく整形できるわけではないようだ。
  ```
  - 整形されたファイルを読み込む
  - 解析方法を考える：）
  
  少し調べただけだが、なかなか厄介な分野のようだ REST API のような利用ではないので場合によっては
  偽計業務妨害にあたるかもしれないし、取得したデータの利用も販売等の利益を得るような場合は罪に問
  われる可能性がある。今回は学習目的で、HTML データは利用するが、頻繁にウェブサイトへのアクセスを
  行うわけではないので、どちらも該当しないと思うが。
  
  参考文献
  C++ やスクリプト言語で行う方がいいとは思う。それらには既にライブラリがあるため。
  @see 
  https://brightdata.jp/blog/%E3%82%A6%E3%82%A7%E3%83%96%E3%83%87%E3%83%BC%E3%82%BF/best-languages-web-scraping
  https://brightdata.com/blog/how-tos/web-scraping-in-c-plus-plus#libraries
  
  e.g. compile
  gcc -O3 -DDEBUG -std=c17 -pedantic-errors -Wall -Werror string_parse.c -o ../bin/main
*/
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <string.h>




int main(void) {
  puts("START 文字列の解析 ===");
  puts("===   文字列の解析  END");
  return 0;
}

