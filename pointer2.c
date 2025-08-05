#include <ctype.h>
#include<stdio.h>
#include <stdlib.h>

#define MAXLEN 100
int buffer[MAXLEN]; 
int buf_len = 0; 
int getint(int*); 
int getch(void);
void ungetch(int);
void bubble_sort(int *, int*);

int main(){
    printf("let me know n: ");
    int n;
    if (!getint(&n)) {
        printf("error while reading number");
        return 1;
    }
    int *ptr = malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++) ptr[i] = n - i; 
    
    bubble_sort(ptr, ptr + n - 1);
    for (int i = 0; i < n; i++) printf("%d", ptr[i]);
    free(ptr);
    return 0; 
}

void  bubble_sort(int *ptr, int *end) {
    int swapped; 
    do {
        swapped = 0;
        for (int *i =  ptr; i < end; i++)
            if (*(i + 1) < *i) {
                int temp = *i; 
                *i = *(i + 1);
                *(i + 1) = temp; 
                swapped = 1; 
            }
        end--;
    } while (swapped);
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
