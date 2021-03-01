#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "PeriodNaive.h"

#define MAX_LINE_SIZE 1000   // maximum size of a line of input


int main(int argc, char const *argv[])
{
    char a[MAX_LINE_SIZE];
    int size = scanArray(a); 
    
    return 0;
}

int PeriodNaive(char *s, int size){
    
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