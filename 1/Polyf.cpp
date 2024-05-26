#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define EPS 1e-5

typedef struct Node {
    double coef;
    int exp;
    struct Node *next;
} Term, *Poly;

void *SafeMalloc(int size) {  // 预先处理malloc失败
    void *res = malloc(size);
    if (!res) {
        exit(EXIT_FAILURE);
    }
    return res;
}

Poly read() {  // 读入以指数升序排列的多项式，使用头插法将其转换为使用指数降序排列的链表
    int len;
    scanf("%d", &len);
    Poly poly = (Term *)SafeMalloc(sizeof(Term));
    poly->next = NULL;
    for (int i = 0; i < len; ++i) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        scanf("%lf %d", &n->coef, &n->exp);
        n->next = poly->next;
        poly->next = n;
    }
    return poly;
}

Poly add(Poly A, Poly B) {  // 实现多项式相加
    Term *p = A->next, *q = B->next;
    Poly ans = (Term *)SafeMalloc(sizeof(Term));
    ans->next = NULL;
    Term *tail = ans;
    while (p && q) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        if (p->exp > q->exp) {
            n->coef = p->coef;
            n->exp = p->exp;
            p = p->next;
            tail->next = n;
            tail = n;
        } else if (p->exp < q->exp) {
            n->coef = q->coef;
            n->exp = q->exp;
            q = q->next;
            tail->next = n;
            tail = n;
        } else {
            n->coef = q->coef + p->coef;
            n->exp = q->exp;
            if (fabs(n->coef) < EPS) {
                free(n);
            } else {
                tail->next = n;
                tail = n;
            }
            q = q->next;
            p = p->next;
        }
    }
    while (p) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        n->coef = p->coef;
        n->exp = p->exp;
        p = p->next;
        tail->next = n;
        tail = n;
    }
    while (q) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        n->coef = q->coef;
        n->exp = q->exp;
        q = q->next;
        tail->next = n;
        tail = n;
    }
    tail->next = NULL;
    return ans;
}

Poly sub(Poly A, Poly B) {  // 实现多项式相减
    Term *p = A->next, *q = B->next;
    Poly ans = (Term *)SafeMalloc(sizeof(Term));
    ans->next = NULL;
    Term *tail = ans;
    while (p && q) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        if (p->exp > q->exp) {
            n->coef = p->coef;
            n->exp = p->exp;
            p = p->next;
            tail->next = n;
            tail = n;
        } else if (p->exp < q->exp) {
            n->coef = -q->coef;
            n->exp = q->exp;
            q = q->next;
            tail->next = n;
            tail = n;
        } else {
            n->coef = q->coef - p->coef;
            n->exp = q->exp;
            if (fabs(n->coef) < EPS) {
                free(n);
            } else {
                tail->next = n;
                tail = n;
            }
            q = q->next;
            p = p->next;
        }
    }
    while (p) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        n->coef = p->coef;
        n->exp = p->exp;
        p = p->next;
        tail->next = n;
        tail = n;
    }
    while (q) {
        Term *n = (Term *)SafeMalloc(sizeof(Term));
        n->coef = -q->coef;
        n->exp = q->exp;
        q = q->next;
        tail->next = n;
        tail = n;
    }
    tail->next = NULL;
    return ans;
}

void printPoly(Poly poly) {
    Term *p = poly->next;
    if (!p) {
        printf("0 0\n");
        return;
    }
    while (p && fabs(p->coef) < EPS) {
        p = p->next;
    }
    while (p) {
        printf("%.1f %d", p->coef, p->exp);
        p = p->next;
        while (p && fabs(p->coef) < EPS) {
            p = p->next;
        }
        if (p) {  // not last one
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    Poly A = read();
    Poly B = read();
    Poly addList = add(A, B);
    Poly subList = sub(A, B);
    printf("C(x) = ");
    printPoly(addList);
    printf("D(x) = ");
    printPoly(subList);
}