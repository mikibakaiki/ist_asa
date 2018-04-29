#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

#define SOURCE -1
#define SINK -2

typedef struct edge {
    int u;
    int v;
    int cap;
    int flow;

} Edge;

typedef struct pixel {
    int id;
    int i;
    int j;
    std::vector<Edge> edgeList;

} Pixel;

/*    VARIAVEIS GLOBAIS     */
int numPixels;
Pixel *head;



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




int main() {

    scanInput();

    printf("Hello Worold\n");
    return 0;

}
