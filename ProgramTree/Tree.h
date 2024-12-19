#ifndef MANAJEMEN_MUSIK_H
#define MANAJEMEN_MUSIK_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Tree
struct treeNode {
    int id;
    char judul[100];
    char artis[100];
    int durasi;             
    int tahunRilis;
    struct treeNode *left;
    struct treeNode *right;
};
typedef struct treeNode treeNode;

// Fungsi untuk menambahkan node ke tree
treeNode* insertTree(treeNode* root, int id, char* judul, char* artis, int durasi, int tahunRilis);

// Fungsi untuk mencetak tree
void printTree(treeNode* root);

#endif