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
    int p = PeriodSmart(a, size);
    printf("%d", p);
    return 0;
}

int PeriodSmart(char *s, int n){
    int r [n];
    r[0]=0;
    int z=0;
    for (int i = 1; i < n; ++i)
    {
        z=r[i-1];
        while ((z>0)&&(s[i]!=s[z]))
        {
            z=r[z-1];
        }
        if (s[i]==s[z])
        {
            r[i]= z+1;
        }else{
            r[i]=0;
        }

    }
    for (int i = 0; i < n; i++){
	printf("r[%d]:%d\n", i, r[i]);
	}

    return n - r[n-1];
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
