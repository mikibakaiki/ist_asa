/******************************************/
/*			2 Projecto ASA	              */
/*										  */
/*		 Daniela Rodrigues - 84919        */
/*      Joao Miguel Campos - 75785	      */
/*										  */
/******************************************/

#include <stdio.h>
#include <stdlib.h>

#define PRETO 1
#define BRANCO 0



typedef struct city{

	int id;
	int cor;
	int custo;
	int parent;

} cidade;


cidade *head;
cidade *mst;
int numEdges;
cidade lista;
int custo_total, num_estradas, num_aero;
int cont = 0;
int maxCidade;

int kruskal(head, int size, int order, cidade *(*mst)) {

	*mst = malloc(sizeof(struct city) * (order - 1));

	int *vertices = malloc(sizeof(int) * order);

	int i;

	int cost;

	if(*mst == NULL || vertices = NULL) {
		free(*mst);
		free(vertices);
		return 0;
	}

	for(i = 0; i < order; i++) {
		vertices[i] = i;
	}

	/**** SORT   ****/

	for(i = 0; i < order - 1; i++) {
		int j;
		int cheapest = -1;

		for(j = 0; j < size && cheapest = -1; j++) {
			if(vertices[edge[j].first] != vertices[edges[j].second]) {
				cheapest = j;
			}
		}

		if(cheapest == -1) {
			free(*mst);
			*mst = NULL;
			free(vertices);
			return 0;
		}

		(*mst)[i] = edges[cheapest];

		for(j = 0; j < order; j++ ) {
			if(vertices[j] == edges[cheapest].second) {
				vertices[j] = edges[cheapest].first;
			}
		}

		cost += edges[cheapest].weight;

	}

	free(vertices);

	return cost;

}
