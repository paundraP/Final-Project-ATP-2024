#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"

Playlist* createPlaylist(char name[]){
    Playlist* new_playlist = (Playlist*)malloc(sizeof(Playlist));
    strcpy(new_playlist->playlistName, name);
    new_playlist->song = NULL;
    new_playlist->next = NULL;

    return new_playlist;
}

Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time){
    Song* new_song = (Song*)malloc(sizeof(Song));
    strcpy(new_song->title, new_title);
    strcpy(new_song->singer, new_singer);
    strcpy(new_song->album, new_album);
    new_song->time = new_time;
    new_song->next = NULL;
    return new_song;
}

void addSongtoPlaylist(Playlist* playlist, Song* song){
    if(playlist->song == NULL) {
        playlist->song = song;
    }else {
        Song* current = playlist->song;
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
    Playlist* temp = head;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_playlist;
    return head;
}

Playlist* deleteSongFromPlaylist(Playlist* playlist, char songName[]){
    //implementasi disini
}
