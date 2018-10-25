#include <stdio.h>

typedef struct Stack {
    int data[20];
    int top;
} Stack;

void Init(Stack* s) {
    s->top = 0;
}

int push(Stack *s, int v) {
    if (s == NULL) {
        return 0;
    }

    if (s->top > 20) {
        return 0;
    }

    s->data[s->top++] = v;
    return 1;
}

int pop(Stack *s, int *v) {
    if (s == NULL) {
        return 0;
    }

    if (s->top == 0)
        return 0;

    *v = s->data[--s->top];
    return 1;
}

int main() {
    Stack s;
    Init(&s);
    for(int i=0; i<5; ++i) {
        push(&s, i);
    }

    int v;
    for(int i=0; i<5; ++i) {
        pop(&s, &v);
        printf("%d ", v);
    }
    printf("\n");
}
