#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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


    while (1) {
        char comando[1000];
        printf("\n Introduce un comando: ");
        scanf("%s", &comando);
        printf("\n Tu comando es: %s", comando);
        

        Node* nodo = nodeInit();
        addNode(lista, nodo);

        
        if (strcmp(comando, "modify") == 0){
            
            int _pid = fork();
            if (_pid == 0) {
                
                printf("\nEn el hijo PID = %d", getpid());
                Node *nodo_hijo = lista -> tail;
                nodo_hijo -> pid = getpid();
                nodo_hijo -> tiempoInicial = 1234;
                nodo_hijo -> estado = 1;
                sleep(3);
                nodo_hijo  -> estado = 0;
                return 0;
            }

        }
        

        else if (strcmp(comando, "crlist") == 0) {
            sleep(1);
            eraseTail(lista);
            for(Node* _nodo = lista ->head; _nodo -> next; _nodo = _nodo -> next){
                printf("\n  PID nodo: %d, Tiempo inicial: (%f), Estado: (%d)", _nodo -> pid, _nodo -> tiempoInicial, _nodo -> estado);
            }
            
        }

        else{
            eraseTail(lista);
        }

    }
    /*nodo = nodeInit(2);
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
        //Node *nodo_2 = nodeInit(5);
        //addNode(lista, nodo_2);
        printf("\nEn el padre , nodo final = %d", lista -> tail -> pid);
    }
    else if (_pid == 0) {
        
        printf("\nEn el hijo PID = %d", getpid());
        lista -> tail -> pid = getpid();
        //return 0;
    }

    if (_pid > 0) {
        sleep(3);
        printf("\n!!! pid nodo cola  %d  (%d)", lista -> tail -> pid, getpid());
    }*/
    return 0;
}