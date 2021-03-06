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
    int numeros[10];
    for(int i = 0; i < 10; i++){
      numeros[i] = 0;
    }
  
    for(int i = 0; i < 9; i++){
      for(int j = 0; j < 9; j++){
        int num = n->sudo[i][j];
        if(num != 0){
          for(int k = i+1; k<9; k++){
            if(num == n->sudo[k][j]){
              return 0;
            }
          }
          for(int k = j+1; k<9; k++){
            if(num == n->sudo[i][k]){
              return 0;
            }
          }
        }
      }
    }
  
  
  
  for(int i = 0; i < 9; i+=3){
    for(int j = 0; j < 9; j+=3){
      for(int z = 0; z < 10; z++){
        numeros[z] = 0;
      }
      for(int k = i; k < i+3; k++){
        for(int u = j; u < j+3; u++){
          if(n->sudo[k][u] != 0){
            if(numeros[n -> sudo[k][u]] == 0){
              numeros[n->sudo[k][u]] = 1;
            }else{
              return 0;
            }
          }
        }
      }
      
    }
  }

  return 1;
}


List* get_adj_nodes(Node* n){
    List* list=createList();
    int i,j,k;
    for(i = 0; i<9; i++){
      for(j = 0; j<9;j++){
        if(n->sudo[i][j] == 0){
          for(k = 1; k<10; k++){
            n->sudo[i][j] = k;
            if(is_valid(n)){
              Node *adj = copy(n);
              pushBack(list, adj);
            }
          }
          n->sudo[i][j] = 0;
          return list;
        }
      }
    }
    return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++){
    for(int j = 0; j< 9; j++){
      if(n->sudo[i][j] == 0){
        return 0;
      }
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){
  Stack *stack = createStack();
  push(stack, initial);

  while(!is_empty(stack)){
    Node *node = top(stack);
    pop(stack);
    if(is_final(node)){
      return node;
    }
    List *list = get_adj_nodes(node);
    Node* current = first(list);
    while(current != NULL){
      push(stack, current);
      current = next(list);
    }
    free(node);
    cont++;
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/