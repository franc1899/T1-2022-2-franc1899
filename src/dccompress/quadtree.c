#include <stdio.h>
#include <stdlib.h>
#include "quadtree.h"
#include "../imagelib/imagelib.h"
#include <math.h>

Node *new_node(int x, int y, int width, int height)
{
    Node *p;
    p = malloc(sizeof(Node));
    p->x = x;
    p->y = y;
    p->width = width;
    p->height = height;
    p->is_leaf = true;
    p->L = 0;
    p->a = 0;
    p->b = 0;
    p->mean_L = 0;
    p->mean_a = 0;
    p->mean_b = 0;
    p->NW = NULL;
    p->NE = NULL;
    p->SW = NULL;
    p->SE = NULL;

    return p;
}

Node *insert(Image *img, Node *root, int x, int y, int width, int height)
{
    // searching for the place to insert
    if (root == NULL)
    {
        root = new_node(x, y, width, height);
        mean_Lba(img, root);
        sd_Lba(img, root);
        //printf("x: %d y: %d width: %d height: %d\n", x, y, width, height);
        insert(img, root, x, y, width, height);
    }
    else
    {
        if (width == 1)
        {
            root->is_leaf = true;
            return root;
        }
        width = width / 2;
        height = height / 2;
        //printf("x: %d y: %d width: %d height: %d\n", x, y, width, height);
        root->is_leaf = false;
        root->SW = insert(img, root->SW, x, y + height, width, height);
        root->NW = insert(img, root->NW, x, y, width, height);
        root->SE = insert(img, root->SE, x + width, y + height, width, height);
        root->NE = insert(img, root->NE, x + width, y, width, height);
        //printf("means: %f %f %f %f\n", root->SW->mean_L, root->NW->mean_L, root->SE->mean_L, root->NE->mean_L);
        //printf("sd: %f %f %f %f\n", root->SW->sd, root->NW->sd, root->SE->sd, root->NE->sd);
    }
    return root;
}

void mean_Lba(Image *img, Node *root)
{
    double sum_L = 0;
    double sum_a = 0;
    double sum_b = 0;
    for (int i = root->x; i < root->x + root->width; i++)
    {
        for (int j = root->y; j < root->y + root->height; j++)
        {
            sum_L += img->pixels[i][j].L;
            sum_a += img->pixels[i][j].a;
            sum_b += img->pixels[i][j].b;
        }
    }
    root->mean_L = sum_L / (root->width * root->height);
    root->mean_a = sum_a / (root->width * root->height);
    root->mean_b = sum_b / (root->width * root->height);
}

void sd_Lba(Image *img, Node *root)
{
    printf("x: %d y: %d width: %d height: %d\n", root->x, root->y, root->width, root->height);
    for (int i = root->x; i < root->x + root->width; i++)
    {
        for (int j = root->y; j < root->y + root->height; j++)
        {
            root->L += pow((img->pixels[i][j].L - root->mean_L), 2);
            root->a += pow((img->pixels[i][j].a - root->mean_a), 2);
            root->b += pow((img->pixels[i][j].b - root->mean_b), 2);
        }
    }
    root->L = sqrt(root->L / (root->width * root->height));
    root->a = sqrt(root->a / (root->width * root->height));
    root->b = sqrt(root->b / (root->width * root->height));
    root->sd = (root->L + root->a + root->b) / 3;
    //printf("height sd: %d %f\n", root->height, root->sd);
}

void free_tree(Node *root)
{
    if (root == NULL)
    {
        return;
    }
    free_tree(root->NW);
    free_tree(root->NE);
    free_tree(root->SW);
    free_tree(root->SE);
    free(root);
}

void filter(Image *img, Node *root, double alpha){
    if (root == NULL)
    {
        //printf("me voy a la xuxa");
        return;
    }
    if (root->is_leaf == true)
    {
        //printf("no wei xd\n");
        return;
    }
    if (root->sd < alpha)
    {   
        //printf("HOLAAAAAA\n");
        //printf("sd: %f\n", root->sd);
        root->is_leaf = true;
        img_square_paint(
            img,
            root->x,
            root->y,
            root->height,
            (Color) {.L = root->mean_L, .a = root->mean_a, .b = root->mean_b}
        );
        return;
    }
    filter(img, root->NW, alpha);
    filter(img, root->NE, alpha);
    filter(img, root->SW, alpha);
    filter(img, root->SE, alpha);
}