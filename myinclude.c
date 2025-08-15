#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

double myatof(char *s) {
    double answer = 0;
    double dpart = 0;
    double exppart = 1;
    int sign = 1; 
    while (isspace(*s)) s++;
    if (!isdigit(*s) && *s != '.' && *s != '+' && *s != '-') return 0.0; 
    if (*s == '-') {
        s++; 
        sign = -1; 
    } else if (*s == '+') s++; 
    while (isdigit(*s)) answer = answer * 10 + (*s++ - '0');
    if (*s == '.') {
        s++;
        double power = 1.0; 
        for (; isdigit(*s); power*=10) dpart = dpart * 10 + (*s++ - '0'); 
        dpart/=power; 
    }
    if (*s == 'e' || *s == 'E') {
        exppart=0; 
        int exp_sign = 1;
        s++;
        if (*s == '-') {
            exp_sign = -1;
            s++;
        } else if (*s == '+') s++; 
        while (isdigit(*s)) exppart = exppart * 10 + (*s++ - '0');
        if (exp_sign == -1) exppart=1/pow(10, exppart); 
        else exppart = 1*pow(10, exppart); 
    } 
    return (answer + dpart) *sign * exppart; 
}

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

void bbleSort(int nums[], int biggestIndex) {
    for (int i = 0; i < biggestIndex; i++) 
        for (int q = 0; q <= biggestIndex - i; q++) 
            if (nums[q] > nums[q+1]) swap(&nums[q], &nums[q+1]);
}

void qSort(int nums[], int l, int h) {
    if (l>=h)return;
    int pivot = nums[(l + h)/2];
    int i = l, q = h; 
    while (i <= q) {
        while (nums[i++] < pivot); 
        while (nums[q--] > pivot);
        if (i <= q) swap(&nums[i++], &nums[q--]);
    }
    qSort(nums, l, q);
    qSort(nums, i, h);
}

int getflinebyname(char**answer, const char*filename, int maxlen) {
    if (!filename || maxlen <= 0) return -1; 
    if (*answer) {
        free(*answer); 
        *answer = NULL;
    }
    int n = open(filename, O_RDONLY); 
    if (n == -1) {
        fprintf(stderr, "error with file open\n");
        return -1; 
    }
    if (!(*answer = malloc(maxlen))) {
        close(n); 
        fprintf(stderr, "problems with mem allocate\n");
        return -1; 
    }
    int len = read(n, *answer, maxlen-1); 
    if (len < 0) return -1;  
    else if (len == 0) {
        free(*answer); 
        return -1;
    }
    for(int l = 0; l < len; l++) if ((*answer)[l] == '\n' || (*answer)[l] == '\0') len = l;
    char* temp = realloc(*answer, len);
    if (temp) *answer = temp;
    else {
        free(*answer); 
        close(n);
        fprintf(stderr, "problems with mem realloccated"); 
    }
    (*answer)[len] = '\0';
    close(n);
    return len;      
}

int getfline(char**answer, FILE* f, int maxlen) {
    if (!f || maxlen<=0) return -1;
    if (*answer) free(*answer); 
    if (!(*answer = malloc(maxlen))) return -1;
    int len = 0;
    for (int c = 0; ( c = getc(f) ) != EOF && c != '\n' && c != '\0' && len <= maxlen-1;) (*answer)[len++] = c;
    while (isspace((unsigned char)(*answer)[len])) len--;
    if (len == 0) return 0; 
    char* temp = realloc(*answer, len + 1);
    if (temp) *answer = temp; 
    (*answer)[++len] = '\0';
    return len;  
}

int getlinebynumber(char*buffer, char**to, int number) {
    if (!buffer || number <= 0) return -1;
    char* start= buffer;  
    for (; *buffer != '\0' && number > 0; buffer++) if (*buffer == '\n') {
        if (--number > 0) start = buffer+1;
        else buffer--;
    }
    if (*to) {
        free(*to);
        *to = NULL; 
    }
    *to = malloc(buffer-start + 1);
    if (!*to) {
        fprintf(stderr, "problems with mem allocate");
        return -1;
    }
    for (int len = 0; len < buffer-start; len++) (*to)[len] = start[len];
    (*to)[buffer-start] = '\0'; 
    return buffer-start;
}

int main() {
    char* buffer = NULL;
    int n = open("text.txt", O_RDONLY); 
    char buf[BUFSIZ];
    int q = read(n, buf, 100);
    for (int i = 1; i < 4; i++) {
    printf("line len = %d\n", getlinebynumber(buf, &buffer, i));
    printf("%s\n", buffer);}; 
}
