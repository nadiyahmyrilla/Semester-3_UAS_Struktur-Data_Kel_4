#include <stdio.h>
#include <stdlib.h>
#include "ManajemenFile.h"

// Fungsi untuk memuat data dari file
void loadFromFile(node **head, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    while (!feof(file)) {
        node *pNew = (node *)malloc(sizeof(node));
        if (fscanf(file, "%d,%99[^,],%99[^,],%d,%d\n", &pNew->id, pNew->judul, pNew->artis, &pNew->durasi, &pNew->tahunRilis) == 5) {
            pNew->right = *head;
            pNew->left = NULL;
            if (*head != NULL) {
                (*head)->left = pNew;
            }
            *head = pNew;
        } else {
            free(pNew); // Jika gagal membaca, hapus node yang tidak terpakai
        }
    }

    fclose(file);
    printf("Data berhasil dimuat dari file %s\n", filename);
}

// Fungsi untuk menyimpan data ke file
void saveToFile(node *head, const char *filename) {
    FILE *file = fopen(filename, "w");
    if (file == NULL) {
        printf("Gagal membuka file %s\n", filename);
        return;
    }

    node *pCur = head;
    while (pCur != NULL) {
        fprintf(file, "%d,%s,%s,%d,%d\n", pCur->id, pCur->judul, pCur->artis, pCur->durasi, pCur->tahunRilis);
        pCur = pCur->right;
    }

    fclose(file);
    printf("Data berhasil disimpan ke file %s\n", filename);
}