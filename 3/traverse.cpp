#include <cstdio>
#include <cstdlib>
using namespace std;

typedef char TElemType;

typedef struct BiTNode *BiTree;

struct BiTNode {
    TElemType Data;
    BiTree Left, Right;
    int flag;
};

void *SafeMalloc(unsigned long size) {
    void *p = malloc(size);
    if (!p) exit(EXIT_FAILURE);
    return p;
}

void CreateBiTree(BiTree &T) {
    char ch;
    scanf("%c", &ch);
    if (ch == '.') {
        T = NULL;
    } else {
        T = (BiTree)SafeMalloc(sizeof(BiTNode));
        T->Data = ch;
        CreateBiTree(T->Left);
        CreateBiTree(T->Right);
    }
}

void InorderTraversal(BiTree T) {
    if (!T) return;
    InorderTraversal(T->Left);
    printf(" %c", T->Data);
    InorderTraversal(T->Right);
}

void PreorderTraversal(BiTree T) {
    if (!T) return;
    printf(" %c", T->Data);
    PreorderTraversal(T->Left);
    PreorderTraversal(T->Right);
}

void PostorderTraversal(BiTree T) {
    if (!T) return;
    PostorderTraversal(T->Left);
    PostorderTraversal(T->Right);
    printf(" %c", T->Data);
}

typedef BiTNode *SElemType;
typedef struct SNode *PSNode, *Stack;
struct SNode {
    SElemType Data;
    PSNode Next;
};

Stack CreateStack() {
    Stack a = (Stack)SafeMalloc(sizeof(SNode));
    a->Next = NULL;
    return a;
}

bool IsEmpty(Stack S) {
    return S->Next == NULL;
}

SElemType Pop(Stack S) {
    if (S->Next == NULL) exit(EXIT_FAILURE);
    PSNode n = S->Next;
    SElemType d = n->Data;
    S->Next = n->Next;
    free(n);
    return d;
}

SElemType Peek(Stack S) {
    return S->Next->Data;
}

void Push(Stack S, SElemType p) {
    PSNode n = (PSNode)SafeMalloc(sizeof(struct SNode));
    n->Data = p;
    n->Next = S->Next;
    S->Next = n;
}

void InorderTraversalNonRecursive(BiTree T) {
    Stack s = CreateStack();
    Push(s, T);
    while (!IsEmpty(s)) {
        BiTree t;
        while ((t = Peek(s))) {
            Push(s, t->Left);
        }
        Pop(s);
        if (!IsEmpty(s)) {
            t = Pop(s);
            printf(" %c", t->Data);
            Push(s, t->Right);
        }
    }
    free(s);
}

void PreorderTraversalNonRecursive(BiTree T) {
    Stack s = CreateStack();
    Push(s, T);
    while (!IsEmpty(s)) {
        BiTree t = Pop(s);
        if (!t) continue;
        printf(" %c", t->Data);
        Push(s, t->Right);
        Push(s, t->Left);
    }
    free(s);
}

void PostorderTraversalNonRecursive(BiTree T) {
    Stack s = CreateStack();
    if (!T) return;
    T->flag = 0;
    Push(s, T);
    while (!IsEmpty(s)) {
        BiTree t = Pop(s);
        if (!t) continue;
        switch (t->flag) {
            case 0:
                t->flag = 1;
                Push(s, t);
                if (t->Left) {
                    t->Left->flag = 0;
                    Push(s, t->Left);
                }
                break;
            case 1:
                t->flag = 2;
                Push(s, t);
                if (t->Right) {
                    t->Right->flag = 0;
                    Push(s, t->Right);
                }
                break;
            case 2:
                printf(" %c", t->Data);
                break;
        }
    }
    free(s);
}

void DeleteTree(BiTree t) {
    if (!t) return;
    DeleteTree(t->Left);
    DeleteTree(t->Right);
    free(t);
}

int main() {
    BiTree t;
    CreateBiTree(t);
    printf("Preorder:");
    PreorderTraversal(t);
    printf("\nPreorder non recursive:");
    PreorderTraversalNonRecursive(t);
    printf("\nInorder:");
    InorderTraversal(t);
    printf("\nInorder non recursive:");
    InorderTraversalNonRecursive(t);
    printf("\nPostorder:");
    PostorderTraversal(t);
    printf("\nPostorder non recursive:");
    PostorderTraversalNonRecursive(t);
    printf("\n");
    DeleteTree(t);
}