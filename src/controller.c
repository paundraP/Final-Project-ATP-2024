#include <string.h>
#include <stdlib.h>
#include "dto.h"

struct Playlist* createPlaylist(char name[]){
    struct Playlist* new_playlist = (struct Playlist*)malloc(sizeof(struct Playlist));
    strcpy(new_playlist->playlistName, name);
    new_playlist->song = NULL;
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

void addSongtoPlaylist(struct Playlist* playlist, struct Song* song){
    if(playlist->song == NULL) {
        playlist->song = song;
    }else {
        struct Song* current = playlist->song;
        while (current->next != NULL) {
            current = current->next;
        }
        current->next = song;
    }
}

int playlistExists(struct Playlist* head, char playlistname[]) {
    struct Playlist* temp = head;
    while (temp != NULL) {
        if (strcmp(temp->playlistName, playlistname) == 0) {
            return 1; 
        }
        temp = temp->next;
    }
    return 0;
}

struct Playlist* addNewPlaylist(struct Playlist* head, char playlistname[]){
    if (playlistExists(head, playlistname)) {
        printf("Playlist with the name '%s' already exists.\n", playlistname);
        return head;
    }

    struct Playlist* new_playlist = createPlaylist(playlistname);
    if(head == NULL){
        return new_playlist;
    }
    struct Playlist* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_playlist;
    return head;
}

struct Playlist* deleteSongFromPlaylist(struct Playlist* head, char songName[]){
    //implementasi disini
}
