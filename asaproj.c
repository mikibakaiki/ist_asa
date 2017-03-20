#include <stdio.h>
#include <stdlib.h>


/*ptr e um ponteiro para uma estrutura do tipo photograph */

typedef struct photograph {

    int data;
    int inDeg;
    struct photograph *next;

} fotografia;

typedef fotografia *pointer;



pointer new(int maxphoto) {

    pointer x = (pointer) malloc(sizeof(struct photograph));

    x->data = maxphoto;
    x->inDeg = 0;
    x->next = NULL;

    return x;
}

pointer insertEnd(pointer ptr, int value) {

    pointer x = ptr;

    while(x->next != NULL) {

        x = x->next;
    }

    x->next = new(value);
    /*sempre que se insere um elemento, significa que aumentou o inDegree*/
    // x->inDeg++;

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
        NodeList[i].inDeg = 0;
        NodeList[i].next = NULL;
    }

	for(i = 0; i < maxPermuta; i++) {

        int photo1, photo2;

		scanf("%d %d", &photo1, &photo2);

        NodeList[photo2 - 1].inDeg++;

        pointer x;

        x = insertEnd( (ptr + (photo1 - 1)), photo2);


        printf("ligacao do %d para o %d\n",(ptr+(photo1-1))->data, x->next->data);
        printf("indegree da posicao %d do vector = %d\n", (photo2-1), NodeList[photo2 - 1].inDeg);
	}

    return 0;
}
