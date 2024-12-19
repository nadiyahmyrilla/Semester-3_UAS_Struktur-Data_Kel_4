#include "Tree.h"

// Fungsi untuk menambahkan node ke tree
treeNode* insertTree(treeNode* root, int id, char* judul, char* artis, int durasi, int tahunRilis) {
    if (root == NULL) {
        treeNode* newNode = (treeNode*)malloc(sizeof(treeNode));
        newNode->id = id;
        strcpy(newNode->judul, judul);
        strcpy(newNode->artis, artis);
        newNode->durasi = durasi;
        newNode->tahunRilis = tahunRilis;
        newNode->left = newNode->right = NULL;
        return newNode;
    }

    if (id < root->id) {
        root->left = insertTree(root->left, id, judul, artis, durasi, tahunRilis);
    } else if (id > root->id) {
        root->right = insertTree(root->right, id, judul, artis, durasi, tahunRilis);
    }

    return root;
}

// Fungsi untuk mencetak tree
void printTree(treeNode* root) {
    if (root != NULL) {
        printTree(root->left);
        printf("ID: %d, Judul: %s, Artis: %s, Durasi: %d detik, Tahun Rilis: %d\n", 
                root->id, root->judul, root->artis, root->durasi, root->tahunRilis);
        printTree(root->right);
    }
}