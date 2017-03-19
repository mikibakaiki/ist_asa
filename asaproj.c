#include <stdio.h>
#include <stdlib.h>


/*ptr e um ponteiro para uma estrutura do tipo photograph */

typedef struct photograph {

    int data;
    struct photograph *next;
    int ligacao = 0; // Varia de 0 a maxPhotos
    int visitado = 0; // Varia entre 0 e 1, marcacao de visitado ou nao (0  =  não visitado / 1 = visitado)

} fotografia;

typedef fotografia *pointer;


pointer new(int maxphoto) {

    pointer x = (pointer) malloc(sizeof(struct photograph));

    x->data = maxphoto;
    x->next = NULL;

    return x;
}

pointer insertEnd(pointer ptr, int value) {

    pointer x = ptr;

    while(x->next != NULL) {

        x = x->next;
    }

    x->next = new(value);

    return x;
}


int main()  {

    int maxPhotos;
	int maxPermuta;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    /*vector de nodos, onde se guardam as ligacoes*/

    fotografia NodeList[maxPhotos];
    pointer ptr = (pointer) malloc(sizeof(struct photograph));
    ptr = NodeList;

    int i;

    for(i = 0; i < maxPhotos; i++) {

        NodeList[i].data = i + 1;
        NodeList[i].next = NULL;
    }

	for(i = 0; i < maxPermuta; i++) {

        int photo1, photo2;

		scanf("%d %d", &photo1, &photo2);

        pointer x;

        x = insertEnd( (ptr + (photo1 - 1)), photo2);

        printf("ligacao do %d para o %d\n",(ptr+(photo1-1))->data, x->next->data);
	}

    return 0;
}
