#include <stdio.h>
#include "void_string.c"
//#include "ascii_string.c"
//#include "unicode_string.c"
//#include "utf8_string.c"

int main() {

//    unsigned char a = 128;        А
//    unsigned char a = 143;        П
//    unsigned char a = 144;        Р
//    unsigned char a = 159;        Я

//    unsigned char a = 160;        а
//    unsigned char a = 175;        п
//    unsigned char a = 224;        р
//    unsigned char a = 239;        я

//    unsigned char a = 240;        Ё
//    unsigned char a = 241;        ё
    unsigned char a[2] = "а";
    printf("%d\n", 'A' - 'a');
    return 0;
}
