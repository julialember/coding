#include <dirent.h>
#include <limits.h>
#include <string.h>
#include <stdio.h>
#include <sys/stat.h>

void find_with(char*, char*); 

int main(int argc, char* argv[]) {
    find_with(argv[1], argv[2]); 
    return 0;
}

void find_with(char* directory, char* extens) {
    if (!directory || !extens) return;
    DIR* dir = opendir(directory);
    if (!dir) {
        fprintf(stderr, "find_with: error with open directory: %s\n", directory);
        return;
    }
    char fullp[PATH_MAX]; 
    struct stat st;
    struct dirent* dd; 
    while ((dd = readdir(dir)) != NULL) {
        if (dd->d_name[0] != '.') {
            if (strlen(directory) + strlen(dd->d_name) + 2 > PATH_MAX) {
                fprintf(stderr, "find_with: the name is too long: %s/%s", directory, dd->d_name);
                continue;
            }
            snprintf(fullp, sizeof fullp, "%s/%s", directory, dd->d_name);
            if (lstat(fullp, &st) == -1) continue; 
            if (S_ISDIR(st.st_mode)) find_with(fullp, extens);
            else if (strstr(dd->d_name, extens) != NULL) printf("%s\n", fullp);
        }
    }
    closedir(dir); 
}
