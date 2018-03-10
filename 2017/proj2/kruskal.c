/****************************************************************************/
/*                                                                          */
/*							  2 Projecto ASA								*/
/*																			*/
/*						Joao Miguel Campos, 75785							*/
/*						 Daniela Rodrigues, 84919							*/
/*																			*/
/*						   2016/2017 - 2 Semestre							*/
/*																			*/
/****************************************************************************/


#include <stdio.h>
#include <stdlib.h>

typedef struct edge{

	int id;
	int custo;
	int parent;

} Edge;

typedef struct set{
	int parent;
	int rank;
} Subset;


int numEdges;
int maxCidade;
int maxAeroporto;
int maxEstradas;

int custo_total;
int num_aero;
int num_roads;

int cont; /*conta o numero cidades ja contabilizados */



void makeSubSet(int v, Subset ptrSubsets[maxCidade + 1]) {

	ptrSubsets[v].parent = v;
	ptrSubsets[v].rank = 0;
}

int qcmp(const void *p, const void *q)  {

	Edge x = *((Edge const *) p);

	Edge y = *((Edge const *) q);

	if( x.custo == y.custo) {
		if(x.parent != maxCidade + 1) {
			return -1;
		}

		else {
			return 1;
		}
	}

	return (x.custo - y.custo);
}

int findSet(int i, Subset ptrSubsets[maxCidade + 1]) {

	if(i != ptrSubsets[i].parent) {
		ptrSubsets[i].parent = findSet(ptrSubsets[i].parent, ptrSubsets);
	}

	return ptrSubsets[i].parent;
}

void linkSet(int src, int dest, Subset ptrSubsets[maxCidade + 1]) {

	int src_raiz = findSet(src, ptrSubsets);
	int dest_raiz = findSet(dest, ptrSubsets);

	if(ptrSubsets[src_raiz].rank < ptrSubsets[dest_raiz].rank) {
		ptrSubsets[src_raiz].parent = dest_raiz;
	}

	else if(ptrSubsets[src_raiz].rank > ptrSubsets[dest_raiz].rank) {
		ptrSubsets[dest_raiz].parent = src_raiz;
	}

	else {
		ptrSubsets[dest_raiz].parent = src_raiz;
		ptrSubsets[src_raiz].rank++;
	}
}

Edge *kruskal(Edge *ptr) {

	int i;
	int src, dest;
	cont = 0;

	custo_total = 0;
	num_aero = 0;
	num_roads = 0;

	Subset ptrSubsets[maxCidade + 1];

	for(i = 0; i <= maxCidade; i++) {
		makeSubSet(i+1, ptrSubsets);
	}

	i = 0;

	while(cont < maxCidade) {

		if(i >= numEdges) {
			return ptr;
		}

		src = findSet(ptr[i].parent, ptrSubsets);

		dest = findSet(ptr[i].id, ptrSubsets);

		if(src != dest) {

			custo_total += ptr[i].custo;

			if(ptr[i].parent == maxCidade + 1) {
				num_aero++;
			}

			else {
				num_roads++;
			}

			linkSet(src, dest, ptrSubsets);
			cont++;
			i++;
		}

		else {

			i++;
		}
	}
	return ptr;
}



Edge *kruskalRoads(Edge *ptr) {

	int i;
	int src, dest;
	cont = 0;

	custo_total = 0;
	num_aero = 0;
	num_roads = 0;

	Subset ptrSubsets[maxCidade + 1];


	for(i = 0; i <= maxCidade; i++) {
		makeSubSet(i+1, ptrSubsets);
	}

	i = 0;

	while(cont < maxCidade - 1) {

		if(i >= maxEstradas) {
			return ptr;

		}

		src = findSet(ptr[i].parent, ptrSubsets);

		dest = findSet(ptr[i].id, ptrSubsets);

		if(src != dest) {

			custo_total += ptr[i].custo;

			num_roads++;

			linkSet(src, dest, ptrSubsets);
			cont++;
			i++;
		}

		else {
			i++;
		}
	}

	return ptr;
}



int main() {

	int i;
	int aeroporto_id, custo_aero;
	int cidadeA;
	int cidadeB;
	int custoEstradaAB;
	int maxcost, num_aer_aux, num_roads_aux, cont_aux;


	scanf("%d", &maxCidade);
	scanf("%d", &maxAeroporto);


	/****************   CRIACAO DO GRAFO   ****************/

	/*criacao de um vector que vai guardar as informacoes das edges que sao de aeroportos */
	Edge *ptrEdgesAero = (Edge *) malloc(sizeof(Edge) * maxAeroporto);


	/* leitura e alteracao dos dados respectivos as ligacoes que incluem aeroportos */
	for(i = 0; i < maxAeroporto; i++) {
		scanf("%d %d", &aeroporto_id, &custo_aero);

		ptrEdgesAero[i].id = aeroporto_id;
		ptrEdgesAero[i].custo = custo_aero;
		ptrEdgesAero[i].parent = maxCidade + 1;
	}

	scanf("%d", &maxEstradas);

	/*criacao de um vector que vai guardar as edges que apenas incluem estradas */
	Edge *ptrEdgesSemAero = (Edge *) malloc(sizeof(Edge) * maxEstradas);

	/* numero maximo de edges do grafo*/
	numEdges = maxAeroporto + maxEstradas;

	/*criacao de ponteiro para o vector que vai guardar o numero total de edges e as suas informacoes */
	Edge *ptrEdges = (Edge *) malloc(sizeof(Edge) * numEdges);

	/* inicializacao dos valores recebidos para as ligacoes que incluem estradas */
	cidadeA = -1;
	cidadeB = -1;
	custoEstradaAB = -1;

	for(i = 0; i < maxEstradas; i++) {
		scanf("%d %d %d", &cidadeA, &cidadeB, &custoEstradaAB);

		ptrEdgesSemAero[i].id = cidadeB;
		ptrEdgesSemAero[i].custo = custoEstradaAB;
		ptrEdgesSemAero[i].parent = cidadeA;
	}


	for(i = 0; i < numEdges; i++) {
		if(i <= maxAeroporto - 1) {
			ptrEdges[i].id = ptrEdgesAero[i].id;
			ptrEdges[i].parent = ptrEdgesAero[i].parent;
			ptrEdges[i].custo = ptrEdgesAero[i].custo;
		}

		else if(i >= maxAeroporto) {
			ptrEdges[i].id = ptrEdgesSemAero[i - maxAeroporto].id;
			ptrEdges[i].parent = ptrEdgesSemAero[i - maxAeroporto].parent;
			ptrEdges[i].custo = ptrEdgesSemAero[i - maxAeroporto].custo;
		}
	}

	qsort(ptrEdges, numEdges, sizeof(Edge), qcmp);

	kruskal(ptrEdges);

	maxcost = custo_total;
	num_aer_aux = num_aero;
	num_roads_aux = num_roads;
	cont_aux = cont;


	qsort(ptrEdgesSemAero, maxEstradas, sizeof(Edge), qcmp);

	kruskalRoads(ptrEdgesSemAero);


	if(cont_aux < maxCidade && cont < maxCidade - 1) {
		printf("Insuficiente\n");
		return 0;
	}

	else if(cont < maxCidade - 1) {

		printf("%d\n%d %d\n", maxcost, num_aer_aux, num_roads_aux);
	}

	else {

		if(custo_total <= maxcost) {
			printf("%d\n%d %d\n", custo_total, num_aero, num_roads);
		}

		else {
			printf("%d\n%d %d\n", maxcost, num_aer_aux, num_roads_aux);
		}

	}

	return 0;
}
