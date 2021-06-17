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
    int p = PeriodNaive(a, size); 
    printf("%d\n", p);
    return 0;
}



int PeriodNaive(char *s, int n){
    //printf("n:%d\n", n);
    for (int i =1; i < n; ++i)
    
    {
        //printf("n:%d i:%d n-i:%d\n",n, i, n-i);
	char *s1 = (char *)malloc(sizeof(char) *(n-i+2));
	s1 = memcpy(s1, s, (n-i));
	char *s2 = substr(s, i, n);
	s1[n-i+1] = '\0';
	s1[n-i] = '\0';
        if(strcmp (s1, s2)==0)
	    return i;
	free(s1);
	free(s2);
    }
    return n;
}
char *substr(char *src, int start, int end){
    int len = end - start;
    char *dest = (char *)malloc(sizeof(char)*(len+1));
    dest = strncpy(dest, (src + start), len);
    dest[len +1] = '\0';
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
