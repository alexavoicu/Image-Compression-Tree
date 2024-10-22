/*VOICU Alexa-Andreea-312CD*/
#include <stdio.h>
#include <stdlib.h>

typedef struct tree_node {
    unsigned char type;
    unsigned char red;
    unsigned char green;
    unsigned char blue;
    struct tree_node* top_left;
    struct tree_node* top_right;
    struct tree_node* bottom_right;
    struct tree_node* bottom_left;
} *TreeNode;

typedef struct {
    unsigned char red;
    unsigned char green;
    unsigned char blue;
} pixel;

TreeNode create_leaf(TreeNode, unsigned char, unsigned char, unsigned char);
TreeNode create_tree(pixel **, int, int, int, int, int *);
int max(int, int);
int get_tree_depth(TreeNode);
int get_num_leaves(TreeNode);
void print_level(TreeNode, int, FILE *);
void get_level_order(TreeNode, FILE *);
void free_tree(TreeNode);
void free_image(pixel**, int);