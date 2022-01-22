#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);



typedef struct _listnode
{
  int item ;
  enum ExpType type ;
  struct _listnode * next ;
} ListNode ;


typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExpLL);
char strrev(char* infix);
_Bool isOperator(char c);
int getPrecedence(char c);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
  //Write your code here

  char r[SIZE];
  char t[SIZE];
  char tempstr[SIZE];
  char symbol;

  int num;

    Stack s;
    s.head = NULL;
    s.size = 0;


  int i=0,j=0,u=0,h=0;
tempstr[0]='\0';
  //-----------------------------------------------------------------------------------------------------------------

strrev(infix);
//while(infix[i]!='\0'){printf("%c",infix[i]); i++;}
i=0;
printf("\n");
//infix is being reversed.
/*while (infix[h] != '\0'){ // Complement all brackets
        if (infix[h] == '(')
            infix[h] = ')';
        else if (infix[h] == ')')
            infix[h] = '(';
        h++;
    }*/
//while(infix[i]!='\0'){printf("%c",infix[i]); i++;}
//----------------------------------------------------------------------------------------------------------------------
i=0;
j=0;
//begin=0; end=0; count = 0;
while(infix[i]!='\0')
{   //printf("processing the current infix: %c\n",infix[i]);
    if(!isOperator(infix[i]))
    {
        tempstr[j]=infix[i];
        j++;


    } // until here is fine
    else
    {
      //printf("this is an operator %c\n",infix[i]);
      if(tempstr[0]!='\0')
        {
          strrev(tempstr);
          //printf("insert tempstr into LL: %d\n",atoi(tempstr));
          insertNode(inExpLL,atoi(tempstr),OPERAND);
          for(u=0;u<SIZE;u++){tempstr[u] = '\0';}
          j=0;
        }

        num=getPrecedence(infix[i]);
        //printf("this is the precedence of infix[i]: %d\n", num);
        if(num==2)
        {
           while(peek(s)!=')')
           {
             insertNode(inExpLL,peek(s),OPT);
             pop(&s);
             if(isEmptyStack(s)){break;}
           }
           if(!isEmptyStack(s)){pop(&s);}

        }
        if(num==1)
        {
            push(&s,infix[i]);
        }
        if(num==4||num==3)
        {  if(isEmptyStack(s))
               {
                   //printf("push the operator into the stack coz its empty\n");
                   push(&s,infix[i]);
                   i++;
                   continue;
               }
           if(num>=getPrecedence(peek(s)))
           {
               push(&s,infix[i]);
           }
           else
           {
               while(num<getPrecedence(peek(s)))
               {
                   //printf("the top of the stack now is %c\n",peek(s));
                   insertNode(inExpLL,peek(s),OPT);
                   pop(&s);
                   if(isEmptyStack(s)){break;}
               }

                   push(&s,infix[i]);

           }
        }

    }

//-----------------------------------------------------------------------------------------
i++; // don't touch this
}
//after while loop is done
//---------------------------------------------------------------
if(tempstr[0]!='\0')
        {
          strrev(tempstr);
          //printf("insert tempstr into LL %d\n",atoi(tempstr));
          insertNode(inExpLL,atoi(tempstr),OPERAND);
          for(u=0;u<SIZE;u++){tempstr[u] = '\0';}
          j=0;
        }
while(!isEmptyStack(s))
{
    //printf("the stack is not emptied after the for loop");
    insertNode(inExpLL,peek(s),OPT);
    pop(&s);
    //if(isEmptyStack(s)){break;}
}
//------------------------------------------------------------------------------------------------------------

}
_Bool isOperator(char c){
    return (c == '*' || c == '/' || c == '+' || c == '-'||c == '('|| c == ')');
}

int getPrecedence(char c){
    if(c == '(')
       return 2;
    else if(c == ')')
        return 1;
    else if (c == '*' || c == '/')
        return 4;
    else if (c == '+' || c == '-')
        return 3;
    return 0;
}
void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

char strrev(char* infix)
{ int begin, end, count = 0;
int j=0;
char r[SIZE];
    while (infix[count] != '\0')
      count++;

   end = count-1;

   for (begin = 0; begin < count; begin++) {
      r[begin] = infix[end];
      end--;
   }
   printf("\n");
   for(j=0; j<count; j++)
   {
     infix[j]  = r[j];

   }
   return infix;
}

