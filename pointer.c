#include <ctype.h>
#include<stdio.h>
#include <stdlib.h>


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
#define MAXLEN 100
int buffer[MAXLEN]; 
int buf_len = 0; 
int getint(int*); 
int getch(void);
void ungetch(int);
void bubble_sort(int *, int*);

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

struct Node {
    int data;
    struct Node *next; 
};

void addNode(struct Node *self, struct Node *next){
    if (!self->next) self->next = next;
    else {
        self = self->next;
        while (self->next) self = self->next; 
        self->next = next;
    }
}

struct Node* createNode(int data) {
    struct Node* node = malloc(sizeof(struct Node));
    node->data = data; 
    node->next = NULL;
    return node; 
}

void printList(struct Node *self){
    if (!self->next){
        printf("the stack is empty");
        return;
    }
    printf("%d\n", self->data);
    while (self->next) {
        printf("%d\n", self->next->data);
        self = self->next; 
    }
}


