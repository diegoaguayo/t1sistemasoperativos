#include "struct.h"
#include <stdlib.h>
#include <sys/mman.h>

List* listInit()
{
  //List* Lista = calloc(1, sizeof(List));
  List* Lista = mmap(NULL, sizeof(List), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  Lista -> head = NULL;
  Lista -> tail = NULL;

  return Lista;
}

Node* nodeInit(int pid)
{
  Node* Nodo = mmap(NULL, sizeof(Node), PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
  Nodo -> pid = pid;

  //callloc rellena con 0 el resto de las variables

  return Nodo;
}

void addNode(List* lista, Node* nuevo){

    if (lista -> head == 0) {
        lista -> head = nuevo;
    }
    else {
        lista -> tail -> next = nuevo;
        nuevo -> prev = lista -> tail;
    }
    //printf("agregado el estrecho con id = %i al padre %i\n", person -> id, person ->parent ->id);
    lista -> tail = nuevo;
}

Node* getNode(List* list, int pid){
  for(Node* nodo = list->head; nodo -> next; nodo = nodo -> next){
    if (nodo->pid == pid){
      return nodo;
    }
  }
  return NULL;
}