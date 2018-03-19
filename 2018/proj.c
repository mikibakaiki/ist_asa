#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

/* To compile, run: */
/*gcc -ansi -g -Wall proj.c -o test*/

typedef struct node {
    int index;
    int discovery;
    int lowest;
    struct node *next;
} *link;

/*typedef struct edge {
int v;
int w;
} Edge;

typedef struct graph {
int numVertices;
int numEdges;
link *adj;
} *Graph;*/

/*A structure to represent a stack*/
typedef struct StackNode {
    int data;
    struct StackNode* next;
} *Stack;



/* GLOBAL VARIABLES */

int numNodes;
link * head;


link newNode(int value) {

    link x = (link) malloc(sizeof(struct node));

    x->index = value;
    x->discovery = -1;
    x->lowest = -1;
    x->next = NULL;

    return x;
}

link insertEnd(link head, int value) {

    link x;
    if(head == NULL) {
        /*printf("head e null\n");*/
        return newNode(value);
    }
    for(x = head; x->next != NULL; x = x->next);
    x->next = newNode(value);
    return head;
}

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

int minimum(int u, int v) {
    return u > v ? v : u;
}


static int visited = 0;
static Stack nodeStack = NULL;


void TarjanVisit(int vert) {

    head[vert]->discovery = visited;
    head[vert]->lowest = visited;
    visited++;

    push(&nodeStack, head[vert]->index);
    printf("Pushed %d to stack\n", head[vert]->index);

    link x;

    for(x = head[vert]->next; x != NULL; x = x->next) {
        if (x->discovery == -1) {
            printf("am doing dfs\n\n");
            TarjanVisit(x->index);
            head[vert]->lowest = minimum(head[vert]->lowest, x->lowest);
        }
        /*ou se esse vertice estiver na stack*/
        else if (checkStack(&nodeStack, x->index) == 1) {
            head[vert]->lowest = minimum(head[vert]->lowest, x->lowest);
        }
    }
    int popped = -1;

    // int j = 0;
    /* this is the root of the SCC */
    if (head[vert]->discovery == head[vert]->lowest) {
        /*printf("Valor discovery do vertice %d: %d\n",vertex, G->adj[vertex]->discovery);*/
        /*printf("Valor lowest do vertice %d: %d\n", vertex, G->adj[vertex]->lowest);*/
        /*printf("value of popped before -> %d\n", popped);*/

        while( popped != head[vert]->index) {
            /*printf("popped before popping again: %d\n", popped);*/
            popped = pop(&nodeStack);
            printf("popped element %d from stack.\n", popped);
            /*scc_list[j] = popped;
            j++;*/
        }
        /* retirar os elementos da stack/lista */
        /* até que G->adj[vertex]->index == ao elemento que saiu da lista */
    }
}

void TarjanSCC() {
    printf("entrei no tarjanSCC\n");
    int k;
    // printf("inicializei os valores de discovery\n");

    for(k = 0; k < numNodes; k++) {
        // printf("entrei no segundo for em tarjanSCC()\n");
        if(head[k]->discovery == -1) {
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

    head = (link*) malloc(numNodes*sizeof(link));
    for (i = 0; i < numConnections; i++) {
        head[i] = insertEnd(head[i], i);
    }

    for(i = 0; i < numConnections; i++) {

        int vertU, vertV;

        scanf("%d %d", &vertU, &vertV);
        head[vertU-1] = insertEnd(head[vertU-1], vertV-1);
    }

    // printf("numero de edges do grafo: %d\n", graph->numEdges);
    // printf("numero de nodes do grafo: %d\n", graph->numVertices);
    TarjanSCC();

    /*printf("SCC:\n");
    for(i = 0; i < 3; i++) {
    printf("%d\n", scc_list[i]);
}*/


return 0;


}
