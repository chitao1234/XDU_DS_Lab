#include <cstring>
#include <fstream>
#include <iostream>
using namespace std;

#define MAX_WEIGHT 1e9
#define MAX_LEN 200
#define MAXN 70

struct HTNode {
    char ch;
    double weight;
    int parent, lchild, rchild;
};

typedef HTNode *HuffmanTree;

struct CharCode {
    char ch;
    char *code;
};

typedef CharCode *HuffmanCode;

void mergeNode(HuffmanTree t, int n1, int n2, int i) {
    t[i].weight = t[n1].weight + t[n2].weight;
    t[i].parent = 0;
    t[i].lchild = n1;
    t[i].rchild = n2;
    t[i].ch = '\0';
    t[n1].parent = i;
    t[n2].parent = i;
}

void selectNode(HuffmanTree t, int n, int &n1, int &n2) {
    double min1 = MAX_WEIGHT, min2 = MAX_WEIGHT;
    for (int i = 1; i <= n; ++i) {
        if (t[i].parent) continue;
        if (t[i].weight < min1) {
            min2 = min1;
            min1 = t[i].weight;
            n2 = n1;
            n1 = i;
        } else if (t[i].weight < min2) {
            min2 = t[i].weight;
            n2 = i;
        }
    }
}

int findNode(HuffmanTree t, int n, char ch) {
    for (int i = 1; i <= n; ++i) {
        if (t[i].ch == ch) return i;
    }
    return -1;
}

HuffmanTree buildTree(int n) {
    HuffmanTree t = new HTNode[n * 2];
    if (!t) exit(EXIT_FAILURE);

    for (int i = 1; i <= n; ++i) {
        cin >> t[i].ch >> t[i].weight;
        t[i].parent = 0;
        t[i].lchild = 0;
        t[i].rchild = 0;
    }

    for (int i = n + 1; i <= n * 2 - 1; ++i) {
        int n1, n2;
        selectNode(t, i - 1, n1, n2);
        mergeNode(t, n1, n2, i);
    }

    return t;
}

int getHeight(HuffmanTree t, int i) {
    if (!i) return 0;
    if (t[i].lchild == 0 && t[i].rchild == 0) {
        return 1;
    } else {
        return 1 + max(getHeight(t, t[i].lchild), getHeight(t, t[i].rchild));
    }
}

void treeToCode(HuffmanTree t, HuffmanCode &code, int n) {
    int root = n * 2 - 1;
    int height = getHeight(t, root);
    char *temp = new char[height + 1];
    if (!temp) exit(EXIT_FAILURE);
    int p = root, len = 0, cnt = 0;
    // weight 用作 flag，记录访问状态
    for (int i = 1; i <= root; ++i) {
        t[i].weight = 0;
    }
    while (p) {
        if (t[p].weight == 0) {
            t[p].weight = 1;
            temp[len] = '0';
            if (t[p].lchild) {
                p = t[p].lchild;
                len++;
            }
        } else if (t[p].weight == 1) {
            t[p].weight = 2;
            temp[len] = '1';
            if (t[p].rchild) {
                p = t[p].rchild;
                len++;
            }
        } else {
            temp[len] = '\0';
            if (t[p].lchild == 0 && t[p].rchild == 0) {
                code[cnt].ch = t[p].ch;
                code[cnt].code = new char[strlen(temp) + 1];
                if (!code[cnt].code) exit(EXIT_FAILURE);
                strcpy(code[cnt].code, temp);
                cnt++;
            }
            p = t[p].parent;
            --len;
        }
    }
    delete[] temp;
}

void deleteCode(HuffmanCode &c, int n) {
    if (!c) return;
    for (int i = 0; i < n; ++i) {
        delete[] c[i].code;
    }
    delete[] c;
    c = NULL;
}

int encodeChar(HuffmanCode c, char ch, char *dest, int n) {
    for (int i = 0; i < n; ++i) {
        if (c[i].ch == ch) {
            strcpy(dest, c[i].code);
            return strlen(c[i].code);
        }
    }
    return 0;
}

void encode(HuffmanCode c, char *input, char *out, int maxLen, int n) {
    int len = strlen(input);

    char *dest = out;
    for (int i = 0; i < len; ++i) {
        if (dest - out >= maxLen) exit(EXIT_FAILURE);
        dest += encodeChar(c, input[i], dest, n);
    }
    *dest = '\0';
}

