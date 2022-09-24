#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

Node* search(Node *root, int x, FILE *output_file)
{
    if(root==NULL || root->data==x) //if root->data is x then the element is found
    {
        return root;
    }
    else if(x>root->data) // x is greater, so we will search the right subtree
    {
        fprintf(output_file, "%d ", root->data);
        return search(root->right_child, x, output_file);
    } 

        
    else //x is smaller than the data, so we will search the left subtree
    { 
        fprintf(output_file, "%d ", root->data);
        return search(root->left_child, x, output_file);
    } 
        
}

int deep(Node *root, int x)
{
    if(root==NULL || root->data==x) //if root->data is x then the element is found
    {
        return 0;
    }
    else if(x>root->data) // x is greater, so we will search the right subtree
    {
        return 1 + deep(root->right_child, x);
    } 

        
    else //x is smaller than the data, so we will search the left subtree
    { 
        return 1 + deep(root->left_child, x);
    } 
        
}

Node* new_node(int x)
{
    Node *p;
    p = malloc(sizeof(Node));
    p->data = x;
    p->left_child = NULL;
    p->right_child = NULL;

    return p;
}

Node* insert(Node *root, int x)
{
    //searching for the place to insert
    if(root==NULL)
        return new_node(x);
    else if(x>root->data) // x is greater. Should be inserted to right
        root->right_child = insert(root->right_child, x);
    else // x is smaller should be inserted to left
        root->left_child = insert(root->left_child, x);
    return root;
}

void inorder(Node *root, FILE *output_file)
{
    if(root!=NULL) // checking if the root is not null
    {
        inorder(root->left_child, output_file); // visiting left child
        fprintf(output_file, "%d ", root->data); // printing data at root
        inorder(root->right_child, output_file);// visiting right child
    }
}

void free_tree(Node *root)
{
    if(root!=NULL)
    {
        free_tree(root->left_child);
        free_tree(root->right_child);
        free(root);
    }
}
