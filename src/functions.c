/*VOICU Alexa-Andreea-312CD*/
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

TreeNode create_leaf(TreeNode node, unsigned char red, unsigned char blue, unsigned char green)
{   
    node->type = 1;
    node->red = red;
    node->green = green;
    node->blue = blue;
    node->top_left = NULL;
    node->top_right = NULL;
    node->bottom_right = NULL;
    node->bottom_left = NULL;
    return node;
}

TreeNode create_tree(pixel **image, int x, int y, int size, int factor, int *max_leaf_size)
{
    TreeNode node = (TreeNode)calloc(1, sizeof(struct tree_node));
    if (node == NULL) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    unsigned long long red = 0, green = 0, blue = 0, mean = 0;
    //calcularea valorilor medii de rgb
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            red = red + image[i][j].red;
            green = green + image[i][j].green;
            blue = blue + image[i][j].blue;
        }
    }
    red = red / (size * size);
    blue = blue / (size * size);
    green = green / (size * size);
    //calcularea scorului
    for (int i = x; i < x + size; i++) {
        for (int j = y; j < y + size; j++) {
            unsigned long long red_mul= 0, green_mul = 0, blue_mul = 0;
            red_mul = (red - image[i][j].red) * (red - image[i][j].red);
            green_mul = (green - image[i][j].green) * (green - image[i][j].green);
            blue_mul = (blue - image[i][j].blue) * (blue - image[i][j].blue);
            mean = mean + red_mul + green_mul + blue_mul;  
        }
    }
    mean = mean / (3 * size *size);
    //crearea de noduri in functie de mean
    if ((int) mean <= factor) {
        if (size > *max_leaf_size) {
            *max_leaf_size = size;
        }
        node = create_leaf(node, (unsigned char)red, (unsigned char)blue, (unsigned char)green);
        return node;
    }
    else {
        node->type = 0;
        node->red = 0;
        node->green = 0;
        node->blue = 0;
        node->top_left = create_tree(image, x, y, size / 2, factor, max_leaf_size);
        node->top_right = create_tree(image, x, y + size / 2, size / 2, factor, max_leaf_size);
        node->bottom_right = create_tree(image, x + size / 2, y + size / 2, size / 2, factor, max_leaf_size);
        node->bottom_left = create_tree(image, x + size / 2, y, size / 2, factor, max_leaf_size);
        return node;
    }
}

int max(int a, int b)
{
    if(a > b)
    return a;
    return b;
}

int get_tree_depth(TreeNode node)//calculam recursiv adancimea
{
    if (node == NULL) {
        return 0;
    }
    int left_up_depth = get_tree_depth(node->top_left);
    int right_up_depth = get_tree_depth(node->top_right);
    int left_down_depth = get_tree_depth(node->bottom_left);
    int right_down_depth = get_tree_depth(node->bottom_right);
    int max1 = max(left_up_depth, right_up_depth);
    int max2 = max(left_down_depth, right_down_depth);
    return max(max1, max2) + 1;//returneaza maximul pornind de la un nod radacina
}

int get_num_leaves(TreeNode node)
{
    if (node == NULL) {
        return 0;
    }
    if (node->type == 1) {
        return 1;
    }
    int num_leaves = get_num_leaves(node->top_left) + get_num_leaves(node->top_right);
    num_leaves = num_leaves + get_num_leaves(node->bottom_left) + get_num_leaves(node->bottom_right);
    return num_leaves;
}

void print_level(TreeNode node, int level, FILE *out)
{
    if (node == NULL)
        return;
    if (level == 0) {
        if (node->type == 0) {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
        } else {
            fwrite(&node->type, sizeof(unsigned char), 1, out);
            fwrite(&node->red, sizeof(unsigned char), 1, out);
            fwrite(&node->green, sizeof(unsigned char), 1, out);
            fwrite(&node->blue, sizeof(unsigned char), 1, out);
        }
    } else {
        print_level(node->top_left, level - 1, out);
        print_level(node->top_right, level - 1, out);
        print_level(node->bottom_right, level - 1, out);
        print_level(node->bottom_left, level - 1, out);        
    }
}

void get_level_order(TreeNode root, FILE *out)
{
    int height = get_tree_depth(root);
    for (int i = 0; i < height; i++) {
        print_level(root, i, out);
    }
}

void free_tree(TreeNode root)
{
    if (root == NULL) {
        return;
    }
    free_tree(root->top_left);
    free_tree(root->top_right);
    free_tree(root->bottom_right);
    free_tree(root->bottom_left);
    free(root);
}

void free_image(pixel** image, int size)
{
    for (int i = 0; i < size; i++) {
        free(image[i]);
    }
    free(image);
}