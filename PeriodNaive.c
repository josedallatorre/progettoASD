#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PeriodNaive.h"

#define MAX_LINE_SIZE 1000   // maximum size of a line of input


int main(int argc, char const *argv[])
{
    char a[MAX_LINE_SIZE];
    int size = scanArray(a); 
    if (size==1)
    {
        return 1;
    }
    
    int p = PeriodNaive(a, size);
    printf("%d", p);
    
    return 0;
}

int PeriodNaive(char *s, int n){
    for (int p = 1; p < n; p++)
    {
        char *prefix = substr(s,0,p);
        char *suffix = substr(s, p,n); 
        if (strncmp(prefix, suffix,p)==0)
        {
            return p;
        }
        
        
    }
    
}

char *substr(char *src, int i, int j){
    int len= j-i;
    char *dest = (char*)malloc(sizeof(char)*(len+1));
    strncpy(dest,(src+i), len);
    return dest;
}

int scanArray(char *a) {
    // scan line of text
    char line[MAX_LINE_SIZE];
    scanf("%[^\n]s", line);

    // convert text into array
    int size = 0, offset = 0, numFilled, n;
    do { 
        numFilled = sscanf(line + offset, "%c%n", &(a[size]), &n);
        if (numFilled > 0) {
            size++;
            offset += n;
        }
    } while (numFilled > 0);

    return size;
}