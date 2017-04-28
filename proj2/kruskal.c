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

/*valgrind -v --leak-check=full --show-leak-kinds=all --track-origins=yes ./a.out <input1.txt
*/


typedef struct edge{

	int id;
	int custo;
	int parent;

} Edge;


typedef struct set{
	int parent;
	int rank;
} Subset;


Edge *ptrEdges;
Subset *ptrSubsets;
Edge *ptrEdgesSemAero;
Edge *ptrEdgesAero;

int numEdges;
int maxCidade;
int maxAeroporto;

int custo_total;
int num_aero;
int num_roads;


void makeSubSet(int v) {
	ptrSubsets[v].parent = v;
	ptrSubsets[v].rank = 0;
	printf("\n ptrSubset[%d].parent = %d\n",v, ptrSubsets[v].parent);
	printf("ptrSubset[%d].rank = %d\n",v, ptrSubsets[v].rank);
}


int qcmp(const void *p, const void *q)  {
	/* O qcmp passa ponteiros para as posicoes e nao os valores
	* Assim, temos que por o ponteiro a apontar para cidade e depois, desreferenciamo-lo*/

	Edge x = *((Edge const *) p);

	Edge y = *((Edge const *) q);

	if( x.custo == y.custo) {
		if(x.parent != maxCidade+1) {
			return -1;
		}

		else {
			return 1;
		}
	}

	return (x.custo - y.custo);
}


int cmpWithoutAer(const void *p, const void *q) {

	Edge x = *((Edge const *) p);

	Edge y = *((Edge const *) q);

	// if(x.parent <= y.parent) {
	//
	// 	if(x.custo <= y.custo) {
	// 		return -1;
	// 	}
	//
	// 	else
	// }
	//
	// else{
	// 	return 1;
	// }

	return (x.parent < y.parent) - (x.custo < y.custo);
}

int findSet(int i) {

	printf("\nfindSet : i = %d\n", i);
	printf("findSet : ptrSubsets[%d].parent = %d\n", i, ptrSubsets[i].parent);

	if(i != ptrSubsets[i].parent) {
		ptrSubsets[i].parent = findSet(ptrSubsets[i].parent);
	}

	printf("\nfindSet : ptrSubsets[%d].parent = %d\n", i, ptrSubsets[i].parent);
	return ptrSubsets[i].parent;
}


void linkSet(int src, int dest) {

	int src_raiz = findSet(src);
	int dest_raiz = findSet(dest);

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

void kruskal() {

	int i;
	int cont = 0;

	for(i = 0; i <= maxCidade; i++) {

		makeSubSet(i+1);
	}

	for(i = 0; i < numEdges; i++) {

		int src = findSet(ptrEdges[i].parent);
		int dest = findSet(ptrEdges[i].id);

		if(src != dest) {

			custo_total += ptrEdges[i].custo;

			if(ptrEdges[cont].parent == maxCidade + 1) {
				num_aero++;
			}

			else {
				num_roads++;
			}
			cont++;
			linkSet(src, dest);

			if(cont == maxCidade) {
				break;
			}
		}
	}
}



int main() {

	int i;

	scanf("%d", &maxCidade);
	scanf("%d", &maxAeroporto);


	/****************   CRIACAO DO GRAFO   ****************/

	/*criacao de um vector que vai guardar as informacoes das edges que sao de aeroportos */
	ptrEdgesAero = (Edge *) malloc(sizeof(Edge) * maxAeroporto);

	Edge edges[maxAeroporto];
	ptrEdgesAero = edges;


	/*criacao de um vector que vai guardar o estado de cada subset */
	ptrSubsets = (Subset *) malloc(sizeof(Subset) * maxCidade + 1);

	Subset conjuntos[maxCidade + 1];
	ptrSubsets = conjuntos;

	/*inicializacao do vector que vai guardar as informacoes das edges dos aeroportos */
	for(i = 0; i < maxAeroporto; i++) {
		ptrEdgesAero[i].parent = -1;
		ptrEdgesAero[i].id = -1;
		ptrEdgesAero[i].custo = -1;
	}

	int aeroporto_id, custo_aero;

	/* leitura e alteracao dos dados respectivos as ligacoes que incluem aeroportos */
	for(i = 0; i < maxAeroporto; i++) {
		scanf("%d %d", &aeroporto_id, &custo_aero);

		ptrEdgesAero[i].id = aeroporto_id;
		ptrEdgesAero[i].custo = custo_aero;
		ptrEdgesAero[i].parent = maxCidade + 1;

		printf("ptrEdgesAero[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdgesAero[i].parent, ptrEdgesAero[i].id, ptrEdgesAero[i].custo);
	}



	int maxEstradas, cidadeA, cidadeB, custoEstradaAB;

	scanf("%d", &maxEstradas);

	/*ciracao de um vector que vai guardar as edges que apenas incluem estradas */
	ptrEdgesSemAero = (Edge *) malloc(sizeof(Edge) * maxEstradas);

	Edge edgesSemAero[maxEstradas];
	ptrEdgesSemAero = edgesSemAero;


	/* numero maximo de edges do grafo*/
	numEdges = maxAeroporto + maxEstradas;


	/*criacao de ponteiro para o vector que vai guardar o numero total de edges e as suas informacoes */
	ptrEdges = (Edge *) malloc(sizeof(Edge) * numEdges);

	Edge totalEdges[numEdges];
	ptrEdges = totalEdges;

	/* inicializacao dos valores recebidos para as ligacoes que incluem estradas */

	for(i = 0; i < maxEstradas; i++) {
		scanf("%d %d %d", &cidadeA, &cidadeB, &custoEstradaAB);

		ptrEdgesSemAero[i].id = cidadeB;
		ptrEdgesSemAero[i].custo = custoEstradaAB;
		ptrEdgesSemAero[i].parent = cidadeA;

		printf("ptrEdgesSemAero[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdgesSemAero[i].parent, ptrEdgesSemAero[i].id, ptrEdgesSemAero[i].custo);
	}

	/*incializacao do vector que guarda a informacao total do grafo*/

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



	/****************   COLOCAR TUDO NUM VECTOR ORDENADO   ****************/

	printf("\n ---  VECTOR DESORDENADO   ---\n\n");

	for(i = 0; i < numEdges; i++) {
		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);

	}


	qsort(ptrEdges, numEdges, sizeof(Edge), qcmp);

	printf("\n ---  VECTOR ORDENADO POR PESOS   ---\n\n");

	for(i = 0; i < numEdges; i++) {
		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);

	}

	custo_total = 0;
	num_aero = 0;
	num_roads = 0;

	kruskal();

	// ptrEdgesSemAero = ptrEdges;
	//
	// qsort(ptrEdgesSemAero, numEdges, sizeof(Edge), cmpWithoutAer);
	//
	// printf("\n ---  VECTOR ORDENADO POR PESOS SEM AERO   ---\n\n");
	//
	// for(i = 0; i < numEdges; i++) {
	// 	printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);
	//
	// }



	printf("%d\n%d %d\n", custo_total, num_aero, num_roads);

	return 0;
}
