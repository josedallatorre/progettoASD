#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Period.h"
#include <time.h>
#include <math.h>
#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define CLOCK_MONOTONIC 1

int main(int argc, char const *argv[])
{   
    long res = getResolution();
    int A = 1000;
    //double B = exp((log(500000)-log(A))/99);
    int B = 1.1;
    printf("%d",B);
    for (int j = 0; j < 99; j++)
    {
        int nj = A * pow(B,j);
        printf("%d\n",nj);
        char *s = getString(nj);
        printf("%s",s);
        //int p = PeriodSmart(s,nj);
        //printf("\n%d",p);
        free(s);
    }
    return 0;
}
char getLetter(){
    int i = 97 + (rand()%NUM_LETT);  //uso la tabella ASCII
    char c = i;    //converto da num ascii a char
    return c;
}
char *getString(int n){
    char *s = (char *)malloc(n*sizeof(char));
    for (int i = 0; i <= n; i++)
    {
        if(i==0){            //uso i valori compresi tra
                             //s[1..n]  
        }else{
            char c = getLetter();
            s[i] = c;
        }
    }
    return s;
}

    
long getResolution() {                        // fare attenzione alle divisioni su valori di tipo intero... 
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}
int PeriodSmart(char *s, int n){
    int *r = (int*)malloc((n+1)* sizeof (int) );
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
    int risp = n - r[n];
    free(r);
    return risp; 
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