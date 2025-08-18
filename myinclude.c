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

int getnextline(char**to, char*buffer, int maxlen) {
    if (!buffer || maxlen <= 0) return -1;
    int len = 0; 
    if (*to) {
        free(*to);
        *to = NULL;
    }
    *to = malloc(maxlen);
    for (; buffer[len] != '\n' && buffer[len] != '\0' && len < maxlen - 1; len++) (*to)[len] = buffer[len];
    char* temp = realloc(*to, len + 1);
    if (temp) *to = temp; 
    (*to)[len] = '\0';
    return len;
}


#include <dirent.h>
#include <string.h>
#include <errno.h>
#include <sys/stat.h>
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

void printext(char* dirname, char*ext, int deep) {
    if (!dirname || !ext) return;
    DIR* dir = opendir(dirname);
    if (!dir) {
        fprintf(stderr, "can't open the dir: %s\n", dirname);
        return;
    }
    struct dirent* dd; 
    struct stat st; 
    char *dot;
    char fullname[PATH_MAX]; 
    while ((dd = readdir(dir)) != NULL) {
        if ((strcmp(dd->d_name, ".") == 0 || strcmp(dd->d_name, "..") == 0)) continue;
        if (snprintf(fullname, sizeof fullname, "%s/%s", dirname, dd->d_name)>= PATH_MAX) {
            fprintf(stderr, "the filelen is too long: %s/%s", dirname, dd->d_name);
            continue;
        }
        if (lstat(fullname, &st) == -1) {
            fprintf(stderr, "cant stat the file: %s\n%s\n", fullname, strerror(errno));
            continue;
        }
        if (S_ISLNK(st.st_mode)) continue;
        if (S_ISDIR(st.st_mode) && deep > 0) printext(fullname, ext, deep -1 );
        else {
            dot = strchr(dd->d_name, '.');
            if (dot && strcmp(dot, ext) == 0) printf("%s\n", fullname);
        }
    }
    closedir(dir);
}

void printdir(char* dirname, int deep) {
    if (!dirname) return; 
    DIR* dir = opendir(dirname);
    if (!dir) {
        fprintf(stderr, "printdir: can't open directory: %s\n", dirname);
        return;
    }
    struct dirent* dd; 
    char fullname[PATH_MAX]; 
    struct stat st; 
    while ((dd = readdir(dir)) != NULL) {
        if (strcmp(dd->d_name, ".") == 0 || strcmp(dd->d_name, "..") == 0) continue; 
        if (snprintf(fullname, sizeof fullname, "%s/%s", dirname, dd->d_name) >= PATH_MAX) {
            fprintf(stderr, "printdir: the dirname is too long: %s\n", fullname);
            continue;
        }
        if (lstat(fullname, &st) == -1) {
            fprintf(stderr, "printdir: cat stat the file: %s\n", fullname);
            continue;
        }
        if (S_ISLNK(st.st_mode)) continue;
        if (S_ISDIR(st.st_mode) && deep > 0) printdir(fullname, deep - 1);
        else if (S_ISREG(st.st_mode)) {
            printf("%s\n", fullname);
        }
        
    }
    closedir(dir);
}

void print_size(char*name) {
    if (!name) return; 
    struct stat st;
    if(stat(name, &st) == -1) {
        fprintf(stderr, "error with file: %s\n", name);
        return;
    } else printf("sizeof '%s': %lld\n", name, (long long)st.st_size);
} 

void print_last() {
    #include <time.h>
    DIR* dir = opendir(".");
    if (!dir) {
        fprintf(stderr, "error with open '.' dir");
        return;
    }
    time_t now = time(NULL); 
    struct dirent* dd;
    struct stat st;
    while ((dd = readdir(dir)) != NULL) {
        if (stat(dd->d_name, &st) == -1) {
            fprintf(stderr, "error with stat file: '%s': %s\n", dd->d_name, strerror(errno) );
            continue;
        }
        if (difftime(now, st.st_mtime) < 7 * 24 * 3600) {
            printf("%s: %s", dd->d_name, ctime(&st.st_mtime));
        }
    }
    closedir(dir);
}

void thebiggest() {
    DIR* dir = opendir(".");
    if (!dir) {
        fprintf(stderr, "error with open '.' directory\n");
        return;
    }
    long long biggest = 0;
    struct dirent* d;
    struct stat st; 
    while ((d = readdir(dir)) != NULL) {
        if (lstat(d->d_name, &st) == -1) {
            fprintf(stderr, "error with stat file: '%s': %s\n", d->d_name, strerror(errno));
            continue; 
        }
        if (S_ISREG(st.st_mode) && st.st_size > biggest) biggest = st.st_size; 
    }
    printf("%lld", biggest);
    closedir(dir);
}


int main(int argc, char* argv[]) {
 
}