int decodeChar(HuffmanTree t, char *input, char *dest, int n) {
    int p = n * 2 - 1;
    char *ptr = input;
    bool flag = 1;
    while (flag) {
        if (t[p].rchild == 0 && t[p].lchild == 0) {
            *dest = t[p].ch;
            break;
        }
        if (*ptr != '\0') {
            int i = *ptr - '0';
            if (i == 1) {
                p = t[p].rchild;
            } else {
                p = t[p].lchild;
            }
            ptr++;
        } else {
            flag = false;
        }
    }
    return ptr - input;
}

void decode(HuffmanTree t, char *input, char *out, int maxLen, int n) {
    char *dest = out;
    while (*input != 0) {
        if (dest - out >= maxLen) exit(EXIT_FAILURE);
        input += decodeChar(t, input, dest, n);
        dest++;
    }
    *dest = '\0';
}

void saveTree(HuffmanTree t, int n) {
    ofstream s;
    s.open("hfmTree");
    for (int i = 1; i <= n * 2 - 1; ++i) {
        s << t[i].ch << ' ' << t[i].parent << ' ' << t[i].lchild << ' ' << t[i].rchild << '\n';
    }
}

HuffmanTree loadTree(int &n) {
    ifstream s;
    s.open("hfmTree");
    HuffmanTree t = new HTNode[MAXN];
    if (!t) exit(EXIT_FAILURE);
    int i = 1;
    while (true) {
        if (i >= MAXN) exit(EXIT_FAILURE);
        s >> t[i].ch >> t[i].parent >> t[i].lchild >> t[i].rchild;
        if (s.eof()) break;
        ++i;
    }
    n = (i + 1) / 2;
    return t;
}

void initialize(HuffmanTree &t, HuffmanCode &c, int &n) {
    deleteCode(c, n);

    c = new CharCode[n];
    if (!c) exit(EXIT_FAILURE);
    treeToCode(t, c, n);
}

bool verify() {
    ifstream f1;
    f1.open("ToBeTran");
    ifstream f2;
    f2.open("TextFile");
    char s1[MAX_LEN], s2[MAX_LEN];
    f1 >> s1;
    f2 >> s2;
    return !strcmp(s1, s2);
}

void saveText(const char *name, const char *content) {
    ofstream s;
    s.open(name);
    s << content;
}

void readText(const char *name, char (&buffer)[MAX_LEN]) {
    ifstream s;
    s.open(name);
    s >> buffer;
}

int main() {
    int option;

    HuffmanTree t = NULL;
    HuffmanCode code = NULL;
    int n = 0;
    char input[MAX_LEN];
    char output[MAX_LEN];
    bool running = true;
    while (running) {
        cout << "\nUsage:\n";
        cout << "0. Read input and save to file\n";
        cout << "1. Initialize the Huffman tree\n";
        cout << "2. Load the tree\n";
        cout << "3. Save the tree\n";
        cout << "4. Encode input\n";
        cout << "5. Decode input\n";
        cout << "6. Verify the results\n";
        cout << "7. Exit\n";
        cout << "Enter your option (1-7): ";

        cin >> option;

        // Call the corresponding functions based on the option chosen
        switch (option) {
            case 0:
                scanf("%s", input);
                saveText("ToBeTran", input);
                break;
            case 1:
                delete[] t;
                cin >> n;
                t = buildTree(n);
                initialize(t, code, n);
                break;
            case 2:
                delete[] t;
                t = loadTree(n);
                initialize(t, code, n);
                break;
            case 3:
                saveTree(t, n);
                break;
            case 4:
                readText("ToBeTran", input);
                encode(code, input, output, MAX_LEN, n);
                printf("Encoded: %s\n", output);
                saveText("CodeFile", output);
                break;
            case 5:
                readText("CodeFile", input);
                decode(t, input, output, MAX_LEN, n);
                printf("Decoded: %s\n", output);
                saveText("TextFile", output);
                break;
            case 6:
                if (verify()) {
                    cout << "OK!\n";
                } else {
                    cout << "ERROR!\n";
                }
                break;
            case 7:
                running = false;
                break;
            default:
                cout << "Invalid option. Please try again.\n";
                break;
        }
    }

    deleteCode(code, n);
    delete[] t;
    return 0;
}