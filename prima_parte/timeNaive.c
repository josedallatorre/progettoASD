#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Period.h"
#include <time.h>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#define MAX_LINE_SIZE 1000   // maximum size of a line of input
#define CLOCK_MONOTONIC 1


int main(int argc, char const *argv[])
{
    long R = getResolution();
    int A = NMIN;
    double B = exp((log(NMAX)-log(A))/99);
    long Tmin= R*(1/0.001+1);
    struct timespec start, end;  
    for (int j = 0; j < 100; j++)
    {
        printf("inizio la %d-esima iterazione\n",j);
        int iter =0;
        int nj = A * pow(B,j);
	    char *s = getString(nj);
        long t;
        clock_gettime(CLOCK_MONOTONIC,&start);
        
        do{ 
            iter++;
            PeriodNaive(s,nj);  
            clock_gettime(CLOCK_MONOTONIC,&end);
            t = getDiffTime(end, start);             
            printf("Tmin: %ld time: %ld k: %d j: %d nj: %d\n",Tmin,t, iter,j, nj);
            
        }while(t<Tmin);      
        free(s);
        long exec_time = t/iter;
        FILE *fd = fopen("timesNaive.txt","a");
        fprintf(fd, "n:%d time:%ld\n",nj,exec_time);
        fclose(fd);
        
    }
    
    return 0;
}

long getDiffTime(struct timespec end, struct timespec start){
    long temp = (((end.tv_sec - start.tv_sec)* 1.e+9 ) + 
    ((end.tv_nsec - start.tv_nsec)));
    return temp;
}
char getLetter(){
    int i = 97 + (rand()%NUM_LETT);  //uso la tabella ASCII
    char c = i;    //converto da num ascii a char
    return c;
}
char *getString(int n){
    char *s = malloc(n+1*sizeof(char));
    for (int i = 0; i <= n; i++)
    {
        char c = getLetter();
        s[i] = c;
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
