#include <stdio.h>
#include <conio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//===================DOUBLE LINKED LIST=============================
struct node
{
    int id;
    char judul[100];
    char artis[100];
    int durasi; // Durasi Lagu (dalam detik)
    int tahunRilis;
    struct node *left;
    struct node *right;
};
typedef struct node node;

void tambahAwal(node **head);
void tambahData(node **head);
void tambahAkhir(node **head);
void hapusAwal(node **head);
void hapusData(node **head);
void hapusAkhir(node **head);
void totalData(node **head);
void totalValue(node **head);
bool cariData(node *head, int targetID);
void tranverse(node *head);
//==================================================================
//===================QUEUE==========================================
typedef struct queueNode
{
    int id;
    char judul[100];
    char artis[100];
    int durasi;
    int tahunRilis;
    struct queueNode *next;
} queueNode;

typedef struct
{
    queueNode *front;
    queueNode *rear;
    int count;
} queue;

// fungsi untuk queue
queue createQueue();
queueNode *findLaguById(node *head, int id);
int enqueue(queueNode *lagu, queue *myQueue);
void dequeue(queue *myQueue);
void display(queue myQueue);
void destroy(queue *myQueue);
void findMyLagu(queue *myQueue);
//==================================================================
//===================STACK==========================================
typedef struct nodeStack
{
    queueNode *song;
    struct nodeStack *next;
} nodeStack;

typedef struct Stack
{
    nodeStack *top;
} Stack;

Stack stack;

// fungsi stack
void createStack();
bool isEmpty(Stack *myStack);
void push(Stack *myStack, queueNode *newSong);
queueNode *pop(Stack *myStack);
queueNode *stackTop(Stack *myStack);
void destroyStack(Stack *myStack);
void printStack(Stack *myStack);
int stackCount(Stack *myStack);
void undoMultipleSongs(queue *q, Stack *myStack, int count);

//==================================================================
//===================CIRCULAR LINKED LIST===========================
/*Fungsi untuk membuat node baru*/
struct nodeCircular
{
    char judul[100];
    char artis[100];
    int durasi;
    struct nodeCircular *next;
};
typedef struct nodeCircular nodeCircular;

