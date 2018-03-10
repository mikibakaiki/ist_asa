#include <stdio.h>
#include <stdlib.h>

#define BLACK 1 /*concluido*/
#define WHITE -1 /* nao visitado*/
#define GRAY 0 /*visitado*/


typedef struct photograph {

    int data;
    int inDeg;
    struct photograph *next;

} *fotografia;

static fotografia *head;

static fotografia final;

int *pointer;
int incoerente = 0;
int insuficiente = 0;



/********************************************/

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

fotografia insertEnd(fotografia head, int value) {

    fotografia x;

    if(head == NULL) {
        /*printf("head e null\n");*/
        return new(value);
    }

    for(x = head; x->next != NULL; x = x->next);

    x->next = new(value);

    return head;
}

int search(fotografia head, int value)  {

    fotografia t;

    for(t = head; t != NULL; t = t->next) {

        if(t->data == value) {

            return 1;
        }
    }
    return 0;
}

void print(fotografia head, int maxPhotos) {

    fotografia t;
    int i = 0;
    for(t = head; t != NULL; t = t->next) {
        i++;
        if(i < maxPhotos) {
            printf("%d ", t->data);
        }
        else {
            printf("%d\n", t->data);
        }
    }
}

void dfs_visit(int u, int maxPhotos) {

    fotografia v;
    pointer[u] = GRAY;

    for(v = head[u]; v != NULL; v = v->next) {
        /*printf("dfs_visit for\n");*/
        /*printf("dfs_visit next != NULL\n");*/
        if(pointer[v->data - 1] == WHITE) {
            /*printf("dfs_visit pointer[v->data] == WHITE\n");*/
            dfs_visit((v->data - 1), maxPhotos);
        }
        else if(pointer[v->data - 1] == GRAY) {
            incoerente = 1;
            return;
        }
    }
    pointer[u] = BLACK;
    /*printf("pointer[%d] = %d\n", u, pointer[u]);*/
    final = insertBegin(final, u + 1);
}


void dfs(int maxPhotos) {

    int u;

    for(u = 0; u < maxPhotos; u++) {

        pointer[u] = WHITE;
        /*printf("pointer [%d] == %d\n", u, pointer[u]);*/
    }

    for(u = 0; u < maxPhotos; u++) {
        /*printf("entrei no for\n");*/
        if(pointer[u] == WHITE) {
            /*printf("pointer[%d] = WHITE\n", u);*/

            dfs_visit(u, maxPhotos);
        }
        /*printf("u = %d\n", u);*/
        /*print(head[u]);*/
    }
}

void insuf() {
    /*printf("cheguei ao insuf\n");*/
    fotografia iter = final;

    while (iter->next != NULL) {
        /*printf("procurar no head[%d] o elemento %d\n", iter->data,(iter->next)->data);*/
        if(search(head[iter->data - 1],iter->next->data) == 0) {

            insuficiente = 1;
        }
        iter = iter->next;
    }
}





int main()  {

    int maxPhotos;
    int maxPermuta;
    int i;

	scanf("%d %d", &maxPhotos, &maxPermuta);

    int color[maxPhotos];

    pointer = color;

    head = (fotografia*) malloc(maxPhotos*sizeof(fotografia));

    for(i = 0; i < maxPhotos; i++) {
        head[i] = NULL;
    }


	for(i = 0; i < maxPermuta; i++) {

        int photo1, photo2;

		scanf("%d %d", &photo1, &photo2);

        head[photo1-1] = insertEnd(head[photo1-1], photo2);
	}

    dfs(maxPhotos);
    insuf();

    if(incoerente == 1) {

        printf("Incoerente\n");

        return 0;
    }

    if(insuficiente == 1) {

        printf("Insuficiente\n");

        return 0;
    }

    print(final, maxPhotos);

    return 0;
}
