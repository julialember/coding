#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

void printerr(char* fmt, ...) {
    va_list args;
    va_start(args, fmt);
    fprintf(stderr, "error: "); 
    vfprintf(stderr, fmt, args); 
    fprintf(stderr, "\n"); 
    exit(1);
}

int main(int argc, char* argv[]) {
    if (argc < 2) goto fin;
    int n;
    char buf[BUFSIZ]; 
    int readed;
    for(int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-") == 0) fin: while (1) {
            if ((readed = read(0, buf, sizeof buf)) < 0) printerr("something wrong"); 
            if (readed == 0) {
                if (++i>=argc) return 0;
                break;
            } 
            if (write(1, buf, readed) != readed) printerr("error with write");
        };
        if ((n = open(argv[i], O_RDONLY)) == - 1) printerr("cat: error with file open: %s", argv[i]);
        while ((readed = read(n, buf, sizeof buf)) > 0) {
            if (write(1, buf, readed) != readed) printerr("cat: error with writing");
        } 
        if (readed < 0) printerr("error with reading file: %s", argv[i]); 
        if (n!=-1) close(n); 
    }
    return 0;
}
