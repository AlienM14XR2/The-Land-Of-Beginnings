/**
 OK、久しぶりだな、C 言語。
  やることがない（実はある）ので、標準関数をひとつ、ひとつ動作確認してみる。
  初回は、うん、これもやはり、苦C 先生のところから拝借してやっていこうと思う。
 つまり、ファイル操作になるのか。
  
 C 言語　標準関数
 https://9cguide.appspot.com/r_lib.html
 
 C言語の標準ヘッダ一覧
 http://www.c-lang.org/detail/lib_header.html 
 
 まぁ、始めてみるか。
 なんだろ、VS CODE より、なんか良く感じる。　Linux 贔屓なのかな：）
 オレは gedit が好きなんだよ。
*/
#include "stdio.h"
#include "stdlib.h"

/**
 FILE *fopen(const char *filename, const char *mode);
 int fclose(FILE *fp);
 int fgetc(FILE *fp);
 char *fgets(char *s, int n, FILE *fp);
 int fputc(int c, FILE *fp);
 int fputs(const char *s, FILE *fp);
 size_t fread(void *ptr, size_t size, size_t nelem, FILE *fp);
 size_t fwrite(const void *ptr, size_t size, size_t nelem, FILE *fp);
 int fprintf(FILE *fp, const char *format, ...);
 int fscanf(FILE *fp, const char *format, ...);
 long ftell(FILE *fp);
 ・・・
 ・・・
 ・・・
 int scanf(const char *format, ...);
 
 ストーリ、仕様のようなものは必要だな。
 例えば、fopen fclose はワンセットだし。fputc fgetc のような対応したI/O
 で進めてみるかな。そこに、気分のアレンジをして、学習できたら楽しいかもね。
 
 最初は通常のファイルフォーマットで確認して、後半、バイナリで行ってみたい。
 */


int main(void) {
    printf("START Standard Library I/O ===============\n");
    printf("=============== Standard Library I/O END\n");
    return 0;
}



