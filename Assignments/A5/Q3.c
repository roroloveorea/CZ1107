#include <stdio.h>
#include <stdlib.h>
#include <string.h>
 
#define SIZE 200 //The number digit limitation
 
typedef struct _btnode
{
   int item;
   struct _btnode *left;
   struct _btnode *right;
} BTNode; // You should not change the definition of BTNode
 
// since in there, we have no choice to declare the ExpType, the last four num of int is used to represent +-*/.
typedef struct _node
{
   BTNode *item;
   struct _node *next;
} StackNode;
 
typedef struct _stack
{
   int size;
   StackNode *head;
} Stack;
 
void deleteTree(BTNode **root);
 
void createExpTree(BTNode **root, char *prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);
 
void insertBTNode(BTNode **node, int value, int *placed);
void push(Stack *sPtr, BTNode *item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);
 
int char2int(char c);
 
char int2char(int value);
 
int ischar(int value);
int main()
{
   char prefix[SIZE];
   BTNode *root = NULL;
  
   gets(prefix);
 
   createExpTree(&root, prefix);
 
  
   printTree(root);
   printf("\n");
  
   printTreePostfix(root);
   printf("\n");
 
   printf("%.2f\n", computeTree(root));
   deleteTree(&root);
   return 0;
}
int char2int(char c)
{
   if (c == '+')
       return 0x7fffffff;
   if (c == '-')
       return 0x7ffffffe;
   if (c == '*')
       return 0x7ffffffd;
   if (c == '/')
       return 0x7ffffffc;
}
char int2char(int value)
{
   if (value == 0x7fffffff)
       return '+';
   if (value == 0x7ffffffe)
       return '-';
   if (value == 0x7ffffffd)
       return '*';
   if (value == 0x7ffffffc)
       return '/';
   return 0;
}
int ischar(int value)
{
   if (value >= 0x7ffffffc && value <= 0x7fffffff)
   {
       return 1;
   }
   return 0;
}
void createExpTree(BTNode **root, char *prefix)
{
  
   int l = strlen(prefix);
   int i = 0;
  
   int value = 0, flag = 1;
   int placed = 0;
   int *p = &placed;
   for (i = 0; i < l; i++)
   {
       if (prefix[i] == '+' || prefix[i] == '-' || prefix[i] == '*' || prefix[i] == '/')
       {
          
           if (prefix[i] == '-' && prefix[i + 1] >= '0' && prefix[i + 1] <= '9')
           {
             
               flag = -1;
             
               continue;
           }
 
           value = char2int(prefix[i]);
           placed = 0;
           insertBTNode(root, flag * value, p);
           flag = 1;
       }
       else if (prefix[i] == ' ')
       {
          
           if (i - 1 >= 0 && prefix[i - 1] == ' ')
           {
               continue;
           }
           if (!ischar(value))
           {
               placed = 0;
               insertBTNode(root, flag * value, p);
               flag = 1;
           }
           value = 0;
       }
       else
       {
         
           value = value * 10 + (prefix[i] - '0');
       }
   }
 
   placed = 0;
   insertBTNode(root, flag * value, p);
}
 
void insertBTNode(BTNode **node, int value, int *placed)
{
   if (*placed)
   {
       return;
   }
  
   if (*node == NULL)
   {
      
       BTNode *newnode = malloc(sizeof(BTNode));
      
       *node = newnode;
      
       newnode->item = value;
       newnode->left = NULL;
       newnode->right = NULL;
      
       return;
   }
   else
   {
       BTNode *temp = *node;
      
       if (temp->left == NULL && !(*placed))
       {
          
           BTNode *newnode = malloc(sizeof(BTNode));
           newnode->item = value;
           newnode->left = NULL;
           newnode->right = NULL;
           temp->left = newnode;
           *placed = 1;
          
           return;
       }
      
       if (ischar(temp->left->item))
       {
          
           insertBTNode(&(temp->left), value, placed);
          
           if (*placed)
               return;
       }
      
       if (temp->right == NULL && !(*placed))
       {
          
           BTNode *newnode = malloc(sizeof(BTNode));
           newnode->item = value;
           newnode->left = NULL;
           newnode->right = NULL;
           temp->right = newnode;
           *placed = 1;
         
           return;
       }
     
       if (ischar(temp->right->item))
       {
          
           insertBTNode(&(temp->right), value, placed);
           if (*placed)
               return;
       }
   }
   return;
}
void printTree(BTNode *node)
{
   //Write your code here
   if (node->left != NULL)
   {
       printTree(node->left);
   }
   if (ischar(node->item))
   {
       printf("%c ", int2char(node->item));
   }
   else
   {
       printf("%d ", node->item);
   }
 
   if (node->right != NULL)
   {
       printTree(node->right);
   }
}
 
void printTreePostfix(BTNode *node)
{
   //Write your code here
   if (node->left != NULL)
   {
       printTreePostfix(node->left);
   }
   if (node->right != NULL)
   {
       printTreePostfix(node->right);
   }
   if (ischar(node->item))
   {
       printf("%c ", int2char(node->item));
   }
   else
   {
       printf("%d ", node->item);
   }
}
 
double computeTree(BTNode *node)
{
  
   if (!ischar(node->item))
   {
       return 1.0 * node->item;
   }
  
   double l_v = computeTree(node->left);
   double r_v = computeTree(node->right);
   char op = int2char(node->item);
   double ans;
   if (op == '+')
   {
       ans = 1.0 * l_v + r_v;
   }
   else if (op == '-')
   {
       ans = 1.0 * l_v - r_v;
   }
   else if (op == '*')
   {
       ans = 1.0 * l_v * r_v;
   }
   else
   {
       ans = 1.0 * l_v / r_v;
   }
  
   node->item = (double)ans;
   return ans;
}
 
void push(Stack *sPtr, BTNode *item)
{
   StackNode *newNode;
   newNode = malloc(sizeof(StackNode));
   newNode->item = item;
   newNode->next = sPtr->head;
   sPtr->head = newNode;
   sPtr->size++;
}
 
int pop(Stack *sPtr)
{
   if (sPtr == NULL || sPtr->head == NULL)
   {
       return 0;
   }
   else
   {
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
   }
}
 
BTNode *peek(Stack s)
{
   return s.head->item;
}
 
int isEmptyStack(Stack s)
{
   if (s.size == 0)
       return 1;
   else
       return 0;
}
 
void deleteTree(BTNode **root)
{
   BTNode *temp;
   if (*root != NULL)
   {
       temp = (*root)->right;
       deleteTree(&((*root)->left));
       free(*root);
       *root = NULL;
       deleteTree(&temp);
   }
}


