#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// 单链表节点结构
struct Node {
    int data;    // 节点存储的值
    Node *next;  // 指向下一个节点的指针
};
typedef Node *List;

void *SafeMalloc(int size) {  // 预先处理malloc失败
    void *res = malloc(size);
    if (!res) {
        exit(EXIT_FAILURE);
    }
    return res;
}

List read() {  // 读入长度，再读入对应个数的数字，使用尾插法建立链表
    int len;
    scanf("%d", &len);
    List list = (Node *)SafeMalloc(sizeof(Node));
    list->next = NULL;
    Node *tail = list;
    for (int i = 0; i < len; ++i) {
        Node *n = (Node *)SafeMalloc(sizeof(Node));
        scanf("%d", &n->data);
        tail->next = n;
        tail = n;
    }
    tail->next = NULL;
    return list;
}

void sort(List &A) {  // 冒泡排序
    if (!A->next) return;
    Node *last = NULL;
    int swapped = 0;
    do {
        swapped = 0;
        Node *p = A->next, *pre = A;
        while (p && p->next != last) {
            if (p->data > p->next->data) {
                Node *tmp = p->next;
                pre->next = tmp;
                p->next = tmp->next;
                tmp->next = p;
                p = tmp;
                swapped = 1;
            }
            pre = p;
            p = p->next;
        }
        last = p;
    } while (swapped);
}

void printList(List list) {
    Node *p = list->next;

    while (p) {
        printf("%d", p->data);
        p = p->next;
        if (p) {  // not last one
            printf(" ");
        }
    }
    printf("\n");
}

int main() {
    List A = read();
    sort(A);
    printList(A);
}