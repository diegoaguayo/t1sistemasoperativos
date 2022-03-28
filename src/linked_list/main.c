#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "struct.h"

static int *glob_var;

int main(void)
{
    List *lista = listInit();

    Node* nodo = nodeInit(1);
    addNode(lista, nodo);

    nodo = nodeInit(2);
    addNode(lista, nodo);

    nodo = nodeInit(3);
    nodo -> tiempoInicial = 144.4;
    addNode(lista, nodo);

    nodo = nodeInit(4);
    addNode(lista, nodo);
    
    nodo = getNode(lista, 3);

    printf("\nNodo encontrado: %d", nodo -> pid);
    
    int _pid = fork();
    if (_pid > 0) {
        Node *nodo_ = getNode(lista, 4);
        printf("\nEn el padre %d)", nodo_ -> pid);
    }
    /*if (_pid == 0) {
        Node *nodo_ = getNode(lista, 4);
        printf("\nEn el hijo (%d)", nodo_ -> pid);
    }*/

    return 0;
}