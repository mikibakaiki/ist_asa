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
#define PLANO -5
#define CENARIO -6


/* Para compilar : g++ -ansi -g -std=c++11 -Wall p2.cpp -o test */

typedef struct edge {
    int u;
    int v;
    int cap;
    int flow;

} Edge;

typedef struct pixel {
    int id;
    int plano;
    int cenario;
    std::vector<Edge> edgeList;

} Pixel;


/*    VARIAVEIS GLOBAIS     */
int numPixels;
Pixel *head;
int maxFlow;
std::vector<int> parentPixel;
std::vector<int> currentPathCapacity;
int numLinhas;
int numColunas;


void scanInput() {

    int i, j;
    int auxCont = 1;
    int sourceCap;
    int toSinkCap;
    int vertexHor;
    int vertexVer;

    scanf("%d", &numLinhas);

    scanf("%d", &numColunas);

    numPixels = numLinhas * numColunas;
    head = (Pixel *) malloc(sizeof(struct pixel) * (numPixels + 2));

    head[0].id = SOURCE;         // A primeira posicao de head e o vertice S - source

    head[numPixels + 1].id = SINK;  // A ultima posicao de head e o vertice T - sink
    

    // scan for the first matrix - edges from source vertex S to all vertex x
    for(i = 0; i < numLinhas; i++) {
        
        for(j = 0; j < numColunas; j++) {
            
            scanf("%d", &sourceCap);
            head[auxCont].id = auxCont - 1;
            head[auxCont].plano = sourceCap;
            auxCont++;
        }
    }

    auxCont = 1;

    // scan for the second matrix - edges from all vertex x to sink vertex T
   
    for(i = 0; i < numLinhas; i++) {
        for(j = 0; j < numColunas; j++) {
            
            scanf("%d", &toSinkCap);
            head[auxCont].cenario = toSinkCap;
            auxCont++;
        }
    }
            
    for(i = 1; i < numPixels + 1; i++) {
        if(head[i].plano != 0 && head[i].cenario != 0) {
            if(head[i].plano < head[i].cenario) {
                maxFlow += head[i].plano;
                head[i].cenario -= head[i].plano;
                head[i].plano = 0;
            }
            else {
                maxFlow += head[i].cenario;
                head[i].plano -= head[i].cenario;
                head[i].cenario = 0;
            }
        }
        
        if(head[i].plano != 0) {
            Edge e;

            e.u = SOURCE;
            e.v = head[i].id;
            e.cap = head[i].plano;
            head[0].edgeList.push_back(e);

            e.u = head[i].id;
            e.v = SOURCE;
            e.cap = head[i].plano;
            head[i].edgeList.push_back(e);
        }

        if(head[i].cenario != 0) {
            Edge e;

            e.u = numPixels;
            e.v = head[i].id;
            e.cap = head[i].cenario;
            head[numPixels + 1].edgeList.push_back(e);

            e.u = head[i].id;
            e.v = numPixels;
            e.cap = head[i].cenario;             
            head[i].edgeList.push_back(e);
        }
    }


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
    }
}

void decreaseCap(int u, int currentPixel, int flow) {
    int i;
    for(i = 0; i < (int) head[u].edgeList.size(); i++) {
        if(head[u].edgeList[i].v == currentPixel - 1 && head[u].edgeList[i].cap > 0) {
            head[u].edgeList[i].cap -= flow;
        }
    }
    for(i = 0; i < (int) head[currentPixel].edgeList.size(); i++) {
        if(head[currentPixel].edgeList[i].v == u - 1 && head[currentPixel].edgeList[i].cap > 0) {

            head[currentPixel].edgeList[i].cap -= flow;
        }
    }
}

/* tenho que passar os id's + 1 de cada vertice */
/* ou seja, a posicao no vector head[]*/
int BFSKarp(int start, int end) {
    currentPathCapacity.clear();
    parentPixel.clear();

    int i;
    for (i = 0; i < numPixels + 2; ++i) {
        parentPixel.push_back(-2);
        currentPathCapacity.push_back(0);
    }

    std::queue<int> q;
    q.push(start);
    parentPixel[start] = -1;
    currentPathCapacity[start] = INT_MAX;

    while(!q.empty()) {
        int currentPixel = q.front();
        q.pop();

        for(Edge e : head[currentPixel].edgeList) {
            if(e.cap == 0) {
                continue;
            }
            else if(parentPixel[e.v + 1] == -2 && e.cap > 0) {
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
        int aux_flow = BFSKarp(start, end);

        if(aux_flow == 0) {
            break;
        }

        flow += aux_flow;

        int currentPixel = end;

        while(currentPixel != start) {
            int previousPixel = parentPixel[currentPixel];
            decreaseCap(previousPixel, currentPixel, aux_flow);
            currentPixel = previousPixel;
        }
    }

    return flow;
}


int main() {
    maxFlow = 0;
    int i;
    int j = 0;

    scanInput();
    maxFlow += EdmondsKarp(0, numPixels + 1);

    printf("%d\n\n", maxFlow);
    BFSKarp(0, numPixels + 1);

    for(i = 1; i < (int) parentPixel.size() - 1; i++) {
        j++;

        if (j == numColunas + 1) {
            printf("\n");
            j = 0;
            i--;
        }

        else if(parentPixel[i] == -2) {
            printf("P ");
        }

        else if (parentPixel[i] != -2)  {
            printf("C ");
        }
    }

    printf("\n");
    

    return 0;

}
