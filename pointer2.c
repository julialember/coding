#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXBUFFER 100
int buffer[MAXBUFFER];
int buf_len = 0; 
int getch(void) {
    return buf_len > 0 ? buffer[--buf_len] : getchar(); 
}
void ungetch(int c) {
    if (buf_len >= MAXBUFFER) printf("the stack is full");
    else buffer[buf_len++] = c;
}
int get_floats(float**ptr){
    int c, i = 0;
    *ptr = NULL;
    while ((c = getch()) != EOF && c != '\n') {
    while (!isdigit(c)){
        ungetch(c);
        break;
    }
    float* tmp = realloc(ptr, sizeof(float) * (i + 1));
    if (!tmp) {
        free(tmp);
        return -1; 
    }
    *ptr = tmp; 
    *ptr[i] = 0;
    if (c == '.') {
        float power = 1.0;
        for (c = getch(); isdigit(c); c = getch(), power*=10)
           *ptr[i] = *ptr[i] *  10 + ( c - '0');
        *ptr[i]/=power;
        }
    i++;
    }
    return i;
}
int main() {
    float* ptr; 
    get_floats(&ptr);
    while (*ptr) printf("%g", *ptr++);
    
}
