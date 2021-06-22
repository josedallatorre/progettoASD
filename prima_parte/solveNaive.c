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
	char *s1 = (char *)malloc((n-i+1)*sizeof(char));
	memset(s1, '\0', n-i+1);
	strncpy(s1, s, n-i);
	char *s2 = substr(s, i, n);
        if(strcmp (s1, s2)==0){
	    free(s1);
            free(s2);
	    return i;
	}else{
	free(s1);
	free(s2);
	}
    }
    return n;
}
char *substr(char *src, int start, int end){
    int len = end - start;
    char *dest = (char *)malloc((len+1)*sizeof(char));
    memset(dest, '\0', len+1);
    strncpy(dest, (src + start),len);
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
