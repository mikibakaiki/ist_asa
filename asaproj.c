#include <stdio.h>
#include <stdlib.h>


/*ptr e um ponteiro para uma estrutura do tipo photograph */

typedef struct photograph {

    int data;
    int inDeg;
    int disc;
    struct photograph *next;

} *fotografia;

/*typedef fotografia *pointer;*/
static fotografia *head;

fotografia new(int value) {

    fotografia x = (fotografia) malloc(sizeof(struct photograph));

    x->data = value;
    x->inDeg = 0;
    x->disc = 0;
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


// void revTopOrdering(fotografia head, int maxPhotos, int maxPermuta) {
//
//     int i;
//
//     fotografia list, newlist;
//
//     for(list = head; list->next != NULL; list = list->next)  {
//         if(list->disc == 0) {
//             revTopOrder(list, newlist);
//         }
//     }
//
//     return newlist;
// }
//
//
// void revTopOrder(fotografia list, fotografia newlist) {
//     list->disc = 1;
//     for ()
// }

int main()  {

    int maxPhotos;
    int maxPermuta;
    int i;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    head = (fotografia*) malloc(maxPhotos*sizeof(fotografia));

    for(i = 0; i < maxPhotos; i++) {
        head[i] = NULL;
    }

    for(i = 0; i < maxPhotos; i++) {
        /*printf("entrei no for\n");*/

        head[i] = insertBegin(head[i], i+1);
        printf("head = %d\n", head[i]->data);
    }


	// for(i = 0; i < maxPermuta; i++) {
    //     int photo1, photo2;
    //
    //     fotografia t;
    //
	// 	scanf("%d %d", &photo1, &photo2);
    //
    //     t = head[i] + photo2;
    //
    //     if(t != NULL) {
    //
    //         t->inDeg ++;
    //         printf("inDeg de %d = %d\n", photo2, t->inDeg);
    //     }
	// }



    return 0;
}
