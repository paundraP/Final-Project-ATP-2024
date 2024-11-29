#include <stdio.h>
#include <string.h>
#include "dto.h"
#include "inout.h"

void printList(struct Playlist* head) {
    struct Playlist* curr = head;
    int nameLength = strlen(head->playlistName);
    int padding = (159 - nameLength - 10) / 2;

    printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", head->playlistName, padding, "=======================================================================================");
    printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");

    while (curr != NULL) {
        if (curr->song != NULL) {  
            printf("%-50s %-50s %-50s %.2f\n", curr->song->title, curr->song->singer, curr->song->album, curr->song->time);
        }
        curr = curr->next;
    }
    printf("\n");
}