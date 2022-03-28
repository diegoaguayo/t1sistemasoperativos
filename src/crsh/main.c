#include <stdio.h>
#include <string.h>
#include <unistd.h> // getppid() id del parent  // getpid() current id proces
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "struct.h"

#include "../input_manager/manager.h"

static List *lista;

// Funcion auxiliar para chequear si el input es un numero entero.
bool digit_check(char key[])
{
  for(int i = 0; i < strlen(key); i++)
  {
      if(isdigit(key[i])==0)
      {
          return false;
      }
  }
  return true;
}

// Funcion auxiliar para chequear si un numero es primo.
// https://stackoverflow.com/questions/50930926/how-to-check-if-a-number-is-prime-in-a-more-efficient-manner
bool is_prime(int num) {
  if(num <= 1) return false;
  if (num <= 3)  return true; 
  
  int range = sqrt(num);
  // This is checked so that we can skip 
  // middle five numbers in below loop 
  if (num % 2 == 0 || num % 3 == 0) 
      return false; 
  

  for (int i = 5; i <= range; i += 6) 
      if (num % i == 0 || num % (i + 2) == 0) 
          return false; 
  
  return true;
}

int main(int argc, char const *argv[])
{
  lista = listInit();
  int _continue = 1;
  char **input;
  while (_continue){
  
    printf("> ");
    input = read_user_input();
    int childCounter = 0;

    Node* nodo = nodeInit();
    addNode(lista, nodo);

    clock_t t;
    t = clock();
    fun();
    t = clock() - t;
    double time_taken = ((double)t)/CLOCKS_PER_SEC; 
  
    printf("fun() took %f seconds to execute \n", time_taken);

    // COMANDO HELLO
    if (strcmp(input[0], "hello") == 0) {
      childCounter++;
      int result = fork(); 
      if (result == 0){  
        clock_t t;
        t = clock();
        ////
        Node *nodo_hijo = lista -> tail;
        nodo_hijo -> pid = getpid();
        nodo_hijo -> ejecutable = input[0];
        printf("%s", "\n Hello World!. ");
        printf("\n> ");
        nodo_hijo -> estado = 1;
        t = clock() - t;
        double ejecucion = ((double)t)/CLOCKS_PER_SEC; 
        nodo_hijo -> tiempoEjecucion = ejecucion;
        return 0;
      }
    }

    // COMANDO SUM
    else if (strcmp(input[0], "sum") == 0) {
      childCounter++;
      int result = fork();
      if (result == 0){
        Node *nodo_hijo = lista -> tail;
        nodo_hijo -> pid = getpid();
        nodo_hijo -> ejecutable = input[0];
        if (atof(input[1]) && atof(input[2])) {
          float sum = atof(input[1]) + atof(input[2]);
          printf("\n Sum of two numbers= %f \n", sum); 
        }
        else {
          printf("\n Wrong arguments. You must enter float numbers as arguments"); 
          
        }
        printf("\n> ");
        return 0;
      }
    }

    // COMANDO IS_PRIME
    else if (strcmp(input[0], "is_prime") == 0) {
      childCounter++;
      int result = fork();
      if (result == 0){
        Node *nodo_hijo = lista -> tail;
        nodo_hijo -> ejecutable = input[0];
        if (digit_check(input[1])) {
          int number = atoi(input[1]);
          if (is_prime(number)) {
            printf("\n %d es un numero primo", number);
          }
          else {
            printf("\n %d no es un numero primo", number);
          }
        }
        else {
          printf("\n Wrong arguments. You must enter integer number as argument"); 
        }
        printf("\n> ");
        nodo_hijo -> estado = 1;
        return 0;
      }
    }

    // COMANDO CREXEC
    else if (strcmp(input[0], "crexec") == 0) {
      childCounter++;
      int result = fork();
      printf("Fork: %d", result);
      if (result == 0){
        Node *nodo_hijo = lista -> tail;
        nodo_hijo -> pid = getpid();
        //char ch = input[1];
        nodo_hijo -> ejecutable = input[0];
        if (!input[1]) {
          printf("\n Error. You must provide a command to execute.");
          printf("\n> ");
          return 0;
        }
        if (access(input[1], X_OK) != 0) {
          printf("\n Error. Executable doesn't exist.");
          printf("\n> ");
          return 0;
        }
        printf("\n");
        char command[1000] = "./";
        int i = 1;
        while(input[i]) {
          strcat(command, input[i]);
          strcat(command, " ");
          i ++;
        }
        system(command);
        printf("\n> ");
        nodo_hijo -> estado = 1;
        return 0;
      }
    }

    // COMANDO CREXIT
    else if (strcmp(input[0], "crexit") == 0) {
      _continue = 0;
      //falta terminar los procesos
    }

    // COMANDO CRLIST
    else if (strcmp(input[0], "crlist") == 0) {
        sleep(1);
        eraseTail(lista);
        for(Node* _nodo = lista ->head; _nodo -> next; _nodo = _nodo -> next){
            printf("\n PID nodo: (%d) | Ejecutable: (%s) | Tiempo ejecución: (%f) | Estado: (%d)", _nodo -> pid, _nodo -> ejecutable, _nodo -> tiempoEjecucion, _nodo -> estado);
        }
        printf("\n> ");
        
    }

    else{
        eraseTail(lista);
    }

    /* else {
      if (input[0] != "\0") {
        printf("\n crsh: command not found: %s", input[0]);
        printf("\n> ");
      }
      
    } */


    //END  
  }
  free_user_input(input);
}

