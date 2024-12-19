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
void printTree(treeNode *root) {
    if (root == NULL) {
        return;
    }

    // Traverse ke kiri
    printTree(root->left);

    // Cetak informasi artis
    printf("%s\n", root->artis);
    
    // Cetak lagu-lagu di bawah artis
    treeNode *currentSong = root->next; // Asumsikan next menunjuk ke lagu-lagu
    while (currentSong != NULL) {
        printf("   %s\n", currentSong->judul);
        printf("      Durasi: %d detik\n", currentSong->durasi);
        printf("      Tahun Rilis: %d\n", currentSong->tahunRilis);
        currentSong = currentSong->next; // Pindah ke lagu berikutnya
    }
    printf("\n"); // Tambahkan baris kosong untuk pemisah antar artis

    // Traverse ke kanan
    printTree(root->right);
}