#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "struct.h"

int main(void)
{
    List *lista = listInit();

    Node* nodo = nodeInit(1);
    addNode(lista, nodo);

    nodo = nodeInit(2);
    addNode(lista, nodo);

    nodo = nodeInit(3);
    addNode(lista, nodo);

    nodo = getNode(lista, 3);

    printf("\nNodo encontrado: %d", nodo -> pid);
    
    /*int _pid = fork();
    if (_pid > 0) {
        printf("\nEn el padre");
        //nodo = nodeInit(_pid);
        //addNode(lista, nodo);
    }
    if (_pid == 0) {
        printf("\nEn el hijo");
        //nodo = getNode(lista, 3);
        //printf("\nNodo encontrado en hijo: %d", nodo -> pid);
    }*/

    return 0;
}