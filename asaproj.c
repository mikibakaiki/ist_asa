#include <stdio.h>
#include <stdlib.h>


/*ptr e um ponteiro para uma estrutura do tipo photograph */

typedef struct photograph {

    int data;
    int inDeg;
    struct photograph *next;

} *fotografia;

/*typedef fotografia *pointer;*/
/*static fotografia head;*/

fotografia new(int value) {

    fotografia x = (fotografia) malloc(sizeof(struct photograph));

    x->data = value;
    x->inDeg = 0;
    x->next = NULL;

    return x;
}

fotografia insertBegin(fotografia head, int value) {

    fotografia x = new(value);

    x->next = head;

    return x;
}

fotografia search(fotografia head, int value)  {

    fotografia t;

    for(t = head; t != NULL; t = t->next) {

        if(t->data == value) {

            return t;
        }
    }
    return NULL;
}

int main()  {

    int maxPhotos;
    int maxPermuta;
    int i;

    fotografia head = (fotografia) malloc(sizeof(struct photograph));
    head = NULL;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    for(i = 0; i < maxPhotos; i++) {
        /*printf("entrei no for\n");*/

        head = insertBegin(head, i+1);
        printf("head = %d\n", head->data);

    }

	for(i = 0; i < maxPermuta; i++) {
        int photo1, photo2;
        fotografia t;

		scanf("%d %d", &photo1, &photo2);

        t = search(head, photo2);

        if(t != NULL) {

            t->inDeg ++;
            printf("inDeg de %d = %d\n", photo2, t->inDeg);
        }


        // printf("ligacao do %d para o %d\n",(ptr+(photo1-1))->data, x->next->data);
        // printf("indegree da posicao %d do vector = %d\n", (photo2-1), NodeList[photo2 - 1].inDeg);
	}

    return 0;
}
