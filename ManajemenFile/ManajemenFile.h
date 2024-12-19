#ifndef MANAJEMEN_FILE_H
#define MANAJEMEN_FILE_H

#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
//===================DOUBLE LINKED LIST=============================
struct node {
    int id;                
    char judul[100];
    char artis[100];
    int durasi;             // Durasi Lagu (dalam detik)
    int tahunRilis;
    struct node *left;
    struct node *right;
};
typedef struct node node;

// Fungsi untuk memuat data dari file
void loadFromFile(node **head, const char *filename);
// Fungsi untuk menyimpan data ke file
void saveToFile(node *head, const char *filename);

#endif