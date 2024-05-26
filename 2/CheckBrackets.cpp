#include <cstring>
#include <iostream>

#define MAXLEN 120

typedef char SElemType;

struct Stack {
    SElemType base[MAXLEN];
    int top;
};

void InitStack(Stack &s) {
    s.top = 0;
}

SElemType Pop(Stack &s) {
    if (s.top <= 0) {
        exit(EXIT_FAILURE);  // 栈空
    } else {
        return s.base[--s.top];
    }
}

void Push(Stack &s, SElemType data) {
    if (s.top >= MAXLEN - 1) {
        exit(EXIT_FAILURE);  // 栈满
    } else {
        s.base[s.top++] = data;
    }
}

bool StackEmpty(Stack s) {
    return s.top == 0;
}

bool CheckBrackets(char *expr) {
    Stack s;
    InitStack(s);
    for (int i = 0; expr[i] != '\0'; ++i) {
        if (expr[i] == '(' || expr[i] == '[' || expr[i] == '{') {
            Push(s, expr[i]);
        } else if (expr[i] == ')' || expr[i] == ']' || expr[i] == '}') {
            if (StackEmpty(s)) {
                return false;
            }
            char c = Pop(s);
            switch (expr[i]) {
                case ')':
                    if (c != '(') {
                        return false;
                    }
                    break;
                case ']':
                    if (c != '[') {
                        return false;
                    }
                    break;
                case '}':
                    if (c != '{') {
                        return false;
                    }
                    break;
            }
        }
    }
    return StackEmpty(s);
}

int main() {
    char input[MAXLEN];
    do {
        fgets(input, MAXLEN, stdin);
        if (strlen(input) == 1 && input[0] == '\n') break;
        if (CheckBrackets(input)) {
            printf("yes\n");
        } else {
            printf("no\n");
        }
    } while (true);
    return 0;
}