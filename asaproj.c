#include <stdio.h>
#include <stdlib.h>


/*typedef struct graph {

	int V, E;
	int **adj;

} *Graph;*/

typedef struct node {

    int data;
    struct node *next;

} fotografia;



int main()  {

    /*int var;*/

    int maxPhotos;
	int maxPermuta;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    /*vector de nodos, onde se guardam as ligacoes*/

    fotografia NodeList[maxPhotos];

    /* pointer e um ponteiro para a estrutura fotografia  */

    fotografia *pointer;
    pointer = (fotografia*) malloc(sizeof(fotografia));
    int i;

    /* Ciclo que preenche o vector*/
    
    for(i = 0; i < maxPhotos; i++)  {

        NodeList[i].data = i + 1;
    }

	for(i= 0; i < maxPermuta; i ++){

        fotografia photo1, photo2;

		scanf("%d %d", &photo1.data, &photo2.data);

		/*printf("photo1: %d photo2: %d\n", photo1.data, photo2.data);*/
	}
    return 0;
}
