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

    glob_var = mmap(NULL, sizeof *glob_var, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);


    *glob_var = 1;
    Node *nodo = mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    int _pid = fork();
    if (_pid > 0 ) {
        // creamos el nodo
        
        nodeInit(_pid, nodo);
        addNode(lista, nodo);
        printf("PID hijo: %d - Desde el padre", nodo->pid);
    } else {
        printf("PID hijo - Desde el hijo: %d", (int)getpid());
        Node* nodo_hijo = getNode(lista, (int)getpid());
        //nodo_hijo -> pid = 12345;
        exit(EXIT_SUCCESS);
    }
    printf("\nPID: %d", _pid);
    if (_pid == 01234) {
        printf("PID hijo - Desde el hijo: %d", (int)getpid());
        Node* nodo_hijo = getNode(lista, (int)getpid());
        nodo_hijo -> pid = 12345;
        exit(EXIT_SUCCESS);
    } else {
        wait(NULL);
        printf("\nNuevo pid hijo %d\n", lista -> head -> pid);
        munmap(glob_var, sizeof *glob_var);
    }
    return 0;
}