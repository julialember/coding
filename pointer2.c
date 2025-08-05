#include <stdio.h>

void reverse(char* ptr) {
    char *s = ptr;
    while (*s) s++; 
    s--; 
    while (ptr < s){
        *ptr^=*s; 
        *s^=*ptr;
        *ptr++^=*s--; 
    }
}

int main() {
    char s[] = "hello world"; 
    reverse(s); 
    printf("result: %s", s);    
}
