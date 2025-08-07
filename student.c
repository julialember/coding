#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char *name;
    int age;
    float *grades;
    int grades_len;
} Student;

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
    int i = 0, c; 
    float *result = NULL;
    while ((c = getch()) != '\n' && c != EOF){
        while (isspace(c) && c != '\n') c = getch();
        if (!isdigit(c) && c != EOF) {
            ungetch(c);
            return i;
        }
        result = realloc(result, sizeof(float) * (i + 1)); 
        if (!result) {
            free(result);
            printf("problem with mem allocated");
            return -1; 
        }
        for (result[i] = 0; isdigit(c); c = getch()) result[i] = result[i] * 10 + ( c - '0'); 
        if ( c == '.') {
            float power = 1.0; 
            for (c = getch(); isdigit(c); power *= 10, c = getchar()) result[i] = result[i] * 10 + ( c - '0');
            result[i]/=power; 
        }
        i++;
        while ( c == ' ' || c == '\t' ) c = getch();
        if ( c != EOF) ungetch(c);
    } 
    *ptr = result;
    return i;
}

int getname(char *s) {
    int i = 0; 
    for (; (s[i] = getchar()) != '\n'; i++);
    return i; 
}

Student* createStudent(){
    Student* new = malloc(sizeof(Student));
    printf("let me know name: "); 
    char s[30];
    new->name = malloc(getname(s) + 1);
    strcpy(new->name, s);
    printf("let me know your age: "); scanf("%d", &new->age);
    while (getchar() != '\n');
    printf("let me know grades: "); new->grades_len =  get_floats(&new->grades); 
    if (new->grades_len < 0) {
        free(new->name);
        free(new);
        return NULL;
    }
    return new;
}

void printStudent(const Student* st) {
    printf("name: %sage: %d\ngrades:\n", st->name, st->age);
    for (int i = 0; i < st->grades_len; i++) printf("%g ", st->grades[i]); 
}

void freeStudent(Student *st) {
    if (!st) return; 
    free(st->name); 
    free(st->grades);
    free(st);
}
int main() {
    Student *new = createStudent();
    printStudent(new);
    freeStudent(new);
}
