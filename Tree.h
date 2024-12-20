#ifndef MANAJEMEN_TREE_H
#define MANAJEMEN_TREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Struct Tree
struct Song {
    int id;
    char judul[100];
    int durasi;             
    int tahunRilis;
    struct Song *next;
};
typedef struct Song Song;

struct nodeArtis{
    char nama[100];
    struct Song *songs; // Pointer ke lagu-lagu artis
    struct nodeArtis *left; // Pointer ke artis di kiri
    struct nodeArtis *right; // Pointer ke artis di kanan
};
typedef struct nodeArtis nodeArtis;

nodeArtis *insertArtist(nodeArtis* root, const char *namaArtis);

void addSongToArtist(nodeArtis *root, const char *namaArtis, int id, const char *judul, int durasi, int tahunRilis);

void displaySongsByArtist(nodeArtis *root, const char *namaArtis);

#endif