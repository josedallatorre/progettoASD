typedef struct Node
{
    int key;
    char *text;
    int height;
    struct Node *left, *right, *parent;
}Node;
//handle input, given root(pass to other function)
void handleInput(Node *);
//show the avl
void show(Node *);
//create a new node, given key, text
Node *createNode(int, char *);
//free space
void freeTree(Node *);
//insert a node in AVL
Node *insertNode(Node *, Node*);
//fix-up proprierties, given node 
void fixup(Node *,Node *);
//fix-up height, given node
void fixHeight(Node *);
//return max of 2 integer
int max(int, int);
//rotate to the left a tree with given its root
void leftRotate(Node *,Node *);
//rotate to the right a tree with given its root
void rightRotate(Node *,Node *);
