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

    x = vectorPos;

    for(x; x != NULL; x = x->next) {

        if(x->data == valor) {

            return 1;
        }
    }

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

        for(ptr = NodeList[0]; ptr != NULL; ptr ++) {

            if(photo1.data == ptr->data) {

                if(VectorSearch(ptr, photo2.data) == 0) {

                    photo2.next = ptr->next;
                    ptr->next = photo2;
                }
            }
        }
		/*printf("photo1: %d photo2: %d\n", photo1.data, photo2.data);*/
	}
    return 0;
}
