#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

struct Stack {
    int top;
    char items[MAX];
};

struct Stack* createStack() {
    struct Stack* stack = (struct Stack*)malloc(sizeof(struct Stack));
    stack->top = -1;
    return stack;
}

int isEmpty(struct Stack* stack) {
    return stack->top == -1;
}

int isFull(struct Stack* stack) {
    return stack->top == MAX - 1;
}

void push(struct Stack* stack, char value) {
    if (!isFull(stack)) {
        stack->items[++stack->top] = value;
    }
}

char pop(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top--];
    }
    return -1;
}

char peek(struct Stack* stack) {
    if (!isEmpty(stack)) {
        return stack->items[stack->top];
    }
    return -1;
}

int precedence(char c) {
    if (c == '+' || c == '-') {
        return 1;
    } else if (c == '*' || c == '/') {
        return 2;
    } else if (c == '^') {
        return 3;
    }
    return -1;
}

void infixToPostfix(char* infix, char* postfix) {
    struct Stack* stack = createStack();
    int k = 0;
    
    for (int i = 0; infix[i] != '\0'; i++) {
        char current = infix[i];
        
        if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z') || (current >= '0' && current <= '9')) {
            postfix[k++] = current;
        } else if (current == '(') {
            push(stack, current);
        } else if (current == ')') {
            while (!isEmpty(stack) && peek(stack) != '(') {
                postfix[k++] = pop(stack);
            }
            pop(stack);
        } else {
            while (!isEmpty(stack) && precedence(peek(stack)) >= precedence(current)) {
                postfix[k++] = pop(stack);
            }
            push(stack, current);
        }
    }
    
    while (!isEmpty(stack)) {
        postfix[k++] = pop(stack);
    }
    postfix[k] = '\0';
}

void postfixToInfix(char* postfix, char* infix) {
    struct Stack* stack = createStack();
    char temp[2];
    
    for (int i = 0; postfix[i] != '\0'; i++) {
        char current = postfix[i];
        
        if ((current >= 'a' && current <= 'z') || (current >= 'A' && current <= 'Z') || (current >= '0' && current <= '9')) {
            temp[0] = current;
            temp[1] = '\0';
            push(stack, temp[0]);
        } else {
            char op2 = pop(stack);
            char op1 = pop(stack);
            infix[0] = '(';
            infix[1] = op1;
            infix[2] = current;
            infix[3] = op2;
            infix[4] = ')';
            infix[5] = '\0';
            push(stack, infix[0]);
        }
    }
}

int main() {
    char infix[MAX], postfix[MAX], infixFromPostfix[MAX];
    printf("Enter an infix expression: ");
    scanf("%s", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);
    
    postfixToInfix(postfix, infixFromPostfix);
    printf("Infix from Postfix: %s\n", infixFromPostfix);
    
    return 0;
}
