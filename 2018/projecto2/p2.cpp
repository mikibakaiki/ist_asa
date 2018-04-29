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
    std::list<Edge> edgeList;

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

    scanf("%d %d", &numLinhas, &numColunas);

    numPixels = numLinhas * numColunas + 2;
    head = malloc(sizeof(struct pixel) * numPixels);

    head[0].id = SOURCE;                // A primeira posicao de head e o vertice S - source
    head[numPixels - 1].id = SINK;      // A ultima posicao de head e o vertice T - sink

    for(i = 1; i < numPixels - 1; i++) {
        head[i].id = i-1;
    }
    scanf("\n");

    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas; j++) {
            scanf("%d ", sourceCap);
            Edge e;
            e.u = SOURCE;
            e.v = head[auxCont].id;
            e.cap = sourceCap;
            head[auxCont].edgeList.push_back(e);
            auxCont++;
        }
    }

    scanf("\n");
    auxCont = 1;
    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas; j++) {
            scanf("%d ", toSinkCap);
            Edge e;
            e.u = head[auxCont].id;
            e.v = SINK;
            e.cap = toSinkCap;
            head[auxCont].edgeList.push_back(e);
            auxCont++;
        }
    }
}




int main() {



}
