typedef enum COLOR {red, black}COLOR;
typedef struct Node
{
    int key;
    char *text;
    COLOR color;
    struct Node *left, *right, *parent;
}Node;
typedef struct RBT
{
    struct Node *root;
    struct Node *leaf;
}RBT;
//handle input, given root(pass to other function)
void handleInput(RBT *);
//show the avl
void show(RBT *, Node *);
//create RBT
RBT *createRBT();
//create a new node, given key, text
Node *createNode(int, char *);
//free space
void freeTree(RBT *, Node *);
//insert a node in AVL
void rbtInsert(RBT *, Node*);
//restore rbt properties
void rbtInsertFixup(RBT *, Node*);
//compute a left rotation of a given node
void leftRotate(RBT *, Node *);
//compute a right rotation of a given node
void rightRotate(RBT *, Node *);
