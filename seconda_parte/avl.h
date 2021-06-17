typedef struct Node
{
    int key;
    char *text;
    int height;
    struct Node *left, *right;
}Node;
//legge 
void handleInput(char *, int, char *);