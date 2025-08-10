#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 40

int cmpLines(char **answer, FILE* f, int max_len) {
    if (!f || max_len <= 0 || !answer) return -1; 
    if (*answer) free(*answer); 
    *answer = NULL; 
    *answer = malloc(max_len);
    if (!*answer) return -1;
    int c, len = 0; 
    while (len < max_len - 1 && (c = getc(f)) != EOF && c != '\n') (*answer)[len++] = c; 
    while ((*answer)[len] == ' ' || (*answer)[len] == '\t') {
        (*answer)--; len--; 
    } 
    if (len == 0 || c == EOF) {
        free(*answer);
        *answer = NULL; 
        return -1; 
    } 
    (*answer)[len] = '\0';
    return len; 
}
int main() {
    FILE* text1 = fopen("text1.txt", "r");
    FILE* text2 = fopen("text.txt", "r");
}
