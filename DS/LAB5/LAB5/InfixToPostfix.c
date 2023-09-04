#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define MAX_SIZE 100

int isOperator(char ch){
    return (ch=='+' || ch=='-' || ch=='*' || ch=='/' || ch=='/');
}
int precedence(char ch){
    if(ch=='+' || ch=='-'){
        return 1;
    }
    else if(ch=='*' || ch=='/'){
        return 2;
    }
    else if(ch=='^'){
        return 3;
    }
    else{
        return 0;
    }
}

struct Stack{
    char items[MAX_SIZE];
    int top;

};

void initialize(struct Stack* stack){
    stack->top=-1;
}

//Stack operations
void push(struct Stack* stack, char item){
    if(stack->top==MAX_SIZE-1){
        printf("OVERFLOW\n");
        exit(1);
    }
    else{
        stack->items[++stack->top]=item;
    }
}

char  pop(struct Stack* stack){
    if(stack->top==-1){
        printf("UNDERFLOW\n");
        exit(1);
        
    }
    else{
        return stack->items[stack->top--];
    }
}

void InfixToPostfix(char* infix, char* postfix){
    struct Stack stack;
    initialize(&stack);
    int j=0;
    
    for(int i=0;infix[i]!='\0'; i++){
        char ch=infix[i];

        if(ch=='('){
            while(stack.items[stack.top]!=')' && stack.top!=-1){
                postfix[j++]=pop(&stack);
            }
            pop(&stack);
        }

        else if(ch==')'){
            push(&stack, ch);
        }
        
        else if(isOperator(ch)){
            while((precedence(stack.items[stack.top])>=precedence(ch) && stack.top!=-1)){
            postfix[j++]=pop(&stack);
        }
        push(&stack, ch);
        }

        else{
            postfix[j++]=ch;
        }
    }

    while(stack.top!=-1){
        postfix[j++]=pop(&stack);
    }

}

int main(){
    char infix[MAX_SIZE], postfix[MAX_SIZE];

    printf("ENTER INFIX EXPRESSION: ");
    scanf("%s", infix);

    InfixToPostfix(infix, postfix);
    printf("POSTFiX EXPRESSION :%s\n ", postfix);
    return 0;
}
