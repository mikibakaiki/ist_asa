/******************************************/
/*			2 Projecto ASA	              */
/*										  */
/*		 Daniela Rodrigues - 84919        */
/*      Joao Miguel Campos - 75785	      */
/*										  */
/******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define PRETO 1
#define BRANCO 0



typedef struct city{

	int id;
	int cor;
	int custo;
	int parent;
	struct city *next;

} *cidade;


cidade* grafo;
int numEdges;
cidade *lista;
int custo_total, num_estradas, num_aero;
int cont = 0;
int maxCidade;



/*---------------------------------   FUNCOES    -----------------------------------------------*/


cidade new(int id, int custo, int parent) {

	cidade city = (cidade) malloc(sizeof(struct city));

	city->id = id;
	city->custo = custo;
	city->cor = BRANCO;
	city->parent = parent;
	city->next = NULL;

	return city;
}

cidade insertEnd(cidade grafo, int id, int custo, int parent) {

	cidade x;

	if(grafo == NULL) {
		/*printf("head e null\n");*/
		return new(id, custo, parent);
	}

	for(x = grafo; x->next != NULL; x = x->next);

	x->next = new(id, custo, parent);

	return grafo;
}


int countEdges(cidade list) {

	cidade aux = list;
	int count = 0;

	while(aux != NULL) {

		count ++;
		aux = aux->next;
	}

	return count;
}


void put2vector( cidade *grafo, cidade *lista, int maxCidade) {
	/*printf("entrei na funcao put2vector\n");*/

	int i, j = 0;

	for(i = 0; i <= maxCidade; i++) {
		/*printf("dentro do primeiro for\n");*/

		cidade aux = grafo[i];

		while(aux != NULL) {
			/*printf("dentro do while\n");*/

			lista[j] = aux;
			j++;
			aux = aux->next;
		}
	}

	/*printf("sai da funcao put2vector\n");*/

}

int qcmp(const void *p, const void *q)  {
	/* O qcmp passa ponteiros para as posicoes e nao os valores
	* Assim, temos que por o ponteiro a apontar para cidade e depois, desreferenciamo-lo*/

	cidade x = *((cidade const *) p);

	cidade y = *((cidade const *) q);

	return (x->custo - y->custo);
}

int existeEl(int confirmaCidades[], int value, int numEdges) {

	int i;

	for(i = 0; i < numEdges; i++) {

		if(confirmaCidades[i] == value) {

			return 1;
		}
	}

	return 0;
}


void escolha(int confirmaCidades[], int i, int numEdges){

	int id = existeEl(confirmaCidades, lista[i]->id ,numEdges);
	/*int parent = existeEl(confirmaCidades, lista[i]->parent ,numEdges);*/

	if(id == 0) {

		confirmaCidades[cont] = lista[i]->id;
		cont++;
		/*confirmaCidades[cont] = lista[i]->parent;
		cont++;*/


		custo_total += lista[i]->custo;

		if(lista[i]->parent == 5){
			num_aero++;
		}
		if(lista[i]->parent != 5){
			num_estradas++;
		}
	}
}


int output(int numEdges, int maxCidade) {
	/*printf("max cidade = %d\n", maxCidade);*/
	int confirmaCidades[numEdges];

	int i;

	for(i = 0; i < numEdges; i++) {
		confirmaCidades[i] = -1;
	}

	for(i = 0; i < numEdges; i++) {
		escolha(confirmaCidades, i, maxCidade);
	}

	if( (existeEl(confirmaCidades, -1, maxCidade)) == 1) {

		return 1;
	}
	/*printf("escolhidos\n");

	for(i = 0; i < maxCidade; i++) {
		printf(" - %d\n", confirmaCidades[i]);
	}*/

	return 0;
}


/*-------------------------    MAIN   ------------------------------------------- */

int main() {



	int maxCidade, maxAeroporto;
	int i;

	scanf("%d", &maxCidade);
	scanf("%d", &maxAeroporto);

	/****************   CRIACAO DO GRAFO   ****************/

	grafo = (cidade*) malloc(sizeof(cidade)*(maxCidade + 1));

	/* a posicao i = maxCidade sera o vertice extra, sky, que e comum a todas as cidades que tiverem aeroporto */

	for(i = 0; i <= maxCidade; i++) {
		grafo[i] = NULL;
		/*printf("head[%d]->NULL\n", i);*/
	}

	int aeroporto_id, custo_aero;

	for(i = 0; i < maxAeroporto; i++){
		scanf("%d %d", &aeroporto_id, &custo_aero);

		/*printf("aeroporto %d custoaero %d\n", aeroporto_id, custo_aero);*/

		grafo[maxCidade] = insertEnd(grafo[maxCidade], aeroporto_id, custo_aero, maxCidade+1);
		/*printf("grafo[%d] -> %d; Custo = %d\n", maxCidade, grafo[maxCidade]->id, grafo[maxCidade]->custo);*/
	}

	int maxEstradas, cidadeA, cidadeB, custoEstradaAB;

	scanf("%d", &maxEstradas);

	/*printf(" maxEstradas %d\n", maxEstradas);*/

	for(i = 0; i < maxEstradas; i++) {
		scanf("%d %d %d", &cidadeA, &cidadeB, &custoEstradaAB);

		grafo[cidadeA-1] = insertEnd(grafo[cidadeA-1], cidadeB, custoEstradaAB, cidadeA);

		/*printf("grafo[%d]->%d; Custo = %d\n\n", cidadeA-1, grafo[cidadeA-1]->id, grafo[cidadeA-1]->custo);*/
	}

	/****************   COLOCAR TUDO NUM VECTOR ORDENADO   ****************/

	/*clock_t begin = clock();*/

	for(i = 0; i <= maxCidade; i++) {
		numEdges = countEdges(grafo[i]) + numEdges;
	}
	/*int numEdges = 0;
	numEdges = maxCidade + maxAeroporto;*/

	/*printf("Numero total de vertices do grafo: %d\n", numEdges);*/

	lista = (cidade *) malloc(sizeof(cidade) * numEdges);

	put2vector(grafo, lista, maxCidade);

	for(i = 0; i < numEdges; i++) {
		/*printf("Id da posicao %d da lista: %d\n custo: %d\n", i, lista[i]->id, lista[i]->custo);*/
	}

	qsort(lista, numEdges, sizeof(cidade), qcmp);

	/*printf("\n ---  VECTOR ORDENADO POR PESOS   ---\n\n");

	for(i = 0; i < numEdges; i++) {
		printf("lista[%d] = [id = %d , custo: %d , parent: %d]\n", i, lista[i]->id, lista[i]->custo, lista[i]->parent);

	}*/

	int print = output(numEdges, maxCidade);

	if( print == 0) {

		printf("%d\n%d %d\n", custo_total, num_aero, num_estradas);
	}

	else {
		printf("Insuficiente\n");
	}

	/*clock_t end = clock();*/

	/*double time_spent = (double) (end-begin) / CLOCKS_PER_SEC;*/

	/*printf("tempo: %f\n", time_spent);*/

	/*for(i = 0; i <= maxCidade; i++) {
		free(grafo[i]);
		grafo = NULL;
	}
	free(grafo);
	for(i = 0; i < numEdges; i++) {
		free(lista[i]);
		lista = NULL;
	}
	free(lista);*/


	return 0;
}
