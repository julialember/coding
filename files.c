#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXLEN 40

int getfline(char **answer, FILE* f, int max_len) {
    if (!f || max_len <= 0 || !answer) return -1; 
    if (*answer) free(*answer); 
    *answer = malloc(max_len);
    if (!*answer) return -1;
    int c, len = 0; 
    while (len < max_len - 1 && (c = getc(f)) != EOF && c != '\n') (*answer)[len++] = c; 
    if (len == 0 || c == EOF) {
        free(*answer);
        *answer = NULL; 
        return -1; 
    }  
    for(len--; ((*answer)[len] == ' ' || (*answer)[len] == '\t') && len > 0; (*answer)[len--] = '\0');
    *answer = realloc(*answer, len + 1);  
    (*answer)[len++] = '\0';
    return len; 
}

void cmpFiles(FILE* f, FILE* s) {
    if (!f || !s) return;
    char* fir = NULL; 
    char* sec = NULL;
    for (int fl = getfline(&fir, f, MAXLEN),
    fs = getfline(&sec, s, MAXLEN);;){
        if (fl == -1 || fs == -1 || fs != fl){
            printf("%s\n", fir?fir:sec?sec:"unknow setuation\n");
            break;
        } 
        int i = 0; 
        for (; i < fl && fir[i] == sec[i]; i++); 
        if (fir[i] != '\0') {
            printf("%s", fir); 
            break;
        }
        fl = getfline(&fir, f, MAXLEN); 
        fs = getfline(&sec,s, MAXLEN); 
        if (fl == -1 && fs == -1) {
            printf("files are the same\n");
            free(fir);
            free(sec); 
            break;
        }
    }
    
}

int main() {
    FILE* text1 = fopen("text1.txt", "r");
    FILE* text2 = fopen("text.txt", "r");
    cmpFiles(text1, text2); 
}
