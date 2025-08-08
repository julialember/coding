#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define MAXNAME 40
#define MAXVALS 100
int buffer[MAXVALS];
int buf_len = 0;

int getch(void){
    return buf_len > 0 ? buffer[--buf_len] : getchar();   
}

void ungetch(int c) {
    if (buf_len >= MAXVALS) printf("the stack is full\n");
    else buffer[buf_len++] = c; 
}

int get_floats(float**ptr) {
    int c, len = 0; 
    *ptr = NULL; 
    while ((c = getch()) != '\n' && c != EOF) {
        while (isspace(c) && c != '\n') c = getch();
        if (!isdigit(c) && c != EOF) {
            ungetch(c);
            break;
        }
        *ptr = realloc(*ptr, sizeof(float) * (len + 1));
        if (!*ptr){
            free(ptr);
            printf("problems with memory allocated");
            return -1; 
        }
        for ((*ptr)[len] = 0; isdigit(c); c = getch()) (*ptr)[len] = (*ptr)[len] * 10 + ( c - '0' ); 
        if ( c == '.' ) {
            float power = 1.0; 
            for (c = getch(); isdigit(c); c = getch(), power*=10) (*ptr)[len] = (*ptr)[len] * 10 + ( c - '0');
            (*ptr)[len]/=power; 
        }
        len++; 
        while ( c == ' ' || c == '\t' ) c = getch(); 
        if ( c != EOF ) ungetch(c);
    }
    return len;
}

typedef struct {
    char* name; 
    int age; 
    float* grades; 
    int grades_count; 
} Student; 

void copycat(char *from, char* to) {
    if (!from || !to) return; 
    while (*from) *to++ = *from++;
    *to++ = '\0';
}

int get_name(char *name) {
    int len = 0;
    for (int c = getchar(); c != '\n' && len < MAXVALS - 1 ; c = getchar()) name[len++] = c; 
    return len;
}

Student* createStudent(void) {
    Student* new = malloc(sizeof(Student));
    printf("let me know the name: ");
    char name[MAXVALS];
    new->name = malloc(get_name(name) + 1);
    copycat(name, new->name);
    printf("let me know age: ");
    scanf("%d", &new->age);
    while(getchar() != '\n'); 
    printf("let me know grades (sep with space)\n"); 
    if ((new->grades_count = get_floats(&new->grades)) < 0 || !*new->name) {
        free(new->name); 
        free(new->grades); 
        free(new); 
        printf("cant allocate the memory");
        return NULL;
    }
    return new;
}

void freeStudent(Student* st) {
    free(st->name); 
    free(st->grades); 
    free(st);
}

void printStudent(Student* st){
    printf("name: %s\nage: %d\ngrades:\n", st->name, st->age);
    for (int i = 0; i < st->grades_count; i++) printf("%g ", (st->grades)[i]);
}

int main() {
    Student* st = createStudent();
    printStudent(st);
    freeStudent(st);
}
