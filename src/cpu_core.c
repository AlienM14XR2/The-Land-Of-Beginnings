/**
 CPU のコア数が気になったよ。
 どうやって C言語 で取得するのかなと。
 
 https://hiroyukichishiro.com/get-nprocs-function-in-c-language/
*/

#include "stdio.h"
#include "stdlib.h"
#include "sys/sysinfo.h"

void debug_d(const char* message,int debug) {
    printf("%s\t%d\n",message,debug);
}

int main(void) {
    debug_d("get_nprocs_conf is ", get_nprocs_conf());
    debug_d("get_nprocs is ", get_nprocs());
    return 0;
}