nodeCircular *createNode(char *judul, char *artis, int durasi);
void enqueueFromQueue(queue *myQueue, nodeCircular **circularHead);
void playNextSong(nodeCircular *circularHead);
//==================================================================
//========================GLOBAL VARIABLE===========================
queue myQueue;
Stack myStack;
//==================================================================
//====================DATA UTAMA====================================
int main()
{
    node *head = NULL;
    char pilih;
    int pilih1;
    nodeCircular *circularHead = NULL;

    head = NULL;
    do
    {
        system("cls");
        printf("================MENU UTAMA==================\n");
        printf("Masukkan Apa Yang Ingin Dilakukan\n");
        printf("1. Daftar Lagu\n");
        printf("2. Daftar Putar Lagu\n");
        printf("3. Undo Hapus Lagu\n");
        printf("MASUKKAN PILIHAN (tekan c untuk logout) : ");
        fflush(stdin);
        scanf("%c", &pilih);
        if (pilih == '1')
        {
            head = NULL;
            do
            {
                system("cls");
                printf("---------MENU DAFTAR LAGU-----------------\n");
                printf("1. Tambah lagu diawal\n");
                printf("2. Tambah lagu ditengah daftar\n");
                printf("3. Tambah lagu diakhir\n");
                printf("4. Hapus lagu diawal\n");
                printf("5. Hapus lagu ditengah daftar\n");
                printf("6. Hapus lagu diakhir\n");
                printf("7. Total jumlah lagu\n");
                printf("8. Mencari lagu didalam daftar\n");
                printf("9. Cetak isi daftar lagu\n");
                printf("10. Cetak album Artis\n");
                printf("MASUKKAN PILIHAN (tekan 0 untuk logout) : ");
                fflush(stdin);
                scanf("%d", &pilih1);
                if (pilih1 == 1)
                {
                    tambahAwal(&head);
                    getch();
                }
                else if (pilih1 == 2)
                {
                    tambahData(&head);
                    getch();
                }
                else if (pilih1 == 3)
                {
                    tambahAkhir(&head);
                    getch();
                }
                else if (pilih1 == 4)
                {
                    hapusAwal(&head);
                    getch();
                }
                else if (pilih1 == 5)
                {
                    hapusData(&head);
                    getch();
                }
                else if (pilih1 == 6)
                {
                    hapusAkhir(&head);
                    getch();
                }
                else if (pilih1 == 7)
                {
                    totalData(&head);
                    getch();
                }
                else if (pilih1 == 8)
                {
                    int targetID;
                    printf("\nMasukkan ID Lagu yang ingin dicari: ");
                    scanf("%d", &targetID);
                    // karean boolean menggunakan ini untuk memanggil
                    if (!cariData(head, targetID))
                    {
                        printf("Lagu dengan ID %d tidak ditemukan.\n", targetID);
                    }
                    getch();
                }
                else if (pilih1 == 9)
                {
                    tranverse(head);
                    getch();
                }
                else
                {
                    printf("\nInvalid Choice\n");
                }
            } while (pilih1 != 0);
        }
        else if (pilih == '2')
        {
            int success = 0;
            int num;
            int idlagu;
            queue myQueue = createQueue();

            do
            {
                system("cls");
                printf("\n-----MENU DAFTAR PUTAR-----");
                printf("\n1. Menambah daftar putar lagu");
                printf("\n2. Menghapus daftar putar lagu");
                printf("\n3. Display daftar putar lagu");
                printf("\n4. Menghapus seluruh daftar putar lagu");
                printf("\n5. Cari Lagu di Daftar Putar (findMyLagu)");
                printf("\n6. Putar Lagu Secara Berulang");
                printf("\nMasukan pilihan (gunakan 'q' untuk exit): ");
                scanf(" %c", &pilih);
                if (pilih == '1')
                {
                    printf("\nMasukkan ID Lagu yang ingin ditambahkan: ");
                    if (scanf("%d", &idlagu) != 1)
                    {
                        printf("Input ID lagu tidak valid!\n");
                        continue;
                    }
                    queueNode *lagu = findLaguById(head, idlagu);

                    if (lagu == NULL)
                    {
                        printf("Lagu dengan ID %d tidak ditemukan!\n", idlagu);
                    }
                    else
                    {
                        if (enqueue(lagu, &myQueue))
                        {
                            enqueueFromQueue(&myQueue, &circularHead);
                        }
                        else
                        {
                            printf("Gagal menambahkan lagu ke daftar putar.\n");
                        }
                    }
                    getch();
                }
                else if (pilih == '2')
                {
                    if (myQueue.front != NULL)
                    {
                        dequeue(&myQueue);
                    }
                    else
                    {
                        printf("\nLagu berhasil dihapus dari playlist.\n");
                        printf("*Sihlahkan ke menu undo jika salah menghapus lagu.");
                    }
                    getch();
                }
                else if (pilih == '3')
                {
                    display(myQueue);
                    getch();
                }
                else if (pilih == '4')
                {
                    destroy(&myQueue);
                    circularHead = NULL;
                    printf("\nSeluruh daftar putar lagu berhasil dihapus.\n");
                    printf("*Sihlahkan ke menu undo jika salah menghapus lagu.");
                    getch();
                }
                else if (pilih == '5')
                {
                    findMyLagu(&myQueue);
                    getch();
                }
                else if (pilih == '6')
                {
                    playNextSong(circularHead);
                    getch();
                }
            } while (pilih != 'q');
        }
        else if (pilih == '3')
        {
            head = NULL;
            do
            {
                system("cls");
                printf("---------MENU UNDO LAGU-----------------\n");
                printf("1. Undo Penghapusan Lagu\n");
                printf("2. Tampilkan Riwayat Penghapusan Lagu\n");
                printf("3. Tampilkan Jumlah lagu yang dihapus\n");
                printf("4. Hapus Semua Riwayat Penghapusan Lagu\n");
                printf("MASUKKAN PILIHAN (tekan q untuk logout) : ");
                fflush(stdin);
                scanf("%c", &pilih);
                if (pilih == '1')
                {
                    int jumlahUndo;
                    printf("Masukkan jumlah lagu yang ingin di-undo: ");
                    scanf("%d", &jumlahUndo);
                    undoMultipleSongs(&myQueue, &myStack, jumlahUndo);
                    getch();
                }
                else if (pilih == '2')
                {
                    printStack(&myStack);
                    getch();
                }
                else if (pilih == '3')
                {
                    stackCount(&myStack);
                    getch();
                }
                else if (pilih == '4')
                {
                    destroyStack(&myStack);
                    getch();
                }
                else
                {
                    printf("\nInvalid Choice\n");
                }
            } while (pilih != 'q');
        }
        else
        {
            continue;
        }
    } while (pilih != 'c');

    return 0;
}
//================================================================
//===================DOUBLE LINKED LIST=============================
// Fungsi untuk menambahkan data di awal linked list
void tambahAwal(node **head)
{
    node *pNew = (node *)malloc(sizeof(node));

    printf("\nMasukkan ID Lagu: ");
    scanf("%d", &pNew->id);

    // Cek apakah ID sudah ada menggunakan cariData
    if (cariData(*head, pNew->id))
    { // Perbaiki di sini
        printf("ID Lagu sudah ada, tidak dapat menambah data.\n");
        free(pNew); // Menghapus node yang sudah dialokasikan
        return;
    }
    getchar();

    printf("Masukkan Judul Lagu: ");
    fgets(pNew->judul, sizeof(pNew->judul), stdin);
    pNew->judul[strcspn(pNew->judul, "\n")] = 0; // Menghilangkan newline

    printf("Masukkan Nama Artis: ");
    fgets(pNew->artis, sizeof(pNew->artis), stdin);
    pNew->artis[strcspn(pNew->artis, "\n")] = 0;

    printf("Masukkan Durasi Lagu (dalam detik): ");
    scanf("%d", &pNew->durasi);

    printf("Masukkan Tahun Rilis: ");
    scanf("%d", &pNew->tahunRilis);

    pNew->right = *head;
    pNew->left = NULL;
    if (*head != NULL)
    {
        (*head)->left = pNew;
    }
    *head = pNew;
}

