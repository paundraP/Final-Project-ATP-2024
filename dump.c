#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>


struct Node {
    char singer[50];
    char title[50];
    char album[50];
    double time;
    struct Node* next; 
};

struct Playlist {
    struct Node song;
    struct Playlist* next;
};

struct Node* insertSong(char new_singer[], char new_title[], char new_album[], double new_time)
{
    struct Node* new_node
        = (struct Node*)malloc(sizeof(struct Node));

    strcpy(new_node->singer, new_singer);
    strcpy(new_node->title, new_title);
    strcpy(new_node->album, new_album);
    new_node->time = new_time;

    new_node->next = NULL;

    return new_node;
}

// mengubah node menjadi linkedlist dan menaruh node tersebut didepan rangkaian linkedlist 
// dan jika head masih kosong, bakal assign node menjadi head
struct Node* insertAtBeginning(struct Node* head, char new_singer[], char new_title[], char new_album[], double new_time) 
{
    struct Node* new_node = insertSong(new_singer, new_title, new_album, new_time);
    if (head == NULL){
        return new_node;
    }
    new_node->next = head;
    return new_node;
}

// // memasukan node kedalam rangkaian linkedlist ke paling belakang atau menjadi tail (ekor)
// struct Node* insertAtTheEnd(struct Node* head, char new_singer[], char new_title[], char new_album[], double new_time)
// {
//     struct Node* new_node = insertSong(new_singer, new_title, new_album, new_time);
//     if (head == NULL) {
//         return new_node;
//     }
//     struct Node* temp = head;
//     while(temp->next != NULL) {
//         temp = temp->next;
//     }
//     temp->next = new_node;
//     return head;
// }
// // memasukkan node kedalam rangkaian linkedlist ke indeks tertentu sesuai dengan panjang linkedlist yang akan 
// // dimasuki.
// struct Node* insertInSpesificIndex(struct Node* head, char new_singer[], char new_title[], char new_album[], double new_time, int index) 
// {
//     struct Node* new_node = insertSong(new_singer, new_title, new_album, new_time);
//     if (head == NULL) {
//         return new_node;
//     }
//     struct Node* temp = head;
//     int count = 1;
//     while(temp != NULL && count < index - 1) {
//         temp = temp->next;
//         count++;
//     }
//     if (temp == NULL) {
//         printf("Index lebih dari batas akhir\n");
//         return head;
//     }
//     new_node->next = temp->next;
//     temp->next = new_node;
//     return head;
// }

// menghapus node paling depan (head) dari rangkaian linkedlist
struct Node* deleteAtBeginning(struct Node* head) 
{
    if (head == NULL) {
        printf("List Kosong, tidak ada yang bisa dihapus\n");
        return NULL;
    }

    struct Node* temp = head;
    head = head->next;

    free(temp);
    return head;
}

// menghapus node paling belakang (tail) dari rangkaian linkedlist
struct Node* deleteAtEnd(struct Node* head) 
{
    if (head == NULL) {
        printf("List Kosong, tidak ada yang bisa dihapus\n");
        return NULL;
    }

    if (head->next == NULL) {
        free(head);
        return NULL;
    }

    struct Node* temp = head;
    while (temp->next->next != NULL) {
        temp = temp->next;
    }

    free(temp->next);
    temp->next = NULL;

    return head;
}

// menghapus node dengan indeks yang sesuai dengan panjang linkedlist
struct Node* deleteAtSpecificIndex(struct Node* head, int index) 
{
    if (head == NULL) {
        printf("List Kosong, tidak ada yang bisa dihapus\n");
        return NULL;
    }

    if (index == 1) {
        return deleteAtBeginning(head);
    }

    struct Node* temp = head;
    int count = 1;
    while (temp->next != NULL && count < index - 1) {
        temp = temp->next;
        count++;
    }

    if (temp->next == NULL) {
        printf("Index lebih dari batas akhir\n");
        return head;
    }

