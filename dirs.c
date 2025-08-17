#include <errno.h>
#include <dirent.h>
#include <stdio.h>
#include <sys/stat.h> 
#include <limits.h>
#include <string.h>

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

int main(int argc, char* argv[]){
    printext(argv[1], argv[2],  5);
}
