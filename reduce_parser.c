#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define MAX_SIZE 100

char stack[MAX_SIZE];
int top = -1;

void push(char c) {
    if (top == MAX_SIZE - 1) {
        printf("Stack overflow\n");
        exit(1);
    }
    stack[++top] = c;
}

char pop() {
    if (top == -1) {
        printf("Stack underflow\n");
        exit(1);
    }
    return stack[top--];
}

int precedence(char op) {
    switch (op) {
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
            return 2;
        default:
            return 0;
    }
}

int is_operator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int is_operand(char c) {
    return isdigit(c);
}

int evaluate(char op, int a, int b) {
    switch (op) {
        case '+':
            return a + b;
        case '-':
            return a - b;
        case '*':
            return a * b;
        case '/':
            return a / b;
        default:
            return 0;
    }
}

int main() {
    char expr[MAX_SIZE];
    printf("Enter the expression to evaluate: ");
    fgets(expr, MAX_SIZE, stdin);

    int i = 0;
    while (expr[i] != '\0') {
        if (is_operand(expr[i])) {
            int operand = expr[i] - '0';
            i++;
            while (is_operand(expr[i])) {
                operand = operand * 10 + (expr[i] - '0');
                i++;
            }
            push(operand);
        } else if (is_operator(expr[i])) {
            while (top != -1 && stack[top] != '(' && precedence(stack[top]) >= precedence(expr[i])) {
                char op = pop();
                int b = pop();
                int a = pop();
                int result = evaluate(op, a, b);
                push(result);
            }
            push(expr[i]);
            i++;
        } else if (expr[i] == '(') {
            push(expr[i]);
            i++;
        } else if (expr[i] == ')') {
            while (stack[top] != '(') {
                char op = pop();
                int b = pop();
                int a = pop();
                int result = evaluate(op, a, b);
                push(result);
            }
            pop(); // pop the '('
            i++;
        } else {
            i++;
        }
    }

    while (top != -1) {
        char op = pop();
        int b = pop();
        int a = pop();
        int result = evaluate(op, a, b);
        push(result);
    }

    printf("Result: %d\n", stack[0]);

    return 0;
}
