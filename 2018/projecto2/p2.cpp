#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>

#define SOURCE -1
#define SINK -2
#define TRUE -5
#define FALSE -6


/* Para compilar : g++ -ansi -g -std=c++11 -Wall p2.cpp -o test */

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


/*    VARIAVEIS GLOBAIS     */
int numPixels;
Pixel *head;
int maxFlow;
std::vector<int> parentPixel;
std::vector<int> currentPathCapacity;

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

    head[0].id = SOURCE;         // A primeira posicao de head e o vertice S - source
    head[0].i = head[0].j = -1;

    head[numPixels + 1].id = SINK;  // A ultima posicao de head e o vertice T - sink
    head[numPixels + 1].i = head[numPixels + 1].j = -2;

    for (i = 0; i < numPixels + 2; ++i) {
        parentPixel.push_back(-2);
        currentPathCapacity.push_back(0);
    }

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
            head[0].edgeList.push_back(e);

            e.u = head[auxCont].id;
            e.v = SOURCE;
            e.cap = sourceCap;          //TODO aqui talvez seja 0, porque e residual edge
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
            e.u = numPixels;
            e.v = head[auxCont].id;
            e.cap = toSinkCap;
            head[numPixels + 1].edgeList.push_back(e);

            e.u = head[auxCont].id;
            e.v = numPixels;
            e.cap = toSinkCap;              //TODO aqui talvez seja 0, porque e residual edge
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
/* ou seja, a posicao no vector head[]*/

void deleteFull() {
    int i, j = 0;
    for(j = 0; j < numPixels + 2; j++) {
        for(i = 0; i < (int) head[j].edgeList.size(); i++) {
            Edge e = head[j].edgeList[i];
            if(e.cap == 0) {
                int u = e.u;
                int v = e.v;

                head[j].edgeList.erase(head[j].edgeList.begin() + i);
                head[v + 1].edgeList.erase(head[v + 1].edgeList.begin())
            }
        }
    }
}


int BFS(int start, int end) {

    std::queue<int> q;
    q.push(start);
    parentPixel[start] = -1;
    currentPathCapacity[start] = INT_MAX;

    while(!q.empty()) {
        int currentPixel = q.front();
        q.pop();

        for(Edge e : head[currentPixel].edgeList) {
            if(parentPixel[e.v + 1] == -2 && e.cap > 0) {
                parentPixel[e.v + 1] = currentPixel;
                currentPathCapacity[e.v + 1] = std::min(currentPathCapacity[currentPixel], (e.cap));

                if(e.v + 1 == end) {
                    return currentPathCapacity[end];
                }

                q.push(e.v + 1);
            }
        }
    }
    return 0;
}


int EdmondsKarp(int start, int end) {
    int flow = 0;
    while(true) {
        int aux_flow = BFS(start, end);

        if(aux_flow == 0) {
            break;
        }

        flow += aux_flow;

        int currentPixel = end;

        while(currentPixel != start) {
            int previousPixel = parentPixel[currentPixel];
            for(Edge e : head[previousPixel].edgeList) {
                if(e.v == currentPixel - 1 && e.cap > 0) {
                    // e.flow += aux_flow;
                    e.cap -= aux_flow;
                    // head[e.v + 1].edgeList
                }
                // if(e.v == previousPixel - 1 && e.cap > 0) {
                //     e.cap -= aux_flow;
                // }
            }
            currentPixel = previousPixel;
        }
        deleteFull();
    }

    return flow;
}


int main() {
    maxFlow = 0;

    scanInput();
    maxFlow = EdmondsKarp(0, numPixels + 1);
    printf("Hello Worold\n");

    printf("MAX FLUX : %d\n", maxFlow);
    return 0;

}
