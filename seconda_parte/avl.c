#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
int main(int argc, char const *argv[])
{   
    //initialize the root
    AVL *T = createAVL();
    handleInput(T);
    freeTree(T, T->root);
    return 0;
}
int balance(AVL *T, Node *node){
    if (node == T->leaf)
    {
        return 0;
    }else if (node->right == T->leaf || node->left == T->leaf)
    {
        return node->height;
    }else{
        return (node->left->height - node->right->height);
    }
    
    
}
void fixup(AVL *T,Node *node){
    fixHeight(T, node->parent);
    if (node->parent == T->leaf)//node is root
    {
        return;
    }else if(node->parent->parent != T->leaf){
        Node *p = node->parent;
        Node *gp = p->parent;
        fixHeight(T, gp);
        if (balance(T,gp)<-1 || balance(T,gp)>1)  //grandparent isn't balanced
        {
            if (p == gp->left)
            {
                if (node == p->left)
                {
                    rightRotate(T, gp);
                }else{
                    leftRotate(T,p);
                    rightRotate(T, gp);
                }
                
            }else if (p == gp->right){
                if (node == p->right)
                {
                    leftRotate(T, gp);
                }else{
                    rightRotate(T, p);
                    leftRotate(T, gp);
                }
                
            }
            
        }
    }
    fixup(T, node->parent);
}
char *find(AVL *T, Node *node, int key){
    while(node != T->leaf && key != node->key){
        if(key<node->key){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    return node->text;
}
void leftRotate(AVL *T, Node *node){    
    Node *y = node->right;
    node->right = y->left;
    if(y->left != T->leaf){
	    y->left->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == T->leaf){
	    T->root= y;
    }
    else if(node == node->parent->left){
	    node->parent->left = y;
    }else{
	    node->parent->right = y;
    }
    y->left = node;
    node->parent = y;
    fixHeight(T, node);
    fixHeight(T, y);
}
void rightRotate(AVL *T,Node *node){
    Node *y = node->left;
    node->left = y->right;
    if(y->right != T->leaf){
	    y->right->parent = node;
    }
    y->parent = node->parent;
    if(node->parent ==T->leaf){
	    T->root = y;
    }
    else if(node == node->parent->right){
	    node->parent->right = y;
    }else{
	    node->parent->left = y;
    }
    y->right = node;
    node->parent = y;
    fixHeight(T, node);
    fixHeight(T, y);
}

void fixHeight(AVL *T,Node *node){
    if(node== T->leaf){
        return;
    }else{
    if(node->left == T->leaf && node->right == T->leaf){
	    node->height = 1;
    }else if(node->right == T->leaf){
        node->height = node->left->height+1;
    }else if(node->left == T->leaf){
        node->height = node->right->height+1;
        
    }else{
        node->height = max(node->left->height, node->right->height)+1;
    }
    }
}
int max(int x, int y){
    if(x>y) return x;
    else return y;
}

void handleInput(AVL *T){
    //initialize variable for the input
    char function[20];
    int key;
    char text[30];
    scanf("%s", function);
    while (strcmp(function, "exit")!= 0)
    {
        if ((strcmp(function, "insert"))==0)
        {        
            scanf("%d %s",&key, text);
            Node *node = createNode(key, text);
		    insertNode(T, node);
	        fixup(T, node);
        }
        if ((strcmp(function, "show"))==0)
        {
            show(T, T->root);
        }
         if ((strcmp(function, "find"))==0)
        {
            scanf("%d", &key);
            printf("\n%s",find(T, T->root, key));
        }
        scanf("%s", function);
    }
}
void insertNode(AVL *T, Node *node){
    Node *y = T->leaf;
    Node *x = T->root;
    while(x!=T->leaf){
	    y = x;
	    if(node->key < x->key){
	        x = x->left;
	    }else{
	        x = x->right;
	    }
    }
    node->parent = y;
    if(y == T->leaf){
	    T->root = node;
    }else if(node->key < y->key){
	    y->left = node;
    }else{
	    y->right = node;
    }
    node->left= T->leaf;
    node->right=T->leaf;
}
void show(AVL *T,Node *node){
    if (node == T->leaf)
    {
        printf("NULL ");
    }else{
        printf("%d:%s:%d ", node->key, node->text, node->height);
        show(T,node->left);
        show(T,node->right);
    }
}

AVL *createAVL() {
    struct AVL *T = (AVL *)malloc(sizeof(struct AVL));
    struct Node *leaf = (Node *)malloc(sizeof(struct Node));
    leaf->parent= leaf->right = leaf->left = NULL;
    T->leaf = leaf;
    T->root = T->leaf; 
    return T;
}

Node *createNode(int key, char *text){
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->text = (char *)malloc(strlen(text)+1); //make a local copy of the text
    strcpy(node->text, text);  //otherwise it will modified because it's a ptr
    node->height = 1;
    node->left= NULL;
    node->right= NULL;
    node->parent = NULL;
    return node;
}
void freeTree(AVL *T, Node *node){
    if (node == T->leaf || node == NULL)
    {
        return;
    }else{
        Node *right = node->right;
        Node *left = node->left;
        free(node->text);
        free(node);
        freeTree(T,right);
        freeTree(T,left);
    }
}
