#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* To compile, run: */
/*gcc -ansi -g -Wall proj.c -o test*/

typedef struct node {
    int discovery;
    int lowest;
} Node;

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

int numNodes;
static Link *head;
/*int nodesVisited;*/
Node *vertexInfo;
int visited = 0;
Stack nodeStack = NULL;


Link newNode(int value) {
    Link x = (Link) malloc(sizeof(struct graph));
    x->index = value;
    x->next = NULL;
    return x;
}

Link insertEnd(Link nodeHead, int value) {

    Link x;
    if(nodeHead == NULL) {
        /*printf("head e null\n");*/
        return newNode(value);
    }
    for(x = nodeHead; x->next != NULL; x = x->next);
    x->next = newNode(value);
    return nodeHead;
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
    int exists = 0;
    while(exists == 0) {
        if(temp->data == index) {
            exists = 1;
        }
        else {
            temp = temp->next;
        }
    }
    return exists;
}

/* STACK ADT END */


int minimum(int u, int v) {
    return u > v ? v : u;
}


void TarjanVisit(int vert) {

    // if( nodesVisited != 0) {}
    vertexInfo[vert].discovery = visited;
    vertexInfo[vert].lowest = visited;
    visited++;

    push(&nodeStack, vert);
    printf("Pushed %d to stack\n", vert);
    printf("Stack top = %d\n", peek(nodeStack));

    Link x;

    for(x = head[vert]; x != NULL; x = x->next) {
        if (vertexInfo[x->index].discovery == -1) {
            printf("am doing dfs\n\n");
            // nodesVisited --;
            TarjanVisit(x->index);
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[x->index].lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if (checkStack(&nodeStack, x->index) == 1) {
            vertexInfo[vert].lowest = minimum(vertexInfo[vert].lowest, vertexInfo[x->index].lowest);
        }
    }

    int popped = -1;

    // int j = 0;
    /* this is the root of the SCC */
    if (vertexInfo[vert].discovery == vertexInfo[vert].lowest) {
        /*printf("Valor discovery do vertice %d: %d\n",vertex, G->adj[vertex]->discovery);*/
        /*printf("Valor lowest do vertice %d: %d\n", vertex, G->adj[vertex]->lowest);*/
        /*printf("value of popped before -> %d\n", popped);*/

        /* retirar os elementos da stack */
        /* até que vert == popped */
        while( popped != vert) {
            /*printf("popped before popping again: %d\n", popped);*/
            popped = pop(&nodeStack);
            printf("popped element %d from stack.\n", popped);
            /*scc_list[j] = popped;
            j++;*/
        }
        printf("acabou o conjunto\n");
    }
}

void TarjanSCC() {
    printf("entrei no tarjanSCC\n");
    int k;
    // printf("inicializei os valores de discovery\n");

    for(k = 0; k < numNodes; k++) {
        // printf("entrei no segundo for em tarjanSCC()\n");
        if(vertexInfo[k].discovery == -1) {
            printf("vou fazer o tarjan visit() do vertice %d\n", k);
            TarjanVisit(k);
        }
    }
}



int main()  {
    /* Number of connections - arches*/
    int numConnections;

    int i;

    scanf("%d %d", &numNodes, &numConnections);

    /*nodesVisited = numNodes;*/

    head = (Link*) malloc(numNodes * sizeof(Link));

    vertexInfo = malloc(numNodes * sizeof(Node));

    for (i = 0; i < numNodes; i++) {
        vertexInfo[i].discovery = -1;
        vertexInfo[i].lowest = -1;
    }

    for(i = 0; i < numConnections; i++) {
        int vertU, vertV;
        scanf("%d %d", &vertU, &vertV);
        head[vertU-1] = insertEnd(head[vertU-1], vertV-1);
    }

    // printf("numero de edges do grafo: %d\n", graph->numEdges);
    // printf("numero de nodes do grafo: %d\n", graph->numVertices);
    TarjanSCC();

    for(i = 0; i < numNodes; i++) {
        free(head[i]);
    }
    free(head);
    free(vertexInfo);
    /*printf("SCC:\n");
    for(i = 0; i < 3; i++) {
    printf("%d\n", scc_list[i]);
}*/


return 0;


}
