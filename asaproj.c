#include <stdio.h>
#include <stdlib.h>



typedef struct node {

    int data;
    struct node *next;

} fotografia;



static struct node *head;
static struct node *last;


/* Inicializa a lista */

void init() {

    head = NULL;
    last = NULL;
}
