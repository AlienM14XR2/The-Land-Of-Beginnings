/** ===========================================================================

Initial_C

OK、少し整理しよ。

- total 0.28 sec.
- なんとも言えないな、0.28 - 0.16 が正しいのかもしれないが。：）

であれば、ターゲットタイムは
0.12 sec

これをよりも速く 48,000 件のデータをファイルに書き込んだらC 言語の勝ち。
オレは、馬鹿みたいにループしてどれくらいなのか、それが一番気になっている。
それをはっきりさせないと、気分が悪い、先へは進めない。

では、さっそくやってみよう。

- struct (data)
- for loop

以上。

passed 0.025889 sec.
=============== Initial C END
jack@jack-M14xR2:

そりゃそうだよな。これはC++ が少し可愛そうだよね。
おそらく、C++ でも無駄にスレッドなど使わずに、アホみたいにループさせた方が
きっと速いだろうね。

予想通り。

Java で同じ処理、ループでも出来ることをマルチスレッドでスピードを求めることが
どれほど馬鹿げたことなのかと思ってる、今は。

*/
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include <time.h>


#define LOOP 48000

void println(const char* message) {
    printf("%s\n",message);
}

void debug_d(const char* message, const int debug) {
    printf("Kスケ: %s\t%d\n",message,debug);
}

void debug_ptr_d(const char* message, const int* debug) {
    printf("F原: %s\t%p\n",message,debug);
}

void debug_s(const char* message, const char* debug) {
    printf("DEBUG: %s\t%s\n",message,debug);
}

/* C++ での宣言と定義。
struct MockPerson {
// 型は厳密ではない。
    long pid;           // Null NO  PRI    auto_increment
    string address;     // Null YES
    string email;       // Null YES UNI
    string entryAt;     // Null NO  mysql datetime(6) C++ での正しい型がなんなのか知らない。
    string memo;        // Null YES
    string name;        // Null YES
    string password;    // Null YES
    string phone;       // Null YES
    string status;      // Null NO
    string updateAt;    // Null NO mysql datetime(6) C++ での正しい型がなんなのか知らない。
};
*/

//
// struct 
//
typedef struct {
    long pid;
    char address[256];
    char email[256];
    char entryAt[64];
    char memo[128];
    char name[128];
    char password[128];
    char phone[128];
    int  status;
    char updateAt[64];
} MockPerson;

int create_mock_person(MockPerson* mock) {
    println("------------- create_mock_person");
    mock[0].pid = 10000L;
    sprintf(mock[0].address,"%s","Tokyo, Japan.");
    sprintf(mock[0].email,"%s","alien@Loki.org");
    sprintf(mock[0].entryAt,"%s","2023-04-02 23:36:00");
    sprintf(mock[0].memo,"%s","おれだ");
    sprintf(mock[0].name,"%s","AllienM14xR2");
    sprintf(mock[0].password,"%s","root56789");
    sprintf(mock[0].phone,"%s","090xxxxxxxx");
    mock[0].status = 1;
    sprintf(mock[0].updateAt,"%s","2023-04-02 23:36:00");    
    return 0;
}

void print_mock_person(MockPerson* mock) {
    printf("pid is \t%ld\n",(*mock).pid);
    printf("address is \t%s\n",(*mock).address);
    printf("email is \t%s\n",(*mock).email);
    printf("entryAt is \t%s\n",(*mock).entryAt);
    printf("memo is \t%s\n",(*mock).memo);
    printf("name is \t%s\n",(*mock).name);
    printf("password is \t%s\n",(*mock).password);
    printf("phone is \t%s\n",(*mock).phone);
    printf("status is \t%d\n",(*mock).status);
    printf("updateAt is \t%s\n",(*mock).updateAt);
}


int main(void) {
    println("START Initial C ===============");
    int fd3s = 7;
    int* ae86 = &fd3s;
    debug_d("オレが振り切れないだと！！",fd3s);
    printf("%s\t%p\n","Kスケ: ヘアピンなのに減速しない？",&fd3s);    
    debug_ptr_d("前に出ないと勝ったって認めねーだろな、あのクソ親父",ae86);
    // int のデバッグはKスケにやってもらおう、慣らしは終わりだ。
    clock_t start = clock();
    MockPerson mock[1];
    create_mock_person(mock);
    if(1){
        print_mock_person(mock);
    }
    FILE* fp = fopen("initial_C_fin.txt","w");
    if(fp != NULL) {
        int i = 0;
        for(;i < LOOP;i++) {
                        fprintf(fp,"%d\t%ld\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%s\n",i,mock[0].pid,mock[0].address,mock[0].email,mock[0].entryAt,mock[0].memo,mock[0].name,mock[0].password,mock[0].phone,mock[0].status,mock[0].updateAt);
        }
        fclose(fp);
    }
    clock_t end = clock();
    printf("passed %lf sec.\n",(double)(end-start)/CLOCKS_PER_SEC);
    println("=============== Initial C END");
    return 0;
}
