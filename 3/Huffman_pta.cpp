#include <cstring>
#include <iostream>
#include <queue>
using namespace std;

#define MAXN 70

struct HTNode {
    bool isLeaf;
    union {
        char c;  // 叶子结点时
        struct {
            HTNode *left, *right;  // 非叶子结点
        };
    };
    int weight;

    bool operator<(const HTNode other) const {
        return weight < other.weight;
    }
};

struct Cmp {
    bool operator()(const HTNode *lhs, const HTNode *rhs) const {
        return lhs->weight > rhs->weight;
    }
};

HTNode *createNode(char c, int w) {
    HTNode *node = new HTNode;
    if (!node) exit(EXIT_FAILURE);
    node->isLeaf = true;
    node->c = c;
    node->weight = w;
    return node;
}

HTNode *mergeNode(HTNode *l, HTNode *r) {
    HTNode *node = new HTNode;
    if (!node) exit(EXIT_FAILURE);
    node->isLeaf = false;
    node->left = l;
    node->right = r;
    node->weight = l->weight + r->weight;
    return node;
}

HTNode *Initialize(int n) {
    priority_queue<HTNode *, vector<HTNode *>, Cmp> pq;

    if (n >= MAXN) exit(EXIT_FAILURE);
    for (int i = 1; i <= n; ++i) {
        char c;
        int w;
        cin >> c >> w;
        pq.push(createNode(c, w));
    }

    while (pq.size() > 1) {
        HTNode *l = pq.top();
        pq.pop();
        HTNode *r = pq.top();
        pq.pop();
        pq.push(mergeNode(l, r));
    }
    return pq.top();
}

struct CodeLength {
    char c[MAXN];
    int len[MAXN];
    int weight[MAXN];
    int cnt;
};

int Encode(HTNode *t, CodeLength *c, int depth) {
    if (!t) return 0;
    if (t->isLeaf) {
        c->c[c->cnt] = t->c;
        c->len[c->cnt] = depth;
        c->weight[c->cnt] = t->weight;
        c->cnt++;
        return depth * t->weight;
    } else {
        return Encode(t->left, c, depth + 1) + Encode(t->right, c, depth + 1);
    }
}

int GetWeight(CodeLength *c, char ch) {
    for (int i = 0; i < c->cnt; ++i) {
        if (c->c[i] == ch) {
            return c->weight[i];
        }
    }
    return -1;
}

bool ProcessCode(HTNode *t, char ch, string code) {
    int len = code.length();
    HTNode *p = t, *pre = NULL;
    int childType = 0;
    for (int i = 0; i < len; ++i) {
        if (!p) {
            HTNode *node = new HTNode;
            if (!node) exit(EXIT_FAILURE);
            cerr << "New Node: " << node << endl;
            p = node;
            p->isLeaf = false;
            p->left = NULL;
            p->right = NULL;
            if (!pre) {
                exit(EXIT_FAILURE);
            }
            if (childType == 0) {
                pre->left = p;
            } else {
                pre->right = p;
            }
        }
        childType = code[i] - '0';
        if (code[i] == '0') {
            pre = p;
            p = p->left;
        } else {
            pre = p;
            p = p->right;
        }
    }
    if (p) {
        return false;
    } else {
        HTNode *node = new HTNode;
        if (!node) exit(EXIT_FAILURE);
        cerr << "New Node: " << node << endl;
        p = node;
        p->isLeaf = true;
        p->c = ch;
        if (!pre) {
            exit(EXIT_FAILURE);
        }
        if (childType == 0) {
            pre->left = p;
        } else {
            pre->right = p;
        }
    }
    return true;
}

void deleteTree(HTNode *t) {
    if (!t) return;
    if (!t->isLeaf) {
        deleteTree(t->left);
        deleteTree(t->right);
    }
    cerr << "Remove Node: " << t << endl;
    delete t;
}

bool TryBuildTree(char ch[], string code[], int n, HTNode **t) {
    if (!*t) {
        HTNode *node = new HTNode;
        if (!node) exit(EXIT_FAILURE);
        *t = node;
        (*t)->isLeaf = false;
        (*t)->left = NULL;
        (*t)->right = NULL;
    }
    for (int i = 0; i < n; ++i) {
        if (!ProcessCode(*t, ch[i], code[i])) {
            deleteTree(*t);
            *t = NULL;
            return false;
        }
    }
    return true;
}

int main() {
    int n;
    cin >> n;
    HTNode *huffman = Initialize(n);
    CodeLength c;
    c.cnt = 0;
    int len = Encode(huffman, &c, 0);

    int m;
    cin >> m;

    char *ch = new char[n];
    string *code = new string[n];

    for (int i = 0; i < m; ++i) {
        int flag = 1;
        int newLen = 0;
        for (int j = 0; j < n; ++j) {
            cin >> ch[j] >> code[j];
            newLen += code[j].length() * GetWeight(&c, ch[j]);
        }
        flag &= newLen == len;
        HTNode *t = NULL;
        flag &= TryBuildTree(ch, code, n, &t);
        deleteTree(t);
        // for (int i1 = 0; i1 < n; ++i1) {
        //     for (int j1 = i1 + 1; j1 < n; ++j1) {
        //         if (strncmp(code[i1].c_str(), code[j1].c_str(), min(code[i1].length(), code[j1].length())) == 0) {
        //             flag = false;
        //             break;
        //         }
        //     }
        // }
        cout << (flag ? "Yes" : "No") << '\n';
    }
    delete[] code;
    delete[] ch;
}