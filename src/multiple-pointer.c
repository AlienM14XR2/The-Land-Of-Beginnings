/**
    多重ポインタに興味があってな：）
    なんとなくだ。
*/

#include "stdio.h"

void println(const char* message) {
    printf("%s\n",message);
}
void ptr_d_debug(const char* message, const int* debug) {
    printf("%s\t value = %d\t address = %p\n",message,*debug,debug);
}
void ptr2_d_debug(const char* message, int** debug) {
    printf("%s\t value = %d\t address = %p\n",message,*(*debug),debug);
}
void ptr_f_debug(const char* message, const double* debug) {
    printf("%s\t value = %f\t address = %p\n",message,*debug,debug);
}

int main(void) {
    printf("START Multiple Pointer ===============\n");
    println("Yeah here we go.");    
    if(1) {
        int n = 69;
        int* pn = &n;
        ptr_d_debug("First about n is ",&n);
        ptr_d_debug("First about pn is ",pn);
        
        double pai = 3.14159;
        double* pp = &pai;
        ptr_f_debug("second about pai is ",&pai);
        ptr_f_debug("second about pp is ",pp);
    }
    if(2) {
        int a = 33;
        int* pa = &a;
        int** ppa = &pa;
        
        ptr_d_debug("a is ",&a);
        ptr_d_debug("pa is ",pa);
        ptr2_d_debug("ppa is ",ppa);
        
    }
    printf("=============== Multiple Pointer END\n");
    return 0;
}
