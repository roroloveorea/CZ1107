#include <stdio.h>
#include <stdlib.h>

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
char *strrev(char *str);

void in2Pre(char*, char*);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

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

char *strrev(char *str){
    char c, *front, *back;

    if(!str || !*str)
        return str;
    for (front = str, back = str + strlen(str)-1; front < back; front++, back--){
        c = *front, *front = *back, *back = c;
    }
    return str;
}

void in2Pre(char* infix, char* prefix)
{

    strrev(infix);
    char *c_char = infix;
    char *p_char = prefix;
    char top_char;

    Stack s;
    s.head = NULL;
    s.size = 0;

    while(*(c_char) != '\0'){
        //printf("Processing %c \n", *(c_char));
        if (*(c_char) == ')'){
            push(&s, *(c_char));
            //printf("Pushed %c to stack \n", *(c_char));
        }

        else if(*(c_char) == '('){
            if (!isEmptyStack(s)){
                top_char = peek(s);
                while(top_char != ')'){  // Move all operators before ')' to output
                    pop(&s);
                    *(p_char) = top_char;
                    p_char++;
                    //printf("Moved %c from stack to output\n", top_char);
                    if(isEmptyStack(s))
                        break; // In case there is no ')'
                    top_char = peek(s);
                }
                pop(&s); // Pop out ')'
            }
        }

        else if (isalnum(*(c_char))){ // Process Operands
            *(p_char) = *(c_char);
            p_char++; // Insert c_char to output
            //printf("Added %c to output \n", *(c_char));
        }

        else if (isOperator(*(c_char))){
            if (isEmptyStack(s)){
                push(&s, *(c_char)); // Nothing to compare, just push
            }
            else{
                top_char = peek(s);

                if (getPrecedence(*(c_char)) >= getPrecedence(top_char)){
                    push(&s, *(c_char)); // c_char has greater precedence than top_char
                }
                else{
                    while(getPrecedence(*(c_char)) < getPrecedence(top_char)){ // Move any operator > precedence to c_char
                        pop(&s);
                        *(p_char) = top_char;
                        p_char++;
                        //printf("Moved %c from stack to output\n", top_char);
                        if(isEmptyStack(s)) // Stop if stack is empty
                            break;
                        top_char = peek(s); // Check next operator
                    }
                    push(&s, *(c_char)); // Finally, add c_char to stack
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

    strrev(prefix);

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