// Fungsi untuk menambahkan data di posisi tertentu dalam linked list
void tambahData(node **head)
{
    int pos, count = 1;
    node *pCur = *head;
    node *pNew = (node *)malloc(sizeof(node));

    printf("\nMasukkan posisi untuk menambah data lagu: ");
    scanf("%d", &pos);

    printf("Masukkan ID Lagu: ");
    scanf("%d", &pNew->id);

    // Cek apakah ID sudah ada menggunakan cariData
    if (cariData(*head, pNew->id))
    {
        printf("ID Lagu sudah ada, tidak dapat menambah data.\n");
        free(pNew);
        return;
    }
    getchar();

    printf("Masukkan Judul Lagu: ");
    fgets(pNew->judul, sizeof(pNew->judul), stdin);
    pNew->judul[strcspn(pNew->judul, "\n")] = 0;

    printf("Masukkan Nama Artis: ");
    fgets(pNew->artis, sizeof(pNew->artis), stdin);
    pNew->artis[strcspn(pNew->artis, "\n")] = 0;

    printf("Masukkan Durasi Lagu (dalam detik): ");
    scanf("%d", &pNew->durasi);

    printf("Masukkan Tahun Rilis: ");
    scanf("%d", &pNew->tahunRilis);

    pNew->right = NULL;
    pNew->left = NULL;

    if (pos == 1)
    {
        pNew->right = *head;
        if (*head != NULL)
        {
            (*head)->left = pNew;
        }
        *head = pNew;
        return;
    }
    while (pCur != NULL && count < pos - 1)
    {
        pCur = pCur->right;
        count++;
    }
    if (pCur == NULL)
    {
        printf("Posisi tidak valid, menambah data lagu di akhir.\n");
        while (pCur->right != NULL)
        {
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
    else
    {
        pNew->right = pCur->right;
        pCur->right = pNew;
        pNew->left = pCur;
        if (pNew->right != NULL)
        {
            pNew->right->left = pNew;
        }
    }
}

// Fungsi untuk menambahkan data di akhir linked list
void tambahAkhir(node **head)
{
    node *pNew = (node *)malloc(sizeof(node));
    node *pCur = *head;

    printf("\nMasukkan ID Lagu: ");
    scanf("%d", &pNew->id);

    // Cek apakah ID sudah ada menggunakan cariData
    if (cariData(*head, pNew->id))
    {
        printf("ID Lagu sudah ada, tidak dapat menambah data.\n");
        free(pNew);
        return;
    }
    getchar();

    printf("Masukkan Judul Lagu: ");
    fgets(pNew->judul, sizeof(pNew->judul), stdin);
    pNew->judul[strcspn(pNew->judul, "\n")] = 0;

    printf("Masukkan Nama Artis: ");
    fgets(pNew->artis, sizeof(pNew->artis), stdin);
    pNew->artis[strcspn(pNew->artis, "\n")] = 0;

    printf("Masukkan Durasi Lagu (dalam detik): ");
    scanf("%d", &pNew->durasi);

    printf("Masukkan Tahun Rilis: ");
    scanf("%d", &pNew->tahunRilis);

    pNew->right = NULL;

    if (*head == NULL)
    {
        *head = pNew;
        pNew->left = NULL;
    }
    else
    {
        while (pCur->right != NULL)
        {
            pCur = pCur->right;
        }
        pCur->right = pNew;
        pNew->left = pCur;
    }
}

// Fungsi untuk menghapus data di awal linked list
void hapusAwal(node **head)
{
    node *pCur;

    if (*head == NULL)
    {
        printf("Daftar lagu kosong.\n");
        return;
    }
    pCur = *head;
    *head = pCur->right;
    if (*head != NULL)
    {
        (*head)->left = NULL;
    }

    free(pCur);
    printf("\nData lagu di awal berhasil dihapus.\n");
}

// Fungsi untuk menghapus data di posisi tertentu dalam linked list
void hapusData(node **head)
{
    int pos, count = 1;
    node *pCur = *head;
    node *pPrev = NULL;

    printf("\nMasukkan posisi data lagu yang ingin dihapus: ");
    scanf("%d", &pos);

    if (pos == 1)
    {
        hapusAwal(head);
        return;
    }
    while (pCur != NULL && count < pos)
    {
        pPrev = pCur;
        pCur = pCur->right;
        count++;
    }
    if (pCur == NULL)
    {
        printf("Posisi tidak ditemukan.\n");
        return;
    }
    pPrev->right = pCur->right;
    if (pCur->right != NULL)
    {
        pCur->right->left = pPrev;
    }

    free(pCur);
    printf("Data lagu di posisi %d berhasil dihapus.\n", pos);
}

// Fungsi untuk menghapus data di akhir linked list
void hapusAkhir(node **head)
{
    node *pCur = *head;

    if (*head == NULL)
    {
        printf("Daftar lagu kosong.\n");
        return;
    }
    if (pCur->right == NULL)
    {
        free(pCur);
        *head = NULL;
    }
    else
    {
        while (pCur->right != NULL)
        {
            pCur = pCur->right;
        }
        pCur->left->right = NULL;
        free(pCur);
    }

    printf("\nData di akhir berhasil dihapus.\n");
}

// Fungsi untuk menghitung total data di linked list
void totalData(node **head)
{
    node *pCur = *head;
    int count = 0;

    while (pCur != NULL)
    {
        count++;
        pCur = pCur->right;
    }
    printf("\nJumlah daftar lagu: %d\n", count);
}

// Fungsi untuk mencari data berdasarkan ID
bool cariData(node *head, int targetID)
{
    node *pCur = head;

    while (pCur != NULL)
    {
        if (pCur->id == targetID)
        {
            // Jika ID ditemukan, tampilkan informasi lagu
            printf("\nDetail lagu:\n");
            printf("ID: %d\n", pCur->id);
            printf("Judul: %s\n", pCur->judul);
            printf("Artis: %s\n", pCur->artis);
            printf("Durasi: %d detik\n", pCur->durasi);
            printf("Tahun Rilis: %d\n", pCur->tahunRilis);
            return true; // ID ditemukan
        }
        pCur = pCur->right;
    }
    // Jika tidak ditemukan
    return false; // ID tidak ditemukan
}

// Fungsi untuk menampilkan seluruh daftar lagu
void tranverse(node *head)
{
    node *pCur = head;
    if (pCur == NULL)
    {
        printf("Daftar lagu kosong.\n");
    }
    else
    {
        printf("-----------------------------------------------------------------------------------------------------\n");
        printf("  ID Lagu         Judul Lagu       Nama Artis           Durasi Lagu(dalam detik)        Tahun Rilis  \n");
        printf("-----------------------------------------------------------------------------------------------------\n");
        while (pCur != NULL)
        {
            printf("  %-20d %-15s %-25s %-30d %-12d \n", pCur->id, pCur->judul, pCur->artis, pCur->durasi, pCur->tahunRilis);
            pCur = pCur->right;
        }
    }
}
//==================================================================
//===========================QUEUUE==================================
// Fungsi untuk membuat queue
queue createQueue()
{
    queue myQueue;
    myQueue.count = 0;
    myQueue.front = myQueue.rear = NULL;
    return myQueue;
}
// Fungsi untuk mencari lagu di dalam queue (findMyLagu) berdasarkan ID
void findMyLagu(queue *myQueue)
{
    int targetID;
    queueNode *pCur = myQueue->front;

    printf("\n--- Cari Lagu di Daftar Putar ---\n");
    printf("Masukkan ID Lagu yang ingin dicari: ");
    scanf("%d", &targetID);

    while (pCur != NULL)
    {
        if (pCur->id == targetID)
        {
            printf("\nLagu ditemukan:\n");
            printf("ID: %d\n", pCur->id);
            printf("Judul: %s\n", pCur->judul);
            printf("Artis: %s\n", pCur->artis);
            printf("Durasi: %d detik\n", pCur->durasi);
            printf("Tahun Rilis: %d\n", pCur->tahunRilis);
            return;
        }
        pCur = pCur->next;
    }
    printf("Lagu dengan ID %d tidak ditemukan.\n", targetID);
}

// Fungsi untuk mencari lagu berdasarkan ID di linked list
queueNode *findLaguById(node *head, int id)
{
    node *current = head;
    while (current != NULL)
    {
        if (current->id == id)
        {
            queueNode *qNode = (queueNode *)malloc(sizeof(queueNode));
            qNode->id = current->id;
            strcpy(qNode->judul, current->judul);
            strcpy(qNode->artis, current->artis);
            qNode->durasi = current->durasi;
            qNode->tahunRilis = current->tahunRilis;
            qNode->next = NULL;
            return qNode;
        }
        current = current->right;
    }
    return NULL;
}

// Fungsi untuk menambahkan elemen ke dalam queue (enqueue)
int enqueue(queueNode *lagu, queue *myQueue)
{
    if (myQueue->count == 0)
    {
        myQueue->front = myQueue->rear = lagu;
    }
    else
    {
        myQueue->rear->next = lagu;
        myQueue->rear = lagu;
    }

    myQueue->count++;
    printf("Lagu dengan ID %d berhasil ditambahkan ke playlist.\n", lagu->id);
    return 1;
}

// Fungsi untuk menghapus lagu dari queue (dequeue)
void dequeue(queue *myQueue)
{
    queueNode *temp = myQueue->front;

    push(&myStack, temp);

    myQueue->front = myQueue->front->next;
    if (myQueue->front == NULL)
    {
        myQueue->rear = NULL;
    }

    free(temp);
    myQueue->count--;
}

// Fungsi untuk menampilkan semua lagu di queue
void display(queue myQueue)
{
    if (myQueue.count == 0)
    {
        printf("Daftar putar lagu kosong.\n");
        return;
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("  ID Lagu         Judul Lagu       Nama Artis           Durasi Lagu(dalam detik)        Tahun Rilis  \n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    queueNode *temp = myQueue.front;
    while (temp != NULL)
    {
        printf("  %-20d %-15s %-25s %-30d %-12d \n", temp->id, temp->judul, temp->artis, temp->durasi, temp->tahunRilis);
        temp = temp->next;
    }
    printf("\n");
}

// menghapus seluruh antrian
void destroy(queue *myQueue)
{
    while (myQueue->front != NULL)
    {
        dequeue(myQueue);
    }
}
//======================================================================
//=============================STACK====================================
// fungsi untuk membuat stack
void createStack()
{
    stack.top = NULL;
}

bool isEmpty(Stack *myStack)
{
    return myStack->top == NULL;
}

void push(Stack *myStack, queueNode *newSong)
{
    nodeStack *newNode = (nodeStack *)malloc(sizeof(nodeStack));
    if (newNode == NULL)
    {
        printf("Gagal mengalokasikan memori untuk node stack!\n");
        return;
    }

    newNode->song = (queueNode *)malloc(sizeof(queueNode));
    if (newNode->song == NULL)
    {
        printf("Gagal mengalokasikan memori untuk lagu!\n");
        free(newNode);
        return;
    }
    memcpy(newNode->song, newSong, sizeof(queueNode));
    newNode->next = myStack->top;
    myStack->top = newNode;
}

queueNode *pop(Stack *myStack)
{
    if (isEmpty(myStack))
    {
        return NULL;
    }
    nodeStack *temp = myStack->top;
    queueNode *song = temp->song;
    myStack->top = myStack->top->next;
    free(temp);
    return song;
}

// Fungsi Undo untuk memindahkan lagu dari Stack ke Queue
void undoMultipleSongs(queue *q, Stack *myStack, int count)
{
    int undoneCount = 0;
    for (int i = 0; i < count; i++)
    {
        if (isEmpty(myStack))
        {
            printf("Hanya %d lagu yang berhasil di-undo.\n", undoneCount);
            break;
        }

        queueNode *recoveredSong = pop(myStack);
        if (recoveredSong != NULL)
        {
            enqueue(recoveredSong, q);
            undoneCount++;
        }
    }
    printf("%d lagu berhasil di-undo dan dikembalikan ke playlist.\n", undoneCount);
}

// Menghitung jumlah lagu yang ada di stack
int stackCount(Stack *myStack)
{
    int count = 0;
    nodeStack *current = myStack->top;
    while (current != NULL)
    {
        count++;
        current = current->next;
    }
    printf("\nJumlah lagu yang dihapus: %d\n", count); // Cetak jumlah elemen di stack
    return count;
}

// Menghapus seluruh isi stack
void destroyStack(Stack *myStack)
{
    while (!isEmpty(myStack))
    {
        pop(myStack); // Pop setiap elemen hingga stack kosong
    }
    printf("\nSemua riwayat penghapusan lagu telah dihapus.\n");
}

// Menampilkan seluruh lagu yang dihapus di stack
void printStack(Stack *myStack)
{
    if (isEmpty(myStack))
    {
        printf("Stack kosong! Tidak ada riwayat penghapusan lagu.\n");
        return;
    }

    nodeStack *current = myStack->top;
    printf("-----------------------------------------------------------------------------------------------------\n");
    printf("  ID Lagu         Judul Lagu       Nama Artis           Durasi Lagu(dalam detik)        Tahun Rilis  \n");
    printf("-----------------------------------------------------------------------------------------------------\n");
    while (current != NULL)
    {
        printf("  %-15d %-20s %-25s %-30d %-12d\n",
            current->song->id,
            current->song->judul,
            current->song->artis,
            current->song->durasi,
            current->song->tahunRilis);
        current = current->next;
    }
    printf("-----------------------------------------------------------------------------------------------------\n");
}

//======================================================================
//=============================CIRCULAR LINKED LIST=====================
// Membuat node baru bernama lagu yang berisi informasi lagu
nodeCircular *createNode(char *judul, char *artis, int durasi)
{
    nodeCircular *newNode = (nodeCircular *)malloc(sizeof(nodeCircular));
    strcpy(newNode->judul, judul);
    strcpy(newNode->artis, artis);
    newNode->durasi = durasi;
    newNode->next = newNode;
    return newNode;
}

// Menambahkan lagu dari queue ke circular linked list
void enqueueFromQueue(queue *myQueue, nodeCircular **circularHead)
{
    if (myQueue->count == 0)
    {
        printf("Queue kosong! Tidak ada lagu untuk dipindahkan.\n");
        return;
    }
    // Mengambil node dari queue
    queueNode *queueNode = myQueue->front;

    // Membuat nodeCircular baru
    nodeCircular *newNode = createNode(queueNode->judul, queueNode->artis, queueNode->durasi);

    // Jika circular list kosong
    if (*circularHead == NULL)
    {
        *circularHead = newNode;
        newNode->next = newNode;
    }
    else
    {
        nodeCircular *temp = *circularHead;
        while (temp->next != *circularHead)
        {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = *circularHead;
    }

    printf("Lagu '%s' berhasil ditambahkan ke daftar putar circular.\n", newNode->judul);
}

void playNextSong(nodeCircular *circularHead)
{
    if (circularHead == NULL)
    {
        printf("Daftar putar circular kosong.\n");
        return;
    }

    nodeCircular *pCur = circularHead;
    printf("Lagu yang akan diputar selanjutnya:\n");
    do
    {
        printf("Judul: %s\n Artis: %s\n %d detik\n", pCur->judul, pCur->artis, pCur->durasi);
        pCur = pCur->next;
    } while (pCur != circularHead);
}
//======================================================================
