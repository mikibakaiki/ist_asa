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
Edge *ptrResultado;
int numEdges;
int maxCidade;
int maxAeroporto;


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
		if(x.parent != maxCidade+1)
		return -1;
		else
		return 1;

	}
	return (x.custo - y.custo);
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

	for(i = 0; i < maxCidade + 1; i++) {

		int src = findSet(ptrEdges[i].parent);
		int dest = findSet(ptrEdges[i].id);

		if(src != dest) {
			ptrResultado[cont].id = ptrEdges[i].id;
			printf("\nptrResultado[%d].id = %d\n", cont, ptrEdges[i].id);

			ptrResultado[cont].parent = ptrEdges[i].parent;
			printf("ptrResultado[%d].parent = %d\n", cont, ptrEdges[i].parent);

			ptrResultado[cont].custo = ptrEdges[i].custo;
			printf("ptrResultado[%d].custo = %d\n", cont, ptrEdges[i].custo);
			cont++;
			linkSet(src, dest);
		}
	}
}

int main() {

	int i;

	scanf("%d", &maxCidade);
	scanf("%d", &maxAeroporto);

	numEdges = maxCidade + maxAeroporto;


	/****************   CRIACAO DO GRAFO   ****************/

	ptrEdges = (Edge *) malloc(sizeof(Edge) * numEdges);
	ptrSubsets = (Subset *) malloc(sizeof(Subset) * maxCidade + 1);
	ptrResultado = (Edge *) malloc(sizeof(Edge) * maxCidade);

	Edge edges[numEdges];
	ptrEdges = edges;

	Subset conjuntos[maxCidade + 1];
	ptrSubsets = conjuntos;

	Edge resultado[maxCidade];
	ptrResultado = resultado;

	/* a posicao i = maxCidade sera o vertice extra, sky, que e comum a todas as cidades que tiverem aeroporto */

	int aeroporto_id, custo_aero;

	for(i = 0; i < maxAeroporto; i++){
		scanf("%d %d", &aeroporto_id, &custo_aero);

		edges[i].id = aeroporto_id;
		ptrEdges[i].custo = custo_aero;
		ptrEdges[i].parent = maxCidade + 1;

		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);
	}

	int maxEstradas, cidadeA, cidadeB, custoEstradaAB;

	scanf("%d", &maxEstradas);

	/*printf(" maxEstradas %d\n", maxEstradas);*/

	for(i = maxAeroporto; i < (maxAeroporto + maxEstradas); i++) {
		scanf("%d %d %d", &cidadeA, &cidadeB, &custoEstradaAB);

		ptrEdges[i].id = cidadeB;
		ptrEdges[i].custo = custoEstradaAB;
		ptrEdges[i].parent = cidadeA;

		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);
	}

	/****************   COLOCAR TUDO NUM VECTOR ORDENADO   ****************/



	qsort(ptrEdges, numEdges, sizeof(Edge), qcmp);

	printf("\n ---  VECTOR ORDENADO POR PESOS   ---\n\n");

	for(i = 0; i < numEdges; i++) {
		printf("ptrEdges[%d] = parent: %d id: %d Custo = %d\n", i, ptrEdges[i].parent, ptrEdges[i].id, ptrEdges[i].custo);

	}

	kruskal();
	int custo_total = 0;
	int num_aero = 0;
	int num_roads = 0;

	printf("\n\n------   VERTICES / EDGES ESCOLHIDOS   ------\n\n");
	for(i = 0; i < maxCidade; i++) {

		printf("[ parent = %d ; id = %d ; custo = %d ]\n", ptrResultado[i].parent, ptrResultado[i].id, ptrResultado[i].custo);

		custo_total += ptrResultado[i].custo;

		if(ptrResultado[i].parent == maxCidade + 1) {

			num_aero++;

		}

		else {

			num_roads++;
		}
	}

	printf("%d\n%d %d\n", custo_total, num_aero, num_roads);



	return 0;
}
