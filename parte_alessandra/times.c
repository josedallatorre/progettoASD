#include "times.h"
#include <time.h>
#include <math.h>
long getDiffTime(struct timespec end, struct timespec start){
    long temp = (((end.tv_sec - start.tv_sec)* 1.e+9 ) + 
    ((end.tv_nsec - start.tv_nsec)));
    return temp;
}
long getResolution() {                        // fare attenzione alle divisioni su valori di tipo intero... 
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    do {
        clock_gettime(CLOCK_MONOTONIC, &end);
    } while(start.tv_nsec == end.tv_nsec);
    return (end.tv_nsec - start.tv_nsec);
}