#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int index;
    int discovery;
    int lowest;
    struct node *next;
} *link;


typedef struct edge {
    int v;
    int w;
} Edge;

typedef struct graph {
    int numVertices;
    int numEdges;
    link *list;
} *Graph;


link InsertBegin(int index, link head) {
    link x = malloc(sizeof(struct node));

    x->index = index;
    x->next = head;

    return x;
}

Graph GraphInit(int numVertices) {
    int i;
    Graph G = malloc(sizeof(struct graph));
    G->numVertices = numVertices;
    G->numEdges = 0;
    G->list = malloc(numVertices*sizeof(link));

    for (i = 0; i < numVertices; i++) {
        G->list[i] = NULL;
    }

    return G;
}

void GraphInsertEdge(Graph G, Edge e) {
    int vert1 = e.v;
    int vert2 = e.w;

    G->list[vert1] = InsertBegin(vert1, G->list[vert1]);
    G->list[vert2] = InsertBegin(vert2, G->list[vert2]);

    G->numEdges++;
}

static int time = 0;

void TarjanSCC(Graph G) {

    // disc[u] = time;
    // low[u] = time;
    int visited = 0;

    int *stack;
    stack = malloc(sizeof(int) * G->numVertices);
    int i;

    for(i = 0; i < G->numVertices; i++) {
        G->list[i]->discovery = -1;
    }

    for(i = 0; i < G->numVertices; i++) {
        if(G->list[i]->discovery == -1) {
            TarjanVisit(G->list[i]);
        }
    }
}

























int main()  {
    /*Number of supermarkets*/
    int numNodes;

    /* Number of connections - arches*/
    int numConnections;

    int i;

 	scanf("%d %d", &numNodes, &numConnections);

}
