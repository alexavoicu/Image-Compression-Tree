/*VOICU Alexa-Andreea-312CD*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tree.h"

int main(int argc, char *argv[]) {
    char *in_file ;
    char *out_file;
    int option = 0;
    int factor = 0;
    //extragerea informatiilor din linia de comanda
    if (argc >= 4) {
        if (strcmp(argv[1], "-c1") == 0) {
            option = 1;
            factor = atoi(argv[2]);
        } else if (strcmp(argv[1], "-c2") == 0) {
            option = 2;
            factor = atoi(argv[2]);
        } else if (strcmp(argv[1], "-d") == 0) {
            option = 3;
        } 
        in_file = argv[3];
        out_file = argv[4];
    } else {
        in_file = argv[1];
        out_file = argv[2];
    }
    //declararea variabilelor de care ne folosim pentru a extrage informatiile din fisier
    FILE* fin;
    FILE* fout;
    char file_type[3];
    int width, height, maxval;
    pixel **image;
    int count = 0;
    //citirea din fisier
    fin = fopen(in_file, "rb");
    if(option == 1)
    fout = fopen(out_file, "w");
    if(option == 2)
    fout = fopen(out_file, "wb");
    fscanf(fin, "%s %d %d %d", file_type, &width, &height, &maxval);
    fseek(fin, 1, SEEK_CUR);
    unsigned char *image_info = malloc(width * height * 3 * sizeof(unsigned char));//citeste imaginea ca o zona continua de memorie
    fread(image_info, sizeof(unsigned char), width * height * 3, fin);
    fclose(fin);
    //introducerea informatiilor in structurile ce vor fi operate
    image = (pixel **)malloc(width * sizeof(pixel *));
    for (int i = 0; i < width; i++) {
        image[i] = (pixel *)malloc(height * sizeof(pixel));
    }    
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {//pune datele din vector in matrice
            image[i][j].red = image_info[count];
            image[i][j].green = image_info[count + 1];
            image[i][j].blue = image_info[count + 2];
            count += 3;
        }
    }
    int max_leaf_size = 0;//creearea arborelui cuaternar
    TreeNode root =  create_tree(image, 0, 0, width, factor, &max_leaf_size);
    //rezolvarea cerinteli in functie de numarul acesteia
    if (option == 1) {
        int depth = get_tree_depth(root);
        int num_leafs = get_num_leaves(root);
        fprintf(fout, "%d\n%d\n%d\n", depth, num_leafs, max_leaf_size);
    }
    if (option == 2) {
        unsigned int dimension = (unsigned int)width;
        fwrite(&dimension, sizeof(unsigned int), 1, fout);
        get_level_order(root, fout);
    }
    //eliberarea memoriei
    free_tree(root);
    free(image_info);
    free_image(image, width);
    fclose(fout); 

    return 0;
}
