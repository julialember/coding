#include <ctype.h>
#include<stdio.h>
#include <stdlib.h>

#define MAXLEN 100
int buffer[MAXLEN]; 
int buf_len = 0; 
int getint(int*); 
int getints(int *); 
int getch(void);
void ungetch(int);

int main(){
    printf("let me know n: ");
    int n;
    if (!getint(&n)) {
        printf("error while reading number");
        return 1;
    }
    int *ptr = malloc(sizeof(int)*n);
    printf("let me know n numbers: "); 
    if (!getints(ptr)) {
        printf("error while readind numbers");
    }
}

int getints(int *ptr){
    int c, i = 0; 
    while ((c = getch()) != '\n'){
        while ((isspace(c))) c = getch(); 
        if (!isdigit(c) && c!= EOF) {
            ungetch(c);
            return 0;
        }
        while (isdigit(c)){
            ptr[i] = ptr[i] * 10 + (c - '0');
            c = getch();
        }
        i++; 
    }
    if (c != EOF) ungetch(c);
    return c;
}

int getint(int *ptr) {
    int c;
    while (isspace(c = getch())); 
    if (!isdigit(c) && c != EOF) {
        ungetch(c);
        return 0;
    }
    for (*ptr = 0; isdigit(c); c = getch()) *ptr = *ptr * 10 + ( c - '0'); 
    if ( c != EOF) ungetch(c); 
    return c;
}

int getch(void) {
    return buf_len > 0 ? buffer[--buf_len] : getchar();
}

void ungetch(int c){
    if (buf_len >= MAXLEN) printf("the stack is full");
    else buffer[buf_len++] = c;
}
