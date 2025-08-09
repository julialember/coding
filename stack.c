#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Stack;

Stack* createStack() {
    Stack *new = malloc(sizeof(Stack));
    new->capacity = 10;
    new->size = 0;
    new->data = malloc(sizeof(int) * new->capacity);
    return new;
}

void push(Stack *s, int value) {
    if (!s) return;
    if (s->size >= s->capacity) {
        s->capacity *= 2;
        int *temp = realloc(s->data, s->capacity * sizeof(int));
        if (!temp) {
            printf("mem error\n");
            return;
        }
        s->data = temp;
    }
    s->data[s->size++] = value;
}

int pop(Stack *s) {
    if (!s || s->size == 0) {
        printf("the stack is empty\n");
        return -1;
    }
    return s->data[--s->size]; 
}

int peek(Stack *s) {
    if (!s || s->size == 0) {
        printf("the stack is empty\n");
        return -1;
    }
    return s->data[s->size - 1];
}

void freeStack(Stack *s) {
    if (!s) return;
    free(s->data);
    free(s);
}

int main() {
    Stack *s = createStack();
    push(s, 12);
    push(s, 14);
    printf("%d, %d\n", pop(s), peek(s));
    freeStack(s);
    return 0;
}
