#include <stdio.h>

void strcats(char*, char*); 
int strend(char*, char*); 

int main() {
    char s[] = "hello world";
    char t[] = ""; 
    printf("%d", strend(s, t));
}

void strcats(char *s, char *t) {
    while (*++s);
    while ((*s++ = *t++) != '\0'); 
}

int strend(char *s, char *t) {
    if (!*t) return 1; 
    char *t_start = t; 
    while (*t++); 
    while (*s++);
    while (t > t_start && s > t_start && *--s == *--t);
    return (t_start == t && *s == *t);
} 
