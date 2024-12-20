#include "Tree.h"

nodeArtis *insertArtist(nodeArtis* root, const char *namaArtis){
    if (root == NULL) {
        nodeArtis *newArtist = (nodeArtis *)malloc(sizeof(nodeArtis));
        strcpy(newArtist->nama, namaArtis);
        newArtist->songs = NULL; // Tidak ada lagu saat pertama kali
        newArtist->left = newArtist->right = NULL;
        return newArtist;
    }

    if (strcmp(namaArtis, root->nama) < 0) {
        root->left = insertArtist(root->left, namaArtis);
    } else if (strcmp(namaArtis, root->nama) > 0) {
        root->right = insertArtist(root->right, namaArtis);
    }

    return root;
}

void addSongToArtist(nodeArtis *root, const char *namaArtis, int id, const char *judul, int durasi, int tahunRilis) {
    if (root == NULL) {
        return; // Artis tidak ditemukan
    }

    if (strcmp(namaArtis, root->nama) == 0) {
        // Artis ditemukan, tambahkan lagu
        Song *newSong = (Song *)malloc(sizeof(Song));
        newSong->id = id;
        strcpy(newSong->judul, judul);
        newSong->durasi = durasi;
        newSong->tahunRilis = tahunRilis;
        newSong->next = root->songs; // Tambahkan ke awal daftar lagu
        root->songs = newSong;
        return;
    }

    if (strcmp(namaArtis, root->nama) < 0) {
        addSongToArtist(root->left, namaArtis, id, judul, durasi, tahunRilis);
    } else {
        addSongToArtist(root->right, namaArtis, id, judul, durasi, tahunRilis);
    }
}

// Fungsi untuk menampilkan lagu-lagu dari artis tertentu
void displaySongsByArtist(nodeArtis *root, const char *namaArtis) {
    if (root == NULL) {
        printf("Artis tidak ditemukan.\n");
        return;
    }

    if (strcmp(namaArtis, root->nama) == 0) {
        Song *currentSong = root->songs;
        if (currentSong == NULL) {
            printf("Tidak ada lagu untuk artis %s.\n", namaArtis);
            return;
        }
        printf("Lagu-lagu oleh %s:\n", namaArtis);
        while (currentSong != NULL) {
            printf("ID: %d, Judul: %s, Durasi: %d detik, Tahun Rilis: %d\n", currentSong->id, currentSong->judul, currentSong->durasi, currentSong->tahunRilis);
            currentSong = currentSong->next;
        }
        return;
    }

    if (strcmp(namaArtis, root->nama) < 0) {
        displaySongsByArtist(root->left, namaArtis);
    } else {
        displaySongsByArtist(root->right, namaArtis);
    }
}