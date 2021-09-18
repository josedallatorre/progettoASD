#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include "times.h"
//#include "times.c"
//#include <time.h>

struct node
{
  int key;
  char *s;
  struct node *left, *right;
};


struct node *newNode (int data, char *v)
{
  struct node *n = (struct node *) malloc (sizeof (struct node));
  n->s = v;			
  n->key = data;
  n->left = n->right = NULL;
  return n;
}


void show(struct node *root)
{
  if (root == NULL)
    { 
      printf ("NULL ");
    }
  else
    {
      printf ("%d:", root->key);	
      for (int i = 0; root->s[i] != '\0'; i++)
	     {
	         printf ("%c", root->s[i]);
	     }
      printf (" ");
      
      show(root->left);
      show(root->right);
    }
}


struct node *insertNode (struct node *node, int key, char *v)
{
   
  if (node == NULL){
    return newNode (key, v);
  }
  if (key < node->key){
    node->left = insertNode(node->left, key, v);
  }
  else if (key > node->key){
    node->right = insertNode(node->right, key, v);
  }


  return node;
}

void destroy(struct node *root){
    if(root == NULL){
        return;
    }else{
    destroy(root->right);
    destroy(root->left);
    free(root);
    }
}

struct node* find(struct node *root, int k)
{
    if(root==NULL || root->key==k){ 
        return root;
    }
    else if(k>root->key){ 
        return find(root->right, k);
    }
    else{ 
        return find(root->left, k);
    }
}

int main ()
{
  char op[20];  
  
   
   
  char v[100][100];
  int i = 0;
  int k;
  struct node *root = NULL;
  //printf ("Operazione che si vuole eseguire: \n");
  scanf("%s", op);  
 
  while (strcmp (op, "exit") != 0)
    {
      
     
      if(strcmp(op, "insert")==0){
          scanf("%i", &k);
          scanf("%s", v[i]);   
          root=insertNode(root, k, v[i]);
	      
	
      }else if(strcmp(op, "find")==0){
           scanf("%i", &k);
           printf("%s \n",find(root,k)->s); 
      }else{
           show(root);
           printf("\n");
      }
      
      scanf ("%s", op);
      i++;
    }
  destroy(root); 
  return 0;
}

/*
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
                    Node *node = newNode(key, "");
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

BST *createBST() {
    struct BST *T = (BST *)malloc(sizeof(struct BST));
    struct Node *leaf = (Node *)malloc(sizeof(struct Node));
    leaf->parent= leaf->right = leaf->left = NULL;
    T->leaf = leaf;
    T->root = T->leaf; 
    return T;
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
*/
