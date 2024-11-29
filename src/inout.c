#include <stdio.h>
#include <string.h>
#include "dto.h"
#include "inout.h"

void printSongInsidePlaylist(struct Playlist* head) {
    struct Playlist* curr = head;
    int nameLength = strlen(head->playlistName);
    int padding = (159 - nameLength - 10) / 2;

    printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", head->playlistName, padding, "=======================================================================================");
    printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");

    while (curr != NULL) {
        struct Song* song = curr->song; 
        while (song != NULL) {  
            printf("%-50s %-50s %-50s %.2f\n", song->title, song->singer, song->album, song->time);
            song = song->next; 
        }
        curr = curr->next; 
    }
    printf("\n");
}

void printPlaylist(struct Playlist* head) {
    struct Playlist* curr = head;
    printf("Playlists you've created:\n");
    int i = 1;
    printf("%-10s %-50s\n", "Number", "Playlist Name");
    while (curr != NULL) {
        printf("%-10d %-50s\n", i, curr->playlistName);
        i++;
        curr = curr->next;
    }
    printf("\n");
}