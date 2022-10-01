#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "../imagelib/imagelib.h"
#pragma once


struct node;
typedef struct node Node;
struct node
{
    //Childrens
    Node *NW;
    Node *NE;
    Node *SW;
    Node *SE;
    //Data LBA
    double L;
    double a;
    double b;

    //means
    double mean_L;
    double mean_a;
    double mean_b;

    //sd
    double sd;
    //dimensions
    int height;
    int width;
    //position
    int x;
    int y;
    bool is_leaf;
};

Node* new_node(int x, int y, int width, int height);
Node* insert(Image* img, Node *root, int x, int y, int width, int height);
void free_tree(Node *root);
void filter(Image* img, Node *root, double alpha);
void mean_Lba(Image* img, Node *root);
void sd_Lba(Image* img, Node *root);
int n_leaves(Node *root);