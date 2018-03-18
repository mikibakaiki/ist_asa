#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

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

// A structure to represent a stack
struct StackNode {
    int data;
    struct StackNode* next;
}*Stack;

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

Stack newNode(int data) {
    Stack stackNode = (Stack) malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(Stack root) {
    return !root;
}

void push(Stack *root, int data) {
    Stack stackNode = newNode(data);
    stackNode->next = *root;
    *root = stackNode;
    // printf("%d pushed to stack\n", data);
}

int pop(Stack *root) {
    if (isEmpty(*root)) {
        return -1;
    }
    Stack temp = *root;
    *root = (*root)->next;
    int popped = temp->data;
    free(temp);

    return popped;
}

int peek(Stack root) {
    if (isEmpty(root))
        return INT_MIN;
    return root->data;
}

int checkStack(Stack *root, int index) {
    Stack temp = *root;
    int exists = 0;
    while(exists == 0) {
        if(temp->data == index) {
            exists = 1;
        }
        else {
            temp = *root->next;
        }
    }
    return exists;
}

static int visited = 0;
static Stack nodeStack = NULL;

void TarjanSCC(Graph G) {

    int i;

    for(i = 0; i < G->numVertices; i++) {
        G->adj[i]->discovery = -1;
        G->adj[i]->index = i+1;
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

    push(&nodeStack, G->adj[vertex]->index);

    int i;
    link *x;

    for(x = G->adj[vertex]; x->next != NULL; x = x->next) {
        if (x->discovery == -1) {
            TarjanVisit(G, &x);
            G->adj[vertex]->lowest = minimum(G->adj[vertex]->lowest, x->lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if (checkStack(&nodeStack, G->adj[vertex]->index) == 1) {
            G->adj[vertex]->lowest = minimum(G->adj[vertex]->lowest, x->lowest);
        }
    }
    int popped = -1;
    int scc_list[];
    int j = 0;
    /* this is the root of the SCC */
    if (G->adj[vertex]->discovery == G->adj[vertex]->lowest) {
        while( popped != G->adj[vertex]->index) {
            popped = pop(&nodeStack);
            printf("popped element %d from stack.\n", popped);
            scc_list[j] = popped;
            j++;
        }
        /* retirar os elementos da stack/lista */
        /* até que G->adj[vertex]->index == ao elemento que saiu da lista */
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

    Graph graph = GraphInit(int numNodes);

    for(i = 0; i < numConnections; i++) {

        int vertU, vertV;

		scanf("%d %d", &vertU, &vertV);
        Edge newEdge;
        newEdge.v = vertU;
        newEdge.w = vertV;

        GraphInsertEdge(graph, newEdge);
	}


    TarjanSCC(graph);

    return 0;


}
