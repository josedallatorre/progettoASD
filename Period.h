//number of letters used i.e. 3 = 'a','b','c'
#define NUM_LETT 3



//scan line from input and convert it to an array
int scanArray(char *);

//compute the period 
int PeriodNaive(char *, int);
int PeriodSmart(char *, int);

//compute the resolution
long getResolution();

//get the letter from alphabet
char getLetter();

//return a string from alphabet with given length
char *getString(int);