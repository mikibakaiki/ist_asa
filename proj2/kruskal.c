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

	long long int id;
	long long int custo;
	long long int parent;

} Edge;


typedef struct set{
	long long int parent;
	long long int rank;
} Subset;


Edge *ptrEdges;
Subset *ptrSubsets;
Edge *ptrEdgesSemAero;
Edge *ptrResultado;

long long int numEdges;
long long int maxCidade;
long long int maxAeroporto;

long long int custo_total;
long long int num_aero;
long long int num_roads;


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

	ptrEdges = (Edge *) malloc(sizeof(Edge) * numEdges);
	ptrSubsets = (Subset *) malloc(sizeof(Subset) * maxCidade + 1);
	ptrResultado = (Edge *) malloc(sizeof(Edge) * maxCidade);
	ptrEdgesSemAero = (Edge *) malloc(sizeof(Edge) * numEdges);

	Edge edges[numEdges];
	printf("\n\n\n --- NUM EDGES = %d\n\n\n", numEdges);
	ptrEdges = edges;

	Subset conjuntos[maxCidade + 1];
	ptrSubsets = conjuntos;

	Edge resultado[maxCidade];
	ptrResultado = resultado;

	for(i = 0; i < numEdges; i++) {
		ptrEdges[i].parent = -1;
		ptrEdges[i].id = -1;
		ptrEdges[i].custo = -1;
	}

	for(i = 0; i < maxCidade; i++) {
		ptrResultado[i].parent = -1;
		ptrResultado[i].id = -1;
		ptrResultado[i].custo = 0;
	}

	/* a posicao i = maxCidade sera o vertice extra, sky, que e comum a todas as cidades que tiverem aeroporto */

	int aeroporto_id, custo_aero;
	int max_cost = 0;

	for(i = 0; i < maxAeroporto; i++){
		scanf("%d %d", &aeroporto_id, &custo_aero);

		if(custo_aero > max_cost) {
			max_cost = custo_aero;
		}

		edges[i].id = aeroporto_id;
		ptrEdges[i].custo = custo_aero;
		ptrEdges[i].parent = maxCidade + 1;

		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);
	}

	int maxEstradas, cidadeA, cidadeB, custoEstradaAB;

	scanf("%d", &maxEstradas);

	numEdges = maxAeroporto + maxEstradas;

	/*printf(" maxEstradas %d\n", maxEstradas);*/

	for(i = maxAeroporto; i < (maxAeroporto + maxEstradas); i++) {
		scanf("%d %d %d", &cidadeA, &cidadeB, &custoEstradaAB);

		if(custoEstradaAB > max_cost) {
			max_cost = custoEstradaAB;
		}

		ptrEdges[i].id = cidadeB;
		ptrEdges[i].custo = custoEstradaAB;
		ptrEdges[i].parent = cidadeA;

		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);
	}

	/****************   COLOCAR TUDO NUM VECTOR ORDENADO   ****************/

	for(i = 0; i < numEdges; i++) {
		if(ptrEdges[i].parent == -1 && ptrEdges[i].id ==-1) {

			ptrEdges[i].custo = max_cost+1;
		}
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

	ptrEdgesSemAero = ptrEdges;

	qsort(ptrEdgesSemAero, numEdges, sizeof(Edge), cmpWithoutAer);

	printf("\n ---  VECTOR ORDENADO POR PESOS SEM AERO   ---\n\n");

	for(i = 0; i < numEdges; i++) {
		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);

	}



	printf("%d\n%d %d\n", custo_total, num_aero, num_roads);

	return 0;
}
