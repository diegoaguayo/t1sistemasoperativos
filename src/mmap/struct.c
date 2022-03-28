#include "struct.h"
#include <stdlib.h>

List* listInit()
{
  List* Lista = malloc(sizeof(List));
  Lista -> head = NULL;
  Lista -> tail = NULL;

  return Lista;
}

Node* nodeInit(int pid, Node* puntero)
{
  Node* Nodo = puntero;
  Nodo -> pid = pid;

  //callloc rellena con 0 el resto de las variables

  return Nodo;
}

void addNode(List* lista, Node* nuevo){
    lista->Nodos++;
    if(lista -> head == 0)
        {
        lista -> head = nuevo;
        }

        else
        {
        lista -> tail -> next = nuevo;
        nuevo -> prev = lista -> tail;
        }
        //printf("agregado el estrecho con id = %i al padre %i\n", person -> id, person ->parent ->id);
        lista -> tail = nuevo;
}

Node* getNode(List* list, int pid){
  printf("no encontrado");
  for(Node* nodo = list->head; nodo -> next; nodo = nodo -> next){
    if (nodo->pid == pid){
      return nodo;
    }
  }
  return NULL;
  
}