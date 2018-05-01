#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

#define SOURCE -1
#define SINK -2
#define TRUE -5
#define FALSE -6

typedef struct edge {
    int u;
    int v;
    int cap;
    int flow;

} Edge;

typedef struct pixel {
    int id;
    int visited;
    int i;
    int j;
    std::vector<Edge> edgeList;

} Pixel;

/*A structure to represent a stack*/
typedef struct StackNode {
    int data;
    struct StackNode* next;
} *Stack;


/*    VARIAVEIS GLOBAIS     */
int numPixels;
Pixel *head;
int maxFlow;
/* Stack to keep vertex */
Stack pixelStack = NULL;

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

void scanInput() {

    int numLinhas;
    int numColunas;
    int i, j;
    int auxCont = 1;
    int sourceCap;
    int toSinkCap;
    int vertexHor;
    int vertexVer;

    scanf("%d %d", &numLinhas, &numColunas);

    numPixels = numLinhas * numColunas;
    head = (Pixel *) malloc(sizeof(struct pixel) * (numPixels + 2));
    head[0].id = SOURCE;                // A primeira posicao de head e o vertice S - source
    head[0].i = head[0].j = -1;
    head[numPixels + 1].id = SINK;      // A ultima posicao de head e o vertice T - sink
    head[numPixels + 1].i = head[numPixels + 1].j = -2;
    scanf("\n");

    // scan for the first matrix - edges from source vertex S to all vertex x
    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas; j++) {
            scanf("%d", &sourceCap);
            head[auxCont].id = auxCont - 1;
            head[auxCont].i = i;
            head[auxCont].j = j;
            Edge e;
            e.u = SOURCE;
            e.v = head[auxCont].id;
            e.cap = sourceCap;
            head[auxCont].edgeList.push_back(e);
            auxCont++;
            scanf(" ");
        }
        scanf("\n");
    }

    scanf("\n");

    auxCont = 1;

    // scan for the second matrix - edges from all vertex x to sink vertex T
    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas; j++) {
            scanf("%d", &toSinkCap);
            Edge e;
            e.u = head[auxCont].id;
            e.v = SINK;
            e.cap = toSinkCap;
            head[auxCont].edgeList.push_back(e);


            auxCont++;
            scanf(" ");
        }
        scanf("\n");
    }

    scanf("\n");
    auxCont = 1;
    // horizontal edges, working

    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas - 1; j++) {
            scanf("%d", &vertexHor);
            Edge e;
            e.u = head[auxCont].id;
            auxCont++;
            e.v = head[auxCont].id;
            e.cap = vertexHor;
            head[auxCont - 1].edgeList.push_back(e);

            //adding to the vertex v, but swaping the u for v and vice versa
            e.u = head[auxCont].id;
            e.v = head[auxCont - 1].id;
            e.cap = vertexHor;
            head[auxCont].edgeList.push_back(e);
            scanf(" ");
        }
        scanf("\n");
        auxCont++;
    }

    scanf("\n");
    auxCont = 1;

    // vertical edges, works!
    for(i = 0; i < numLinhas - 1; i++) {
        for(j = 0; j < numColunas; j++) {
            scanf("%d", &vertexVer);
            Edge e;
            e.u = head[auxCont].id;
            e.v = head[auxCont + numColunas].id;
            e.cap = vertexVer;
            head[auxCont].edgeList.push_back(e);

            //adding to the vertex v, but swaping the u for v and vice versa
            e.u = head[auxCont + numColunas].id;
            e.v = head[auxCont].id;
            e.cap = vertexVer;
            head[auxCont + numColunas].edgeList.push_back(e);
            auxCont++;
            scanf(" ");
        }
        scanf("\n");
    }
}

/* tenho que passar os id's + 1 de cada vertice */

void BFS(int vertex) {
    push(&pixelStack, vertex);
    while(isEmpty != NULL) {
        int v = pop(&pixelStack);
        if(head[v].visited == FALSE) {
            head[v].visited = TRUE;
            for(Edge e : head[v].edgeList) {
                if(head[e.v + 1].visited == FALSE) {
                    push(&pixelStack, e.v + 1);
                }
            }
        }
    }
}




int main() {
    maxFlow = 0;

    scanInput();

    printf("Hello Worold\n");
    return 0;

}
