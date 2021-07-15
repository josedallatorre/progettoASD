#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
int main(int argc, char const *argv[])
{   
    //initialize the root
    Node *root = NULL;
    handleInput(root);
    freeTree(root);
    return 0;
}
void fixup(Node *root,Node *node){
    if(node == NULL){//last node was the root
	return;
    }  	
    fixHeight(node);
    if (node->right ==NULL|| node->left==NULL){
    }
    else if(node->right->height > node->left->height +1){
	rightRotate(root, node);
	fixHeight(node);
    }
    else if(node->right->height +1 < node->left->height){
	leftRotate(root,node);
	fixHeight(node);
    }
    fixup(root, node->parent);
    

}
char *find(Node *node, int key){
    while(node != NULL && key != node->key){
        if(key<node->key){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    return node->text;
}
void leftRotate(Node  *root, Node *node){    
    Node *y = node->right;
    node->right = y->left;
    if(y->left != NULL){
	y->left->parent = node;
    }
    y->parent = node->parent;
    if(node->parent == NULL){
	root= y;
    }
    else if(node == node->parent->left){
	node->parent->left = y;
    }else{
	node->parent->left = y;
    }
    y->left = node;
    node->parent = y;
}
void rightRotate(Node *root,Node *node){
    Node *y = node->left;
    node->left = y->right;
    if(y->right != NULL){
	y->left->parent = node;
    }
    y->parent = node->parent;
    if(node->parent ==NULL){
	root = y;
    }
    else if(node == node->parent->right){
	node->parent->right = y;
    }else{
	node->parent->right = y;
    }
    y->right = node;
    node->parent = y;
}

void fixHeight(Node *node){
    if(node->left == NULL && node->right == NULL){
	    node->height = 1;
    }else if(node->right == NULL){
        node->height = node->left->height+1;
    }else if(node->left == NULL){
        node->height = node->right->height+1;
        
    }else{
        node->height = max(node->left->height, node->right->height)+1;
    }
}
int max(int x, int y){
    if(x>y) return x;
    else return y;
}

void handleInput(Node *root){
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
	    if(root == NULL){
		root = node;
	    }else{
		root = insertNode(root, node);
	    }
	    fixup(root, node);
        }
        if ((strcmp(function, "show"))==0)
        {
            show(root);
        }
         if ((strcmp(function, "find"))==0)
        {
            scanf("%d", &key);
            printf("%s\n",find(root, key));
        }
        scanf("%s", function);
    }
}
Node *insertNode(Node *root, Node *node){
    Node *y = NULL;
    Node *x = root;
    while(x!=NULL){
	y = x;
	if(node->key < x->key){
	    x = x->left;
	}else{
	    x = x->right;
	}
    }
    node->parent = y;
    if(y == NULL){
	root = node;
    }else if(node->key < y->key){
	y->left = node;
    }else{
	y->right = node;
    }
    return root;
}
void show(Node *node){
    if (node == NULL)
    {
        printf("NULL ");
    }else{
        printf("%d:%s:%d ", node->key, node->text, node->height);
        show(node->left);
        show(node->right);
    }
}
Node *createNode(int key, char *text){
    Node *node = (Node *)malloc(sizeof(Node));
    node->key = key;
    node->text = (char *)malloc(strlen(text)+1); //make a local copy of the text
    strcpy(node->text, text);  //otherwise it will modified because it's a ptr
    node->height = 0;
    node->left= NULL;
    node->right= NULL;
    node->parent = NULL;
    return node;
}
void freeTree(Node *node){
    if (node == NULL)
    {
        return;
    }else{
        Node *right = node->right;
        Node *left = node->left;
        free(node);
        free(node->text);
        freeTree(right);
        freeTree(left);
    }
}
