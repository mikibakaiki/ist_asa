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
        printf("head e null\n");
        return new(value);
    }

    for(x = head; x->next != NULL; x = x->next);

    x->next = new(value);

    return head;
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

void print(fotografia head) {

    fotografia t;

    for(t = head; t != NULL; t = t->next) {

        printf("elemento da lista : %d\n", t->data);
    }


}


void dfs(fotografia *head, int maxPhotos) {

    int u;

    for(u = 0; u < maxPhotos; u++) {

        pointer[u] = WHITE;
        printf("pointer [%d] == %d\n", u, pointer[u]);
    }

    for(u = 0; u < maxPhotos; u++) {

        if(pointer[u] == WHITE) {

            dfs_visit(head[u], u, maxPhotos);
        }
        // printf("u = %d\n", u);
        // print(head[u]);
    }
}

void dfs_visit(fotografia head, int u, int maxPhotos) {

    int v;
    pointer[u] = GRAY;

    for(v = 0; v < maxPhotos; v++) {
        if(head->next != NULL) {
            if(pointer[v] == WHITE) {
                dfs_visit(head, v, maxPhotos);
            }
        }
    }
    pointer[u] = BLACK;
    final = insertBegin(final, head[u].data);
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

    // for(i = 0; i < maxPhotos; i++) {
    //
    //     head[i] = insertBegin(head[i], i+1);
    // }

	for(i = 0; i < maxPermuta; i++) {

        int photo1, photo2;

		scanf("%d %d", &photo1, &photo2);

        head[photo1-1] = insertEnd(head[photo1-1], photo2);
	}

    dfs(head, maxPhotos);

    // print(final);

    return 0;
}
