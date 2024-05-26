#include <iostream>
using namespace std;

#define MAXV 50

// 邻接矩阵的数据结构
typedef int AdjMatrix[MAXV][MAXV];

struct GraphMatrix {
    int vexnum, arcnum;
    AdjMatrix arcs;
};

bool visited[MAXV];

void DFSMatrix(GraphMatrix &graph, int s) {
    visited[s] = true;
    cout << s << " ";

    for (int i = 0; i < graph.vexnum; i++) {
        if (graph.arcs[s][i] != 0 && !visited[i]) {
            DFSMatrix(graph, i);
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

void DFSList(GraphList &graph, int s) {
    visited[s] = true;
    cout << s << " ";

    for (ArcNode *p = graph.vertices[s].firstarc; p; p = p->nextarc) {
        if (!visited[p->adjvex]) {
            DFSList(graph, p->adjvex);
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
        if (!visited[i]) DFSMatrix(graphMatrix, i);
    }
    cout << endl;

    for (int i = 0; i < n; ++i) {
        visited[i] = false;
    }

    for (int i = 0; i < n; ++i) {
        if (!visited[i]) DFSList(graphList, i);
    }
    cout << endl;

    return 0;
}
