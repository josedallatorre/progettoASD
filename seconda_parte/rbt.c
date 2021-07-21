#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rbt.h"
#include "times.h"
#include "times.c"
#include <time.h>
#include <math.h>
int main(int argc, char const *argv[])
{   
    //initialize the root
    //RBT *T = createRBT();
    //handleInput(T);
    //freeTree(T, T->root);
    computeTimes();
    return 0;
}
void computeTimes(){
    long R = getResolution();
    int A = NMIN;
    double B = exp((log(NMAX)-log(A))/99);
    long Tmin= R*(1/0.01+1);
    struct timespec start, end;
    long tTot[100]={0};
    long tMean[100]={0};
    for (int j = 0; j < 100; j++)
    {
        printf("inizio la %d-esima iterazione\n",j);
        int n = A * pow(B,j);
        clock_gettime(CLOCK_MONOTONIC,&start);     
        do{   
            RBT *T = createRBT();        
            for (int i = 1; i < n; i++)
            {
                
                int key = rand() / (RAND_MAX / n + 1);
                if (find2(T, T->root, key)==-1)
                {
                    Node *node = createNode(key, "");
                    rbtInsert(T, node);
                }
            }
            clock_gettime(CLOCK_MONOTONIC,&end);
            tTot[j] = getDiffTime(end, start);
            tMean[j] = tTot[j]/n;
            freeTree(T, T->root);
        }while(tMean[j]<Tmin);
        double s =0.00;
        for (int i = 1; i < 100; i++)
        {
            s = s + pow((tTot[i]-tMean[i]),2);
        }
        double D = sqrt(s/n);
        
        FILE *fd = fopen("timesRBT.txt","a");
        fprintf(fd, "n: %d tTot:%ld tMean:%ld D:%f\n", n,tTot[j], tMean[j], D);
        fclose(fd);
    }
}
int find2(RBT *T, Node *node, int key){
    while(node != T->leaf && key != node->key){
        if(key<node->key){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    if (node == T->leaf)
    {
        return -1;
    }else{
        return 0;
    }
    
}
void find(RBT *T, Node *node, int key){
    if(node == T->leaf){
        printf("key doesnt exit");
    }else{
        if (key == node->key){
            printf("\n%s", node->text);
        }
        else if (key>node->key)
        {
            find(T, node->right, key);
        }else{
            find(T, node->left, key);
        }
        
    }
}
void rbtInsert(RBT *T, Node *node){
    Node *y = T->leaf;
    Node *x = T->root;
    while(x != T->leaf){
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
    }
    else if(node->key < y->key){
	    y->left = node;
    }
    else{
	    y->right = node;
    }
	    node->left = T->leaf;
	    node->right = T->leaf;
	    node->color = red;
	    rbtInsertFixup(T, node);
}
void rbtInsertFixup(RBT *T, Node *node){
    while(node->parent->color == red){
	    if(node->parent == node->parent->parent->left){
	        Node *y = node->parent->parent->right;
	        if(y->color == red){ //case 1 
		        node->parent->color = black;
		        y->color = black;
		        node->parent->parent->color = red;
		        node = node->parent->parent;
            }else{
                if(node == node->parent->right){//case 2
		            node = node->parent;
		            leftRotate(T, node);
                }
	            node->parent->color = black;//case 3
	            node->parent->parent->color = red;
	            rightRotate(T, node->parent->parent);
            }
	    }
        else{
	    Node *y = node->parent->parent->left;
	    if(y->color == red){ //case 1 
		    node->parent->color = black;
		    y->color = black;
		    node->parent->parent->color = red;
		    node = node->parent->parent;
        }
        else{
	        if(node ==node->parent->left){//case 2
		        node = node->parent;
		        rightRotate(T, node);
            }
	        node->parent->color = black;//case 3
	        node->parent->parent->color = red;
	        leftRotate(T, node->parent->parent);
        }
	}
    }
    T->root->color = black;
}

void leftRotate(RBT *T, Node *x){
    Node *y = x->right;
    x->right = y-> left;//turn y subtree into x right subtree
    if (y->left != T->leaf){
	    y->left->parent = x;
    }
    y->parent = x->parent;
    if(x->parent == T->leaf){
	    T->root = y;
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
void rightRotate(RBT *T, Node *x){
    Node *y = x->left;
    x->left = y->right; //turn y subtree into x left subtree
    if(y->right !=T->leaf){
	    y->right->parent = x;
    }
    y->parent = x->parent;
    if(x->parent ==T->leaf){
	    T->root = y;
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


void handleInput(RBT *T){
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
            rbtInsert(T, node);
        }
        if ((strcmp(function, "show"))==0)
        {
            show(T, T->root);
        }
         if ((strcmp(function, "find"))==0)
        {
            scanf("%d", &key);
            find(T, T->root, key);
        }
        scanf("%s", function);
    }
}
void show(RBT *T, Node *node){
    if (node == NULL || node == T->leaf)
    {
	    printf("NULL ");
    }else{
	    const char *c;
	    if (node->color == red)
	    {
		    c = "red";
	    }
	    else
	    {
		    c = "black";
	    }
	    printf("%d:%s:%s ", node->key, node->text, c);
	    show(T,node->left);
	    show(T,node->right);
    }
    
}
RBT *createRBT(){
    struct RBT *T = (RBT *)malloc(sizeof(struct RBT));
    struct Node *leaf = (Node *)malloc(sizeof(struct Node));
    //leaf->key=0;
    leaf->text="";
    leaf->color = black;
    leaf->parent= leaf->right = leaf->left = NULL;
    T->leaf = leaf;
    T->root = T->leaf; 
    return T;
}
Node *createNode(int key, char *text){
    struct Node *node = (Node *)malloc(sizeof(struct Node));
    node->key = key;
    node->text = (char *)malloc(strlen(text)+1);
    strcpy(node->text, text);
    node->color = black;
    node->left= NULL;
    node->right= NULL;
    node->parent = NULL;
    return node;
}
void freeTree(RBT *T, Node *node){
    if (node == T->leaf)
    {
        return;
    }else{
        Node *right = node->right;
        Node *left = node->left;
	    free(node->text);
        free(node);
        freeTree(T,right);
        freeTree(T, left);
    }
}
