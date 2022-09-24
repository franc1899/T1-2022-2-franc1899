#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "tree.h"

//docs https://www.codesdope.com/blog/article/binary-search-tree-in-c/

/* Retorna true si ambos strings son iguales */
bool string_equals(char *string1, char *string2) {
  return !strcmp(string1, string2);
}

/* Revisa que los parametros del programa sean válidos */
bool check_arguments(int argc, char **argv) {
  if (argc != 3) {
    printf("Modo de uso: %s INPUT OUTPUT\n", argv[0]);
    printf("Donde:\n");
    printf("\tINPUT es la ruta del archivo de input\n");
    printf("\tOUTPUT es la ruta del archivo de output\n");
    exit(1);
  }

  return true;
}


int main(int argc, char** argv) {
  check_arguments(argc, argv);

  FILE* input_file = fopen(argv[1], "r");
  FILE* output_file = fopen(argv[2], "w");

  int node_count;
  int query_count;

  fscanf(input_file, "%d", &node_count);

  /* leemos Cada nodo */
  int k;
  Node *root = NULL;
  for (int i=0; i<node_count; i++) {
    fscanf(input_file, "%d", &k);
    root = insert(root, k);
  }


  fscanf(input_file, "%d", &query_count);
  /* leemos las consultas */
  char command[32];
  int value;
  for (int i=0; i<query_count; i++) {
    fscanf(input_file, "%s %d", command, &value);
    if (string_equals(command, "ORDER")) {
      inorder(root, output_file);
      fprintf(output_file, "\n");
    }
    else if (string_equals(command, "PATH")) {
      Node *node_searched = search(root, value, output_file);
      if (node_searched != NULL) {
        fprintf(output_file, "%d\n", node_searched->data);
      }
      else {
        fprintf(output_file, "X\n");
      }
    }
    else if (string_equals(command, "DEEP")) {
      int deep_value = deep(root, value);
        fprintf(output_file, "%d\n", deep_value);
    }
    /* completar la revision de comando y ejecucion de los mismos */
  }

  
  fclose(input_file);
  fclose(output_file);

  ///////////////////////////////////
  //     Liberamos memoria         //
  ///////////////////////////////////

  free_tree(root);

  return 0;
}
