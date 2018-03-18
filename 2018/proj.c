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
    link *adj;
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
    G->adj = malloc(numVertices*sizeof(link));

    for (i = 0; i < numVertices; i++) {
        G->adj[i] = NULL;
    }

    return G;
}

void GraphInsertEdge(Graph G, Edge e) {
    int vert1 = e.v;
    int vert2 = e.w;

    G->adj[vert1] = InsertBegin(vert1, G->adj[vert1]);
    G->adj[vert2] = InsertBegin(vert2, G->adj[vert2]);

    G->numEdges++;
}

static int visited = 0;

void TarjanSCC(Graph G) {

    // disc[u] = time;
    // low[u] = time;

    int *stack;
    stack = malloc(sizeof(int) * G->numVertices);
    int i;

    for(i = 0; i < G->numVertices; i++) {
        G->adj[i]->discovery = -1;
    }

    for(i = 0; i < G->numVertices; i++) {
        if(G->adj[i]->discovery == -1) {
            TarjanVisit(G, G->adj[i]);
        }
    }
}


void TarjanVisit(Graph G, link vertex) {

    G->adj[vertex]->discovery = visited;
    G->adj[vertex]->lowest = visited;
    visited++;

    /* por o vertice na stack */

    int i;
    link *x;
    for(x = G->adj[vertex]; x->next != NULL; x = x->next) {
        if (x->discovery == -1) {
            TarjanVisit(G, &x);
            G->adj[vertex]->lowest = minimum(G->adj[vertex]->lowest, x->lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if ( ) {
            G->adj[vertex]->lowest = minimum(G->adj[vertex]->lowest, x->lowest);
        }
    }

    /* this is the root of the SCC */
    if (G->adj[vertex]->discovery == G->adj[vertex]->lowest) {
        /* retirar os elementos da stack/lista */
        /* até que G->adj[vertex]->index == ao elemento que saiu da lista */
    }
}




}

int minimum(int u, int v) {
    return u > v ? v : u;
}





















int main()  {
    /*Number of supermarkets*/
    int numNodes;

    /* Number of connections - arches*/
    int numConnections;

    int i;

 	scanf("%d %d", &numNodes, &numConnections);

}
