#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
int main(int argc, char const *argv[])
{   
    //initialize the root
    Node *root = NULL;
    handleInput(root);
    freeTree(root);
    return 0;
}
Node *rbtInsert(Node *root, Node *node){
    Node *y = NULL;
    Node *x = root;
    while(x != NULL){
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
    }
    else if(node->key < y->key){
	y->left = node;
    }
    else{
	y->right = node;
    }
    node->left = NULL;
    node->right = NULL;
    node->color = "red";
    rbtInsertFixup(root, node);
    return root;
}
void rbtInsertFixup(Node *root, Node *node){
    Node *y = NULL;
    while(strcmp(node->parent->color ,"red")==0){
	if(node->parent == node->parent->parent->left){
	    y = node->parent->parent->right;
	    if(strcmp(y->color,"red")==0){ //case 1 
		node->parent->color = "black";
		y->color = "black";
		node->parent->parent->color = "red";
		node = node->parent->parent;
	    }
	    else if(node == node->parent->right){//case 2
		node = node->parent;
		leftRotate(root, node);
		}
	    node->parent->color = "black";//case 3
	    node->parent->parent->color = "red";
	    rightRotate(root, node->parent->parent);
	}
	else{
	    y = node->parent->parent->left;
	    if(strcmp(y->color, "red")==0){ //case 1 
		node->parent->color = "black";
		y->color = "black";
		node->parent->parent->color = "red";
		node = node->parent->parent;
	    }
	    else if(node ==node->parent->left){//case 2
		node = node->parent;
		rightRotate(root, node);
		}
	    node->parent->color = "black";//case 3
	    node->parent->parent->color = "red";
	    leftRotate(root, node->parent->parent);
	}
	root->color = "black";
    }
}

void leftRotate(Node *root, Node *x){
    Node *y = x->right;
    x->right = y-> left;//turn y subtree into x right subtree
    if (y->left != NULL){
	y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == NULL){
	root = y;
    }
    else if(x == x->parent->left){
	x->parent->left = y;
    }
    else{
	x->parent->right = y;
    }	
    y->left = x;
    x->parent = y;
}
void rightRotate(Node *root, Node *x){
    Node *y = x->left;
    x->left = y->right; //turn y subtree into x left subtree
    if(y->right !=NULL){
	y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent ==NULL){
	root = y;
    }
    else if(x == x->parent->right){
	x->parent->right = y;
    }
    else{
	x->parent->left = y;
    }
    y->right = x;
    x->parent = y;
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
		    root = rbtInsert(root, node);
	    }
        }
        if ((strcmp(function, "show"))==0)
        {
            show(root);
        }
         if ((strcmp(function, "find"))==0)
        {
            printf("TODO find\n");
        }
        scanf("%s", function);
    }
}
void show(Node *node){
    if (node == NULL)
    {
        printf("NULL ");
    }else{
        printf("%d:%s:%s ", node->key, node->text, node->color);
        show(node->left);
        show(node->right);
    }
    
}
Node *createNode(int key, char *text){
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->text = (char *)malloc(strlen(text)+1);
    strcpy(node->text, text);
    node->height = 0;
    node->color = "black";
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
	free(node->text);
        free(node);
        freeTree(right);
        freeTree(left);
    }
}
