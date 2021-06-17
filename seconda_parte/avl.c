#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "avl.h"
int main(int argc, char const *argv[])
{   
    //initialize the root
    Node *root = createNode(0, "NULL");
    handleInput(root);
    freeTree(root);
    return 0;
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
            root = insertNode(root, node);
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
struct Node *insertNode(struct Node *root, struct Node *node){
    struct Node *y = NULL;
    struct Node *x = root;
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
        {
            x = x->left;
        }else{
            x = x->right;
        }
    }
    node->parent = y;
    if ((strcmp(y->text, "NULL"))==0)
    {
        root = node;
    }
    if (node->key < y->key)
    {
        y->left = node;
    }
    else{
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
    struct Node *node = malloc(sizeof(struct Node));
    node->key = key;
    node->text = text;
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
        freeTree(right);
        freeTree(left);
    }
}