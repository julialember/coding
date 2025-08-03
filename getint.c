#include <ctype.h>
#include <stdio.h>
#define MAXBUFFER 100
char buffer[MAXBUFFER]; 
int buf_len = 0; 
void ungetch(int);
int getch(void);
int getint(int *);

int main(){
    int num = 0;
    if (getint(&num)) printf("%d", num);
}

int getch(void) {
    return buf_len > 0 ? buffer[--buf_len] : getchar(); 
}

void ungetch(int c) {
    if (buf_len >= MAXBUFFER) printf("the stack is already full");
    else buffer[buf_len++] = c; 
}

int getint(int *pn) {
    int c, sign;
    while (isspace(c = getch()));
    if (!isdigit(c) && c != EOF && c != '+' && c != '-') {
        ungetch(c);
        return 0; 
    }
    sign = ( c == '-' ) ? -1 : 1; 
    if ( c == '-' || c == '+' ){
        int next_char = getch();
        if (!isdigit(next_char)){
            ungetch(next_char);
            ungetch(c); 
            return 0;
        }
        c = next_char; 
    } 
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;
    if ( c != EOF ) ungetch(c);
    return c; 
}
