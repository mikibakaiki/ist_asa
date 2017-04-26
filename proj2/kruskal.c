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


Edge *ptrEdges;
Subset *subsets;
int numEdges;
int maxCidade;
int maxAeroporto;

void makeSubSet(int v) {
	subsets[v].parent = v;
	subsets[v].rank = 0;
}

/*Edge new(int i, int id, int custo, int parent) {

	ptrEdges[i].id = id;
	ptrEdges[i].custo = custo;
	ptrEdges[i].parent = parent;

	return ptrEdges[i];
}*/

int qcmp(const void *p, const void *q)  {
	/* O qcmp passa ponteiros para as posicoes e nao os valores
	* Assim, temos que por o ponteiro a apontar para cidade e depois, desreferenciamo-lo*/

	Edge x = *((Edge const *) p);

	Edge y = *((Edge const *) q);

	if( x.custo == y.custo) {
		if(x.parent != maxCidade+1)
			return 1;
		else
			return -2;

	}
	return (x.custo - y.custo);
}


int main() {

	int i;

	scanf("%d", &maxCidade);
	scanf("%d", &maxAeroporto);

	numEdges = maxCidade + maxAeroporto;
	/****************   CRIACAO DO GRAFO   ****************/

	ptrEdges = (Edge *) malloc(sizeof(Edge));
	subsets = (Subset *) malloc(sizeof(Subset));

	Edge edges[numEdges];
	ptrEdges = edges;

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

	return 0;
}
