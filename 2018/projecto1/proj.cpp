#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

#define NOT_SEEN 0
#define ON_STACK 1
#define DONE -3


/* To compile, run: */
/*g++ -ansi -g -Wall proj.c -o test*/

typedef struct node {
    int discovery;
    int lowest;
    int scc;
    int entered;
} Node;

typedef struct scc {
    int u;
    int v;
} sccEdge;

typedef struct graph {
    int index;
    struct graph *next;
} *Link;

/*A structure to represent a stack*/
typedef struct StackNode {
    int data;
    struct StackNode* next;
} *Stack;

/* GLOBAL VARIABLES */

/* Numero de vertices do grafo */
int numNodes;

/* Lista ligada que guarda as edges todas do grafo */
static Link *head;

/* Lista que guarda as informações de cada um dos vertices */
Node *vertexInfo;

/* Keeps track of discovery time */
int visited = 0;

/* Stack to keep vertex */
Stack nodeStack = NULL;

/* Number of SCC */
int scc = 0;

/*lista de edges entre diferentes scc*/
std::list<sccEdge> sccEdges;

/* Sempre que houver uma edge de um scc para outro, serao estes os identificadores apresentados*/
std::vector<int> vertexSccId;

/*   END OF GLOBAL VARIABLES    */

/*  GRAPH FUNCTIONS  */

Link newNode(int value) {
    Link x = (Link) malloc(sizeof(struct graph));
    x->index = value;
    x->next = NULL;
    return x;
}

Link insertEnd(Link nodeHead, int value) {

    Link x = newNode(value);
    x->next = nodeHead;
    return x;
}

/*   GRAPH FUNCTIONS END    */

/* STACK ADT */

Stack newStackNode(int data) {
    Stack stackNode = (Stack) malloc(sizeof(struct StackNode));
    stackNode->data = data;
    stackNode->next = NULL;
    return stackNode;
}

int isEmpty(Stack root) {
    return !root;
}

void push(Stack *root, int data) {
    Stack stackNode = newStackNode(data);
    stackNode->next = *root;
    *root = stackNode;
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

/* STACK ADT END */

int minimum(int u, int v) {
    return u > v ? v : u;
}

bool compare_a(int first, int second ) {
    return first < second;
}

bool compareEdges(struct scc first, struct scc second) {
    if(first.u == second.u) {
        if(first.v < second.v) {
            return true;
        }
    }
    else if(first.u < second.u) {
        return true;
    }
    return false;
}

void TarjanVisit(int vert) {

    vertexInfo[vert].discovery = visited;
    vertexInfo[vert].lowest = visited;
    visited++;

    push(&nodeStack, vert);
    vertexInfo[vert].entered = ON_STACK;

    Link x;
    int a;
    for(x = head[vert]; x != NULL; x = x->next) {
        a = x->index;
        if (vertexInfo[a].discovery == -1) {
            TarjanVisit(a);
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[a].lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if(vertexInfo[a].entered == ON_STACK) {
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[a].lowest);
        }
    }

    int popped = -1;
    int scc_id = INT_MAX;
    /* this is the root of the SCC */
    if (vertexInfo[vert].discovery == vertexInfo[vert].lowest) {
        /* retirar os elementos da stack até que vert == popped */
        while (popped != vert) {
            popped = pop(&nodeStack);

            if(popped < scc_id) {
                scc_id = popped;
            }
            vertexInfo[popped].scc = scc;
            vertexInfo[popped].entered = DONE;
        }
        vertexSccId.push_back(scc_id);
        scc++;
    }
}

void TarjanSCC() {
    int k;

    for(k = 0; k < numNodes; k++) {
        if(vertexInfo[k].discovery == -1) {
            TarjanVisit(k);
        }
    }
}

void sccSearchEdges() {

    int i;
    int v;
    Link x;
    sccEdge n;
    for (i = 0; i < numNodes; i++) {
        v = vertexInfo[i].scc;
        if (v == scc) {
            break;
        }
        for (x = head[i]; x != NULL; x = x->next) {
            int y = vertexInfo[x->index].scc;
            if(v != y) {
                n.u = vertexSccId[v];
                n.v = vertexSccId[y];
                sccEdges.push_front(n);
            }
        }
    }
}

bool repeated (sccEdge deleted, sccEdge notdeleted) {
    return (deleted.u == notdeleted.u && deleted.v == notdeleted.v);
}

void initStuff() {
    int i;
    for (i = 0; i < numNodes; i++) {
        head[i] = NULL;
        vertexInfo[i].discovery = -1;
        vertexInfo[i].lowest = -1;
        vertexInfo[i].scc = -1;
        vertexInfo[i].entered = false;
    }
}

void sortAndErase() {
    sccEdges.sort(compareEdges);
    sccEdges.unique(repeated);
}

int main()  {
    /* Number of connections - arches*/
    int numConnections;

    int i;

    scanf("%d %d", &numNodes, &numConnections);

    head = (Link *) malloc(numNodes * sizeof(Link));
    vertexInfo = (Node *) malloc(numNodes * sizeof(Node));

    initStuff();

    for(i = 0; i < numConnections; i++) {
        int vertU, vertV;
        scanf("%d %d", &vertU, &vertV);
        head[vertU-1] = insertEnd(head[vertU-1], vertV-1);
    }

    TarjanSCC();
    sccSearchEdges();
    sortAndErase();

    for(i = 0; i < numNodes; i++) {
        free(head[i]);
    }
    free(head);
    free(nodeStack);
    free(vertexInfo);

    /* RESPOSTAS DO PROJECTO */
    std::cout << scc << "\n";
    std::cout << sccEdges.size() << "\n";
    for (sccEdge list_edges : sccEdges ) {
        printf("%d %d\n", list_edges.u + 1, list_edges.v + 1);
    }
    return 0;
}
