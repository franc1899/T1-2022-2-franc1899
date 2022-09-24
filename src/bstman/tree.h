#include <stdio.h>
#include <stdlib.h>
#pragma once

struct node;
typedef struct node Node;
struct node
{
    int data; //node will store an integer
    Node *right_child; // right child
    Node *left_child; // left child
};



//functions implemented in tree.c

Node* search(Node *root, int x, FILE *output_file);
int deep(Node *root, int x);
Node* new_node(int x);
Node* insert(Node *root, int x);
void inorder(Node *root, FILE* output_file);
void free_tree(Node *root);

