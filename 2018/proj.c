#include <stdio.h>
#include <stdlib.h>


typedef struct supermarket{
    int num;
    int discovery;
    int lowest;
    struct supermarket *next;
} supermercado;


// static supermercado *head;

supermercado new(int numNo) {

    mercado = (supermercado) malloc(sizeof(struct supermarket));

    mercado->num = numNo;
    mercado->discovery = 0;
    mercado->lowest = 0;
    mercado->next = NULL;

    return mercado;
}

supermercado insertEnd(int value) {
    mercado = new(value);

    if(head == NULL) {
        /*printf("head e null\n");*/
        return new(value);
    }

    for(x = head; x->next != NULL; x = x->next);

    x->next = new(value);

    return head;
}
































//int main()  {
//     /* Number of supermarkets */
//     int numNodes;
//
//     /* Number of connections - arches*/
//     int numConnections;
//
//     int i;
//
// 	scanf("%d %d", &numNodes, &numConnections);
//
//}
