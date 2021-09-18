typedef struct Node
{
    int key;
    char *text;
    int height;
    struct Node *left, *right, *parent;
}Node;
typedef struct BST
{
    struct Node *root;
    struct Node *leaf;
}BST;
//handle input, given root(pass to other function)
void handleInput(BST *);
//show the bst
void show(BST *,Node *);
//create BST
BST *createBST();
//create a new node, given key, text
Node *createNode(int, char *);
//free space
void freeTree(BST *, Node *);
//insert a node in BST
void insertNode(BST *, Node*);
//find text given root and key
char *find(BST *, Node *, int);
//return int, given root and key
int find2(BST *, Node *, int);
//return balance of a node
int balance(BST*, Node *);
//compute times
void computeTimes();