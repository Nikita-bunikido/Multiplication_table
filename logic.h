#include <stdio.h>
#include <time.h>

char generate(char *str){
    char a = rand()%9 + 1 + '0', b = rand()%9 + 1 + '0';
    str[0] = a;
    str[1] = ' ';
    str[2] = 'x';
    str[3] = ' ';
    str[4] = b;
    str[5] = ' ';
    str[6] = '=';
    str[7] = ' ';
    str[8] = '\0';
    return (a - '0') * (b - '0');
}

char check(char expresult, char *result){
    return (expresult == (char)atoi(result)) ? 1 : 0;
}