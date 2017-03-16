#include <stdio.h>
#include <stdlib.h>



typedef struct node {

    int data;
    struct node *next;

} fotografia;



static struct node *head;
/*static struct node *last;*/



/* Inicializa a lista */

void init() {

    head = NULL;
    /*last = NULL;*/
}


int main()  {

    int var;

    int maxPhotos;
	int maxPermuta;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    fotografia NodeList[maxPhotos];

	for(var = 0; var <= maxPhotos, var ++){

        int photo1, photo2;

		scanf("%d %d", &photo1, &photo2);

		new_Node(photo1, photo2);
		actualizaLista();
	}
}
