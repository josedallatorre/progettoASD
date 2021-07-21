typedef struct Node
{
    int key;
    char *text;
    int height;
    struct Node *left, *right, *parent;
}Node;
typedef struct AVL
{
    struct Node *root;
    struct Node *leaf;
}AVL;
//handle input, given root(pass to other function)
void handleInput(AVL *);
//show the avl
void show(AVL *,Node *);
//create AVL
AVL *createAVL();
//create a new node, given key, text
Node *createNode(int, char *);
//free space
void freeTree(AVL *, Node *);
//insert a node in AVL
void insertNode(AVL *, Node*);
//fix-up proprierties, given node 
void fixup(AVL *,Node *);
//fix-up height, given node
void fixHeight(AVL *,Node *);
//return max of 2 integer
int max(int, int);
//rotate to the left a tree with given its root
void leftRotate(AVL *T, Node *);
//rotate to the right a tree with given its root
void rightRotate(AVL *T,Node *);
//find text given root and key
char *find(AVL *, Node *, int);
//return int, given root and key
int find2(AVL *, Node *, int);
//return balance of a node
int balance(AVL*, Node *);
//compute times
void computeTimes();
