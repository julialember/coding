#include <ctype.h>
#include <math.h>
#include <stdio.h>

double atof(char *s) {
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

int main() {
    char s[10]; 
    for(int i = 0; (s[i] = getchar()) != '\n'; i++); 
    printf("%g", atof(s));
}
