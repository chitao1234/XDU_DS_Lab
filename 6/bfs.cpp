#include <iostream>
#include <queue>
using namespace std;

#define MAXV 50

// 邻接矩阵的数据结构
typedef int AdjMatrix[MAXV][MAXV];

struct GraphMatrix {
    int vexnum, arcnum;
    AdjMatrix arcs;
};

bool visited[MAXV];

void BFSMatrix(GraphMatrix &graph, int s) {
    queue<int> q;

    q.push(s);
    visited[s] = true;
    cout << s << " ";

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (int i = 0; i < graph.vexnum; i++) {
            if (graph.arcs[v][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
                cout << i << " ";
            }
        }
    }
}

// 邻接表的数据结构
struct ArcNode {
    int adjvex;
    double weight;
    ArcNode *nextarc;
};

struct VertexNode {
    ArcNode *firstarc;
};

typedef VertexNode AdjList[MAXV];

struct GraphList {
    int vexnum, arcnum;
    AdjList vertices;
};

void InsertList(GraphList &graph, int u, int v, double w) {
    ArcNode *newNode = new ArcNode;
    if (!newNode) exit(EXIT_FAILURE);
    newNode->adjvex = v;
    newNode->weight = w;
    newNode->nextarc = graph.vertices[u].firstarc;
    graph.vertices[u].firstarc = newNode;
}

void BFSList(GraphList &graph, int s) {
    queue<int> q;

    q.push(s);
    visited[s] = true;
    cout << s << " ";

    while (!q.empty()) {
        int v = q.front();
        q.pop();

        for (ArcNode *p = graph.vertices[v].firstarc; p; p = p->nextarc) {
            if (!visited[p->adjvex]) {
                q.push(p->adjvex);
                visited[p->adjvex] = true;
                cout << p->adjvex << " ";
            }
        }
    }
}

int main() {
    int n, e;
    cin >> n >> e;

    GraphMatrix graphMatrix;
    graphMatrix.vexnum = n;
    graphMatrix.arcnum = e;

    GraphList graphList;
    graphList.vexnum = n;
    graphList.arcnum = e;

    for (int i = 0; i < e; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        graphMatrix.arcs[u][v] = w;
        graphMatrix.arcs[v][u] = w;
        InsertList(graphList, u, v, w);
        InsertList(graphList, v, u, w);
    }

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) BFSMatrix(graphMatrix, i);
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) BFSList(graphList, i);
    }
    cout << endl;

    return 0;
}
