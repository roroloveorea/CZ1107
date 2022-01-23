#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

_Bool isOperator(char c);
double calcExp(char c, double l_operand, double r_operand);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    gets(postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}

_Bool isOperator(char c){
    return (c == '*' || c == '/' || c == '+' || c == '-');
}

double calcExp(char c, double l_operand, double r_operand){
    switch(c){
        case '*':
            return l_operand * r_operand;
        case '/':
            return l_operand / r_operand;
        case '+':
            return l_operand + r_operand;
        case '-':
            return l_operand - r_operand;
        default:
            return -1;
    }
}

double exePostfix(char* postfix)
{
    Stack s;
    s.head = NULL;
    s.size = 0;

    double l_operand, r_operand, temp;
    char *c_char = postfix;
    char c_temp;

    char *temp_char;

    _Bool valid = 1;

    while(*(c_char) != '\0'){
        if(isdigit(*(c_char))){
            c_temp = *(c_char);
            push(&s, strtod(&c_temp, NULL));
        }
        else if(isOperator(*(c_char))){
            if (isEmptyStack(s)){ // Invalid Expression
                valid = 0;
                break;
            }
            // Pop out top as r_operand
            r_operand = peek(s);
            pop(&s);

            if (isEmptyStack(s)){ // Invalid Expression
                valid = 0;
                break;
            }

            // Pop out top as r_operand
            l_operand = peek(s);
            pop(&s);

            temp = calcExp(*(c_char), l_operand, r_operand); // Calculate the sub Expression
            //printf("Evaluating %lf %c %lf = %lf \n", l_operand, *(c_char), r_operand, temp);

            //printf("pushed %lf to stack\n", temp);
            push(&s, temp);
        }

        c_char++;
    }

    if (valid == 1 && s.size == 1)
        return peek(s); // There should only be one Node left if expression is valid
    else
        return -99999; // Invalid expression
}

void push(Stack *sPtr, double item){
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
