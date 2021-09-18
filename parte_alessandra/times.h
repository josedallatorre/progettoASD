#define CLOCK_MONOTONIC 1
#define NMAX 1000000
#define NMIN 1000
//compute the resolution
extern  long getResolution();
//return difference between two given time
extern long getDiffTime(struct timespec end, struct timespec start);
