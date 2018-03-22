#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <set>




/* To compile, run: */
/*gcc -ansi -g -Wall proj.c -o test*/

typedef struct node {
    int discovery;
    int lowest;
    int scc;
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

int visited = 0;
Stack nodeStack = NULL;
int scc = 0;
// std::list< std::list<int> > sccBundle;
// std::list<int> sccSubNet;

/*lista de edges entre diferentes scc*/
std::list<sccEdge> sccEdges;

/* vector que guarda os identificadores de cada scc, ou seja, o numero que o identifica em termos de vertice */
/* Sempre que houver uma edge de um scc para outro, serao estes os identificadores apresentados*/
std::vector<int> vertexSccId;

/*                  */
Link newNode(int value) {
    Link x = (Link) malloc(sizeof(struct graph));
    x->index = value;
    x->next = NULL;
    return x;
}

Link insertEnd(Link nodeHead, int value) {

    Link x;
    if(nodeHead == NULL) {
        return newNode(value);
    }
    for(x = nodeHead; x->next != NULL; x = x->next) {
        if(x->index == value) {
            return nodeHead;
        }
    }
    x->next = newNode(value);
    return nodeHead;
}

void removeNode(Link nodeHead, int headIndex) {
    Link current, previous;
    previous = NULL;

    for (current = nodeHead; current != NULL; previous = current, current = current->next) {
        if (vertexInfo[current->index].scc == vertexInfo[headIndex].scc) {  /* Found it. */
            if (previous == NULL) {
                /* Fix beginning pointer. */
                nodeHead = current->next;
            }
            else {
                previous->next = current->next;
            }
            free(current);
            return;
        }
    }
}

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
    /*printf("%d pushed to stack\n", data);*/
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

    while(temp != NULL) {
        if(temp->data == index) {
            return 1;
        }
        else {
            temp = temp->next;
        }
    }
    return 0;
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

    Link x;

    for(x = head[vert]; x != NULL; x = x->next) {
        if (vertexInfo[x->index].discovery == -1) {
            TarjanVisit(x->index);
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[x->index].lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if (checkStack(&nodeStack, x->index) == 1) {
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[x->index].lowest);
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
    for (i = 0; i < numNodes; i++) {
        Link x;
        sccEdge n;
        v = vertexInfo[i].scc;
        for (x = head[i]; x != NULL; x = x->next) {
            int y = vertexInfo[x->index].scc;
            if(v != y) {
                n.u = vertexSccId[v];
                n.v = vertexSccId[y];
                sccEdges.push_back(n);
            }
        }
    }


}

bool repeated (sccEdge deleted, sccEdge notdeleted) {
    return (deleted.u == notdeleted.u && deleted.v == notdeleted.v);
}


int main()  {
    /* Number of connections - arches*/
    int numConnections;

    int i;

    scanf("%d %d", &numNodes, &numConnections);

    head = (Link *) malloc(numNodes * sizeof(Link));

    vertexInfo = (Node *) malloc(numNodes * sizeof(Node));

    for (i = 0; i < numNodes; i++) {
        vertexInfo[i].discovery = -1;
        vertexInfo[i].lowest = -1;
        vertexInfo[i].scc = -1;
    }

    for(i = 0; i < numConnections; i++) {
        int vertU, vertV;
        scanf("%d %d", &vertU, &vertV);
        head[vertU-1] = insertEnd(head[vertU-1], vertV-1);
    }

    TarjanSCC();
    sccSearchEdges();
    sccEdges.sort(compareEdges);
    sccEdges.unique(repeated);

    for(i = 0; i < numNodes; i++) {
        free(head[i]);
    }
    free(head);
    free(vertexInfo);

    /* RESPOSTAS DO PROJECTO */
    std::cout << scc << "\n";
    std::cout << sccEdges.size() << "\n";
    for (sccEdge list_edges : sccEdges ) {
        printf("%d %d\n", list_edges.u + 1, list_edges.v + 1);
    }
    return 0;
}
