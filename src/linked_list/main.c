#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include "struct.h"

static int *glob_var;
static List *lista;

int main(void)
{
    lista = listInit();

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

    printf("\nNodo encontrado: %d  ; PID = %d", nodo -> pid, getpid());
    
    int _pid = fork();
    if (_pid > 0) {
        Node *nodo_2 = nodeInit(5);
        addNode(lista, nodo_2);
        printf("\nEn el padre ");
    }
    if (_pid == 0) {
        nodo = getNode(lista, 5);
        nodo -> pid = 99;
        printf("\nEn el hijo PID = %d", getpid());
    }

    printf("\n!!! Nodo %d", nodo -> pid);

    return 0;
}