typedef struct Node
{
    int key;
    char *text;
    int height;
    char *color;
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
Node *rbtInsert(Node *, Node*);
//restore rbt properties
void rbtInsertFixup(Node *, Node*);
//compute a left rotation of a given node
void leftRotate(Node *, Node *);
//compute a right rotation of a given node
void rightRotate(Node *, Node *);