    struct Node* nodeToDelete = temp->next;
    temp->next = nodeToDelete->next;

    free(nodeToDelete);

    return head;
}

// memasukkan variabel nama, nrp, no_hp dan menjadikannya sebuah node uyang akan dimasukkan kedalam linkedlist
void inputData(struct Node** head) 
{
    char singer[50], title[50], album[50];
    double time;
    int choice, index;

    printf("\n--- Masukkan lagu kesukaanmu kedalam playlist ---\n");
    printf("Masukkan judul lagu: ");
    scanf(" %[^\n]", title);
    printf("Masukkan nama penyanyi: ");
    scanf(" %[^\n]", singer);
    printf("Masukkan nama album: ");
    scanf(" %[^\n]", album);
    printf("Masukkan panjang lagu (ex: 4.54, in minute): ");
    scanf(" %lf", &time);

    *head = insertAtBeginning(*head, singer, title, album, time);

    printf("Data berhasil dimasukkan\n");
}

// menghapus node
void deleteData(struct Node** head) {
    if (*head == NULL) {
        printf("\nPlayist kosong, tidak ada yang dapat dihapus.\n");
        return;
    }

    int choice, index;
    printf("\n--- Hapus lagu dari playlist ---\n");
    printf("Pilih opsi penghapusan:\n");
    printf("1. Hapus lagu di awal playlist\n2. Hapus lagu di akhir playlist \n3. Hapus lagu di posisi tertentu\nPilihan (1/2/3): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            *head = deleteAtBeginning(*head);
            printf("Lagu di awal berhasil dihapus dari playlist.\n");
            break;
        case 2:
            *head = deleteAtEnd(*head);
            printf("Lagu di akhir berhasil dihapus dari playlist.\n");
            break;
        case 3:
            printf("Masukkan indeks lagu yang ingin dihapus dari playlist (mulai dari 1): ");
            scanf("%d", &index);
            *head = deleteAtSpecificIndex(*head, index);
            printf("Lagu di posisi ke-%d berhasil dihapus dari playlist (jika ada).\n", index);
            break;
        default:
            printf("Pilihan tidak valid.\n");
    }
}

// menampilkan linkedlist
void printList(struct Node* head)
{
    struct Node* curr = head;
    char playlistName[] = "pujogans";
    int nameLength = strlen(playlistName);
    int padding = (159 - nameLength - 10) / 2; // 10 for "Playlist " and spaces

    // Print the top line with the playlist name centered
    printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", playlistName, padding, "=======================================================================================");

    printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");

    while (curr != NULL) {
        printf("%-50s %-50s %-50s %.2f\n", curr->title, curr->singer, curr->album, curr->time);

        curr = curr->next;
    }

    printf("\n");
}

// menu awal program
void menu(char *action)
{
    printf("Selamat Datang di Spotijo\n Spotify nya Pujo\n");
    printf("1. Masukkan lagu kedalam playlist\n2. Hapus lagu dari playlist\n3. Lihat playlist\n4. Keluar\n");
    printf("Pilihan (1/2/3/4): ");
    scanf("%c", action);
}

int main() {
    char action, choice;
    struct Node* head = NULL;
    bool cek = true;
    while(cek) {
        system("clear");   
        menu(&action);
        if (action == '1') {
            inputData(&head); 
            printf("\nTekan esc + enter untuk kembali ke menu...");
            while (getchar() != 27);
        } else if (action == '2') {
            deleteData(&head); 
            printf("\nTekan esc + enter untuk kembali ke menu...");
            while (getchar() != 27);
        } else if (action == '3') {
            if (head == NULL) {
                printf("\nList masih kosong.\n");
            } else {
                printList(head); 
                printf("\nTekan esc + enter untuk kembali ke menu...");
                while (getchar() != 27);
            }
        } else if (action == '4') {
            printf("\nKeluar dari program.\n");
            cek = false;
            break;
        } else {
            printf("\nPilihan tidak valid.\n");
        }
    }
    return 0;
}