#include <stdio.h>
#include <dirent.h>
#include <string.h>
#include <sys/stat.h>
#include <limits.h>

void read_dir(){
    DIR* dir = opendir("."); 
    struct dirent *entry;
    while((entry = readdir(dir)) != NULL) {
        if (entry->d_name[0] != '.') printf("%s\n", entry->d_name);
    }
    closedir(dir);
}

int files_count() {
    int c = 0;
    struct stat st; 
    DIR* dir = opendir(".");
    struct dirent *d; 
    while ((d = readdir(dir)) != NULL) {
        if (stat(d->d_name, &st) == -1) return -1;
        if (d->d_name[0] != '.' && S_ISREG(st.st_mode)) c++; 
    }
    closedir(dir);
    return c; 
}

void find_with(char* dir, char* name) {
    DIR* dd = opendir(dir);
    if (!dd) {
        vfprintf(stderr, "find_with: error with open: %s\n", dir);
        return;
    }
    struct dirent* diren;
    char full_path[PATH_MAX]; 
    struct stat st;
    while ((diren = readdir(dd)) != NULL) {
        if (diren->d_name[0] != '.') {
            snprintf(full_path, sizeof full_path, "%s/%s", dir, diren->d_name);  
            if (lstat(full_path, &st) == -1) continue; 
            if (S_ISDIR(st.st_mode)) find_with(full_path, name);
            else if (strstr(diren->d_name, name) != NULL) printf("%s\n", diren->d_name);
        }
    }
    closedir(dd);
}

int main(int argc, char* argv[]) {
    find_with(".", argv[1]);
    return 0; 
}

