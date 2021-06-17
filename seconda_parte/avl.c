#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
int main(int argc, char const *argv[])
{   
    char function[20];
    int key;
    char text[30];
    scanf("%s", function);
    while (strcmp(function, "exit")!= 0)
    {
        if ((strcmp(function, "insert"))==0)
        {
            printf("do insert");
        }
        if ((strcmp(function, "show"))==0)
        {
            printf("do show");
        }
         if ((strcmp(function, "find"))==0)
        {
            printf("do find");
        }
        scanf("%s", function);
    }
    
    
    return 0;
}

