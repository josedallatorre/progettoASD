#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Period.h"
#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define CLOCK_MONOTONIC 1
int main(int argc, char const *argv[])
{   
    char a[MAX_LINE_SIZE];
    int size = scanArray(a); 
    int p = PeriodSmart(b, size);
    printf("%d", p);
    return 0;
}

int PeriodSmart(char *s, int n){
    int r [n+1];
    r[1]=0;
    int z=0;
    for (int i = 1; i <= n-1; i++)//per calcolare r[i+1]
    {
        z=r[i];
        while ((z>0)&&(s[i+1]!=s[z+1]))
        {
            z=r[z];
        }
        if (s[i+1]==s[z+1])
        {
            r[i+1]= z+1;
        }else{
            r[i+1]=0;
        }

    }
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
