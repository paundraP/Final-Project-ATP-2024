#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "dto.h"


struct Playlist* createPlaylist(char name[], struct Song* song){
    struct Playlist* new_playlist = (struct Playlist*)malloc(sizeof(struct Playlist));
    strcpy(new_playlist->playlistName, name);
    new_playlist->song = song;
    new_playlist->next = NULL;

    return new_playlist;
}

struct Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time){
    struct Song* new_song = (struct Song*)malloc(sizeof(struct Song));
    strcpy(new_song->title, new_title);
    strcpy(new_song->singer, new_singer);
    strcpy(new_song->album, new_album);
    new_song->time = new_time;
    new_song->next = NULL;
    return new_song;
}

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

int main() {
    struct Song* songs = createSong("the 1975", "about you", "dont know", 5.45);
    struct Playlist* playlists = createPlaylist("pujo ganteng", songs);
    printList(playlists);
    free(songs);
    free(playlists);

    return 0;
}