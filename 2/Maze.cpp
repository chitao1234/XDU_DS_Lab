#include <cstring>
#include <iostream>

#define N 10

struct Pos {
    int x, y;
};

struct Path {
    Pos pos;
    int direction;
};

typedef Path SElemType;

struct SNode {
    SElemType data;
    SNode *next;
};

typedef SNode *Stack;

const int directions[][2] = {{0, 0}, {1, 0}, {0, 1}, {-1, 0}, {0, -1}};

void *SafeMalloc(int size) {  // 预先处理malloc失败
    void *res = malloc(size);
    if (!res) {
        exit(EXIT_FAILURE);
    }
    return res;
}

void InitStack(Stack &s) {
    s = (SNode *)SafeMalloc(sizeof(SNode));
    s->next = NULL;
}

void Push(Stack &s, SElemType data) {
    SNode *node = (SNode *)SafeMalloc(sizeof(SNode));
    node->data = data;
    node->next = s->next;
    s->next = node;
}

bool StackEmpty(Stack s) {
    return s->next == NULL;
}

SElemType Pop(Stack &s) {
    if (StackEmpty(s)) {
        exit(EXIT_FAILURE);
    }
    SNode *node = s->next;
    SElemType data = node->data;
    s->next = s->next->next;
    free(node);
    return data;
}

SElemType GetTop(Stack &s) {
    if (StackEmpty(s)) {
        exit(EXIT_FAILURE);
    }
    return s->next->data;
}

Pos NextPos(Pos p, int direction) {
    return {p.x + directions[direction][0], p.y + directions[direction][1]};
}

Stack SolveMaze(char maze[N + 2][N + 2], Pos start, Pos end) {
    Stack s;
    InitStack(s);
    Push(s, {start, 1});
    maze[start.x][start.y] = 2;  // 表示已经访问过
    while (!StackEmpty(s)) {
        Path p = GetTop(s);
        Pos next = NextPos(p.pos, p.direction);
        if (next.x == end.x && next.y == end.y) {
            Push(s, {next, 0});
            break;
        }
        if (maze[next.x][next.y] == 0) {
            Push(s, {next, 1});
            maze[next.x][next.y] = 2;
        } else {
            Pop(s);
            if (p.direction < 4) {
                ++p.direction;
                Push(s, p);
            } else {
                continue;
            }
        }
    }
    return s;
}

void printStack(SNode *s) {
    if (s && s->next) {
        printStack(s->next);
    }
    printf("(%d %d %d) ", s->data.pos.x, s->data.pos.y, s->data.direction);
    free(s);
}

/* 测试
9 8
1 1 9 8
0 0 1 0 0 0 1 0
0 0 1 0 0 0 1 0
0 0 0 0 1 1 0 1
0 1 1 1 0 0 1 0
0 0 0 1 0 0 0 0
0 1 0 0 0 1 0 1
0 1 1 1 1 0 0 1
1 1 0 0 0 1 0 1
1 1 0 0 0 0 0 0
*/
int main() {
    char maze[N + 2][N + 2];  // 1为有障碍，0为可通行
    int rowSize, colSize;
    scanf("%d%d", &rowSize, &colSize);
    Pos start, end;
    scanf("%d%d", &start.x, &start.y);
    scanf("%d%d", &end.x, &end.y);
    memset(maze, 1, sizeof(maze));
    for (int i = 1; i <= rowSize; ++i) {
        for (int j = 1; j <= colSize; ++j) {
            scanf("%hhd", &maze[i][j]);
        }
    }
    Stack ans = SolveMaze(maze, start, end);
    printStack(ans->next);
    free(ans);
    return 0;
}