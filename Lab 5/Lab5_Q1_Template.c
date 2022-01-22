#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 80 //The limit of expression length

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

_Bool isOperator(char c);
int getPrecedence(char c);

void in2Post(char*, char*);

int main()
{
    char infix[SIZE];
    char postfix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Post(infix,postfix);
    printf("The postfix expression is \n");
    printf("%s\n",postfix);
    return 0;
}

_Bool isOperator(char c){
    return (c == '*' || c == '/' || c == '+' || c == '-');
}

int getPrecedence(char c){
    if (c == '*' || c == '/')
        return 2;
    else if (c == '+' || c == '-')
        return 1;
    return 0;
}

void in2Post(char* infix, char* postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    char top_char;
    char *c_char = infix;
    char *p_char = postfix;

    while (*(c_char) != '\0'){
        //printf("Processing %c \n", *(c_char));
        if (*(c_char) == '('){
            push(&s, *(c_char));
            //printf("Pushed %c to stack \n", *(c_char));
        }

        else if (*(c_char) == ')'){
            if(!isEmptyStack(s)){
                top_char = peek(s);
                while (top_char != '('){ // Move all operators before '(' to output
                    *(p_char) = top_char;
                    p_char++;
                    pop(&s);
                    //printf("Moved %c from stack to output\n", top_char);
                    if(isEmptyStack(s))
                        break; // In case there's no '('
                    top_char = peek(s); // Process next operator
                }
                pop(&s); // Pop out '('
            }
        }

        else if (isalnum(*(c_char))){ // Process Operands
            *(p_char) = *(c_char);
            p_char++; // Insert c_char to output
            //printf("Added %c to output \n", *(c_char));
        }

        else if(isOperator(*(c_char))){ // Process Operators
            if(isEmptyStack(s)) // Nothing to compare, just push
                push(&s, *(c_char));
            else{
                top_char = peek(s);
                if(getPrecedence(*(c_char)) > getPrecedence(top_char)){ // c_char has greater precedence than top_char
                    push(&s, *(c_char));
                    //printf("Pushed %c to stack \n", *(c_char));
                }
                else{ // c_char has less precedence than top_char
                    while(getPrecedence(*(c_char)) <= getPrecedence(top_char)){ // Move any operator >= precedence to c_char
                        *(p_char) = top_char;
                        p_char++;
                        pop(&s);
                        //printf("Moved %c from stack to output\n", top_char);
                        if(isEmptyStack(s)) // Stop if stack is empty
                            break;
                        top_char = peek(s); // Check next operator in stack
                    }
                    push(&s, *(c_char)); // Finally, add c_char to stack
                    //printf("Pushed %c to stack \n", *(c_char));
                }
            }
        }
        c_char++;
    }

    while(!isEmptyStack(s)){ // Finally, remove any remaining operators from stack to output
        top_char = peek(s);
        pop(&s);
        *(p_char) = top_char;
        p_char++;
    }

    p_char = '\0';
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
