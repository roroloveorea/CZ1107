#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);

char *strrev(char *str);
_Bool isOperator(char *c);
int getPrecedence(char *c);

void in2PreLL(char* infix, LinkedList *inExpLL);

void printExpLL(LinkedList inExp);

int main()
{
    char infix[SIZE];

    //printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

_Bool isOperator(char *c){
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int getPrecedence(char *c){
    if (c == '-' || c == '+')
        return 1;
    else if (c == '*' || c == '/')
        return 2;
    else if (c == '^')
        return 3;
    return 0;
}

char *strrev(char *str){
    char c, *front, *back;

    if(!str || !*str)
        return str;
    for (front = str, back = str + strlen(str)-1; front < back; front++, back--){
        c = *front, *front = *back, *back = c;
    }
    return str;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    char *c_char = infix;
    char temp[SIZE], top_char;
    int temp_int, len = 0;
    StackNode *cur;

    Stack s;
    s.head = NULL;
    s.size = 0;

    strrev(infix); // Reverse infix to read Right to Left


    while (*(c_char) != '\0'){ // Complement all brackets
        if (*(c_char) == '(')
            *(c_char) = ')';
        else if (*(c_char) == ')')
            *(c_char) = '(';
        c_char++;
    }
    printf("Reverse infix is %s\n", infix);
    c_char = infix; // Move pointer back to front

    while (*(c_char) != '\0'){
        if (isdigit(*(c_char))){ // If current char is a digit, add it to temp
            temp[len] = *(c_char);
            len++;

            if (!isdigit(*(c_char+1)) || *(c_char+1) == '\0'){ // Next char is not a digit or is end of string
                // Process the operand
                temp[len] = '\0'; // Close temp string
                strrev(temp);
                sscanf(temp, "%d", &temp_int); // Convert temp to int
                printf("Processing %d \n", temp_int);
                insertNode(inExpLL, temp_int, 1); // Insert operand into inExpLL
                printf("Inserted %d to output\n", temp_int);
                len = 0; // Reset temp
            }
        }

        // Operator Found
        else {
            printf("Processing %c \n", *(c_char));
            if (*(c_char) == '('){
                // Process open parentheses
                // Nothing much here, just push ( into stack
                push(&s, *(c_char));
                printf("Pushed %c to stack\n", *(c_char));
            }

            else if (*(c_char) == ')'){
                // Process close parentheses
                // Pop and move all items in stack to output until open parenthesis encountered
                if(!isEmptyStack(s)){ // Ignore if stack is already empty?
                    top_char = peek(s);
                    while(top_char != '('){
                        pop(&s);
                        insertNode(inExpLL, (int) top_char, 0);
                        printf("Moved %c from stack to output\n", top_char);

                        if (isEmptyStack(s)) // In the case there is no open Parentheses?
                            break;

                        top_char = peek(s); // Check next operator
                    }
                    pop(&s); // Pop out the open parentheses
                }
            }

            else {
                if (isOperator(*(c_char))){ // Check if c_char is +-*/^
                    // Process Operator
                    // Check Precedence
                    if(isEmptyStack(s))
                        push(&s, *(c_char)); // Nothing to compare, just add to stack
                    else{
                        top_char = peek(s);
                        while (getPrecedence(top_char) > getPrecedence(*(c_char))){
                            pop(&s);
                            insertNode(inExpLL, (int) top_char, 0); // Move all operators with higher precedence to output
                            printf("Moved %c from stack to output\n", top_char);
                            if (isEmptyStack(s))
                                break;
                            top_char = peek(s); // Check next operator
                        }
                        // Finally, add c_char into stack
                        push(&s, *(c_char));
                        printf("Pushed %c to stack \n", *(c_char));
                    }
                }
            }
        }
        c_char++;
    }

    //Finally, move any remaining operators to ExpLL
    while(!isEmptyStack(s)){
        top_char = peek(s);
        pop(&s);
        insertNode(inExpLL, top_char, 0); // Move operator to ExpLL
        printf("Moved %c from stack to output\n", top_char);
    }
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
