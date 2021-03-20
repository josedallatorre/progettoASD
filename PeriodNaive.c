#include <stdio.h>
#include <stdlib.h>
#include "Period.h"

#define MAX_LINE_SIZE 1000   // maximum size of a line of input


int main(int argc, char const *argv[])
{
    char a[MAX_LINE_SIZE];
    int size = scanArray(a); 
    int p = PeriodNaive(a, size);
    printf("%d", p);
    
    return 0;
}

int PeriodNaive(char *s, int n){
    for (int p = 1; p <= n; p++)
    {
        int j;
        for (j  = 0; (j<n-p)&&(s[j]==s[j+p]); j++)
        {          
        } 
        if (j==n-p){
            return p;
        }          
    }
    return n;
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