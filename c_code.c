#include <ctype.h>
#include <math.h>
#include <stdio.h>
double atof(char[]); 

int main() {
    char s[10];
    for (int i = 0; (s[i] = getchar()) != '\n'; i++); 
    printf("%g", atof(s));
}

double atof(char s[]){
    int posit, sign; 
    double val; 
    for (posit = 0; isspace(s[posit]); posit++); 
    sign = s[posit] == '-' ? -1 : 1; 
    if (s[posit] == '-' || s[posit] == '+') posit++; 
    for (val = 0; isdigit(s[posit]); val = val * 10 + (s[posit++] - '0')); 
    if (s[posit] == '.'){
        int power = 1;
        for (posit++; isdigit(s[posit]); val = val * 10 + (s[posit++] - '0')) power *= 10; 
        val /= power;
    }
    if (s[posit] == 'e'){
        posit++;
        int e = 0 ;
        for (int i = s[posit] == '-' || s[posit] == '+' ? posit + 1: posit; isdigit(s[i]);  e = e * 10 + (s[i++] - '0'));
        if (s[posit] == '-') val/=pow(10, e);
        else val*=pow(10, e);
    }
    return sign * val;
}
