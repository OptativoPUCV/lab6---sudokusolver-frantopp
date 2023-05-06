#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int fila[10];
  int columna[10];
  int subMatriz[10];

  for(int i = 0; i < 9; i++){
    
    for(int aux = 0; aux < 10; aux++){
      fila[aux] = 0;
      columna[aux] = 0;
      subMatriz[aux] = 0;
    }

    for(int k = 0; k < 9; k++){

      if(n->sudo[i][k] != 0){
        if(fila[n->sudo[i][k]] == 1) return 0;
        else fila[n->sudo[i][k]] = 1;
      }

      if(n->sudo[k][i] != 0){
        if(columna[n->sudo[k][i]] == 1) return 0;
        else columna[n->sudo[k][i]] = 1;
      }

      int subMatrizFila = 3*(i/3) + (k/3);
      int subMatrizColumna = 3*(i%3) + (k%3);

      if(n->sudo[subMatrizFila][subMatrizColumna] != 0){
        if(subMatriz[n->sudo[subMatrizFila][subMatrizColumna]] == 1) return 0;
        else subMatriz[n->sudo[subMatrizFila][subMatrizColumna]] = 1;
      }
    }
  }
    return 1;
}


List* get_adj_nodes(Node* n){
  List* list=createList();

  for(int i = 0; i < 9; i++){
    for(int j = 0; j < 9; j++){
      if(n->sudo[i][j] == 0 ){
        for(int aux = 1; aux < 10; aux++){
          n->sudo[i][j] = aux;
          Node* nuevoNodo = copy(n);
          if(is_valid(nuevoNodo) == 1){
            pushBack(list,nuevoNodo);
          }
        }
      }
    }
  }
  return list;
}


int is_final(Node* n){
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        if(n->sudo[i][j]==0) return 0;
      }
    }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack* aux = createStack();
  push(aux,initial);

  while(is_empty(aux) != 1){
    Node* primero = top(aux);
    pop(aux);
    
    if(is_final(primero) == 1) return primero;
    List* lista = get_adj_nodes(primero);

    Node* nodos = first(lista);
    while(nodos != NULL){
      push(aux,nodos);
      nodos = next(lista);
    }
  }
  return NULL;
}
