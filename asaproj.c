#include <stdio.h>
#include <stdlib.h>


/*ptr e um ponteiro para uma estrutura do tipo photograph */

typedef struct photograph {

    int data;
    struct photograph *next;

} fotografia;

typedef fotografia* pointer;

/* Funcao VectorSearch() retorna 0 caso nao exista o valor na lista e retorna 1 caso contrario*/

int VectorSearch(fotografia vectorPos, int valor)  {

    pointer x = (pointer) malloc(sizeof(struct photograph));

    x = &vectorPos;

    for(x; x != NULL; x = x->next) {
        printf("estou no for do VectorSearch\n");
        printf("x->data = %d; valor = %d\n", x->data, valor);
        if(x->data == valor) {
            printf("ja ha um elemento\n");
            return 1;
        }
    }
    printf("nao ha elemento, vou inserir\n");
    return 0;
}

int main()  {

    int maxPhotos;
	int maxPermuta;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    /*vector de nodos, onde se guardam as ligacoes*/

    fotografia NodeList[maxPhotos];

    pointer ptr = (pointer) malloc(sizeof(struct photograph));


    /* Ciclo que preenche o vector*/
    int i;

    for(i = 0; i < maxPhotos; i++) {

        NodeList[i].data = i + 1;
        NodeList[i].next = NULL;
    }

	for(i = 0; i < maxPermuta; i++) {

        fotografia photo1, photo2;

		scanf("%d %d", &photo1.data, &photo2.data);

        printf("photo1: %d photo2: %d\n", photo1.data, photo2.data);

        int j;

        printf("antes do for \n");

        for(j = 0; j < maxPhotos; j++) {

            printf("passei o for\n");

            if(photo1.data == NodeList[j].data) {
                printf("photo1 = %d == Nodelist[j].data = %d\n", photo1.data,j);

                if(VectorSearch(NodeList[j], photo2.data) == 0) {

                    photo2.next = ptr->next;
                    ptr->next = &photo2;
                }
            }
        }

	}
    return 0;
}
