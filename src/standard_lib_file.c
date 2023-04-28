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
 #include "stdio.h"
 #include "stdlib.h"

// 例の如く、暖機運転をしてからだ。
void println(const char* message) {
    printf("%s\n",message);    
}
void debug_ptr_d(const char* message, const int* debug) {
    printf("DEBUG: %s\tvalue = %d\taddress = %p\n",message,*debug,debug);
}
void debug_ptr_f(const char* message, const double* debug) {
    printf("DEBUG: %s\tvalue = %f\taddress = %p\n",message,*debug,debug);
}

int main(void) {
    printf("START Standard Library I/O ===============\n");
    println("It's my way :)");
    if(1) {
        int ms08 = 8;
        int* rx78 = &ms08;
        double pai = 3.14159;
        debug_ptr_d("ms08 is ",&ms08);
        debug_ptr_d("rx78 is ",rx78);
        debug_ptr_f("pai is ",&pai);
        
    }
    if(2) {
        /**
                        ここで少しだけ仕様のようなものを考えてみる。
           - sample-2023-04-20-v2.txt (a+)
           - Open Close
           - fputc fgetc
           1文字ファイルへ書き込み、そして1文字ファイルから読み込む。
        */
        println("---------------------------- 2");
        FILE* fp = NULL;
        fp = fopen("sample-2023-04-20-v2.txt","a+");
        if(fp != NULL) {
           fputc('N',fp);fputc('u',fp);fputc('m',fp);fputc('b',fp);fputc('\n',fp);
           fclose(fp);
           fp = NULL;
        }
        fp = fopen("sample-2023-04-20-v2.txt","a+");
        if(fp != NULL) {
           char c;
           while((c = fgetc(fp)) != EOF) {
                printf("%c",c);     
           }
        }
    }
    if(3) {
        /**
                        同じように、続けてみる。
           - sample-2023-04-20-v3.txt (w+)
           - open close
           - fputs fgets
                       うん、実は、意識的に避けてることがある。
                       それは、ファイルポインタの位置、なんとなくだけどね。
           Write とRead をわざわざファイルをクローズして、やってるのもそれ。
        */
        println("---------------------------- 3");
        FILE* fp = NULL;
        fp = fopen("sample-2023-04-20-v3.txt","w+");
        if(fp != NULL) {
            fputs("Welcome to the jungle, we've got fun n games.\n",fp);
            fputs("ジャングルへようこそ、楽しいゲームが待ってるぞ。\n",fp);
            fputs("We go everything you want. Honey, we know the names\n",fp);
            fputs("お前の欲しいものは何でもある。ハニー　評判は知ってるぜ。\n",fp);
            fclose(fp);
            fp = NULL;
        }
        fp = fopen("sample-2023-04-20-v3.txt","r");
        if(fp != NULL) {
            char line[256];
            int size = sizeof(line);
            debug_ptr_d("sizeof(line) is ",&size);
            int i = 0;
            while((fgets(line,sizeof(line),fp)) != NULL){
                i++;
                printf("%d: %s",i,line);
            }
            fclose(fp);
        }
    }
    if(4) {
        /**
                            バイナリファイルの読み書き。
            - sample-2023-04-20-v4.bin (wb/rb)
            - open close
            - fwrite fread
            
            https://monozukuri-c.com/langc-funclist-binaryfile/
            #include <stdio.h>
            size_t fwrite(void * buf, size_t size, size_t num, FILE * fp);
            size_t fread(void * buf, size_t size, size_t num, FILE * fp);
        */
        println("---------------------------- 4");
        FILE* fp = NULL;
        fp = fopen("sample-2023-04-20-v4.bin","wb");
        if(fp != NULL) {
            unsigned char data[16] = {
                0x01,0x02,0x03,0x04,0x05,0x06,0x07,0x08,
                0x09,0x0A,0x0B,0x0C,0x0D,0x0E,0x0F,0x10
            };
            fwrite(data,sizeof(unsigned char),sizeof(data)/sizeof(data[0]),fp);
            fclose(fp);
            fp = NULL;
        }
        fp = fopen("sample-2023-04-20-v4.bin","rb");
        if(fp != NULL) {
            unsigned char data[16] = {0};
            printf("sizeof(data)/sizeof(data[0]) is %ld\n",sizeof(data)/sizeof(data[0]));
            fread(data,sizeof(unsigned char),sizeof(data)/sizeof(data[0]),fp);
            for(int i=0 ; i < sizeof(data)/sizeof(data[0]) ;i++) {
                printf("0x%02x\t",data[i]);
            }
            printf("\n");
            fclose(fp);
        }
    }
    if(5) {
        /**
                          構造体を用いた、バイナリファイルの読み書き。
            - sample-2023-04-27-v5.bin (wb/rb)
            - typedef struct {...} S_STATUS
            - open close
            - fwrite fread
        */
        println("---------------------------- 5");
        typedef struct {
            char          name[16];     // 名前
            unsigned long hp;           // HP
            unsigned long mp;           // MP
            unsigned char level;        // レベル
            unsigned char strength;     // 強さ
            unsigned char speed;        // 素早さ
            unsigned char wisdom;       // 賢さ
            unsigned long experience;   // 経験値
        } S_STATUS;
        FILE* fp = NULL;
        if(5.1) {
            println("write save data ... ");
            S_STATUS characters[] = {
                {"Brave",  180, 50,  1, 22, 16, 15, 0},
                {"Knight", 150,  0,  1, 25, 18,  6, 0},
                {"Wizard", 90, 120,  1, 13, 10, 22, 0},
            };
            fp = fopen("sample-2023-04-27-v5.bin","wb");
            if(fp != NULL) {
                fwrite(characters,sizeof(S_STATUS),sizeof(characters)/sizeof(characters[0]),fp);
                fclose(fp);
                println(" ... end");
            }
            fp = NULL;
        }
        if(5.2) {
            println("read save data ... ");
            S_STATUS characters[3] = {0};
            fp = fopen("sample-2023-04-27-v5.bin","rb");
            if( fp != NULL ) {
                fread(characters,sizeof(S_STATUS),sizeof(characters)/sizeof(characters[0]),fp);
                for(int i=0; i < sizeof(characters)/sizeof(characters[0]) ;i++) {
                    printf("%s, HP:%ld, MP:%ld, Level:%d, Strength:%d, Speed:%d, Wisdom:%d, Exp:%ld\n",characters[i].name, characters[i].hp, characters[i].mp, characters[i].level, characters[i].strength, characters[i].speed, characters[i].wisdom, characters[i].experience);
                }
                fclose(fp);
            }
        }
    }
    printf("=============== Standard Library I/O END\n");
    return 0;
}
