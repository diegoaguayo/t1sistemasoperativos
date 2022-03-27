#include <stdio.h>
#include <string.h>
#include <unistd.h> // getppid() id del parent  // getpid() current id proces
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <math.h>

#include "../input_manager/manager.h"

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
  int _continue = 1;
  char **input;
  while (_continue){
  
    printf("> ");
    input = read_user_input();
    int childCounter = 0;

    // COMANDO HELLO
    if (strcmp(input[0], "hello") == 0) {
      childCounter++;
      int result = fork(); 
      if (result == 0){
        printf("%s", "\n Hello World!. \n");
        printf("> ");
        return 0;
      }
    }

    // COMANDO SUM
    else if (strcmp(input[0], "sum") == 0) {
      childCounter++;
      int result = fork();
      if (result == 0){
        if (atof(input[1]) && atof(input[2])) {
          float sum = atof(input[1]) + atof(input[2]);
          printf("\n Sum of two numbers= %f \n", sum); 
        }
        else {
          printf("\n Wrong arguments. You must enter float numbers as arguments"); 
          
        }
        printf("> ");
        return 0;
      }
    }

    // COMANDO IS_PRIME
    else if (strcmp(input[0], "is_prime") == 0) {
      childCounter++;
      int result = fork();
      if (result == 0){
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
        return 0;
      }
    }

    // COMANDO CREXEC
    else if (strcmp(input[0], "crexec") == 0) {
      childCounter++;
      int result = fork();
      printf("Fork: %d", result);
      if (result == 0){
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
        return 0;
      }
    }

    // COMANDO CRLIST
    else if (strcmp(input[0], "crlist") == 0) {
      _continue = 0;
      //falta terminar los procesos
    }

    // COMANDO CREXIT
    else if (strcmp(input[0], "crexit") == 0) {
      _continue = 0;
      //falta terminar los procesos
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

