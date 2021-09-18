#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"
#include "times.h"
#include "times.c"
#include <time.h>
#include <math.h>
int main(int argc, char const *argv[])
{   
    //initialize the root
    //BST *T = createBST();
    //handleInput(T);

    computeTimes();
    //freeTree(T, T->root);
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
            BST *T = createBST();        
            for (int i = 1; i < n; i++)
            {
                
                int key = rand() / (RAND_MAX / n + 1);
                if (find2(T, T->root, key)==-1)
                {
                    Node *node = createNode(key, "");
                    insertNode(T, node);
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
        
        FILE *fd = fopen("timesBST.txt","a");
        fprintf(fd, "n: %d tTot:%ld tMean:%ld D:%f\n", n,tTot[j], tMean[j], D);
        fclose(fd);
    }
}


int find2(BST *T, Node *node, int key){
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
char *find(BST *T, Node *node, int key){
    while(node != T->leaf && key != node->key){
        if(key<node->key){
            node = node->left;
        }else{
            node = node->right;
        }
    }
    return node->text;
}

void handleInput(BST *T){
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
void insertNode(BST *T, Node *node){
    node->left= T->leaf;
    node->right=T->leaf;
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
}

void show(BST *T,Node *node){
    if (node == T->leaf)
    {
        printf("NULL ");
    }else{
        printf("%d:%s:%d ", node->key, node->text, node->height);
        show(T,node->left);
        show(T,node->right);
    }
}

BST *createBST() {
    struct BST *T = (BST *)malloc(sizeof(struct BST));
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
   
    node->left= NULL;
    node->right= NULL;
    node->parent = NULL;
    return node;
}

void freeTree(BST *T, Node *node){
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
