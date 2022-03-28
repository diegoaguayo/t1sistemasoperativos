#include <stdio.h>

#pragma once


struct linked_list_node;
typedef struct linked_list_node Node;
struct linked_list_node
{
  int pid;
  int estado;
  float tiempoInicial;
  float tiempoFinal;
  float tiempoEjecucion;
  char ejecutable[1000] ;

  Node* prev;
  Node* next;


};

struct linked_list;
typedef struct linked_list List;
struct linked_list
{
  Node* head;
  Node* tail;
};

List* listInit();
Node* nodeInit(int pid);
Node* getNode(List* list, int pid);
void addNode(List* lista, Node* nuevo);