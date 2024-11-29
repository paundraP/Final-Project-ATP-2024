#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "inout.h"

// Create a Playlist
struct Playlist* createPlaylist(char name[]){
    struct Playlist* new_playlist = (struct Playlist*)malloc(sizeof(struct Playlist));
    strcpy(new_playlist->playlistName, name);
    new_playlist->song = NULL;
    new_playlist->next = NULL;

    return new_playlist;
}

//Create a Song
struct Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time){
    struct Song* new_song = (struct Song*)malloc(sizeof(struct Song));
    strcpy(new_song->title, new_title);
    strcpy(new_song->singer, new_singer);
    strcpy(new_song->album, new_album);
    new_song->time = new_time;
    new_song->next = NULL;
    return new_song;
}

// Adding and Remove song in Playlist 
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

struct Playlist* addNewPlaylist(struct Playlist* head, char playlistname[]){
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

int main() {
    struct Song* songs = createSong("the 1975", "about you", "dont know", 5.45);
    struct Song* songs1 = createSong("the 1975", "about you", "dont know", 5.45);
    struct Playlist* playlists = createPlaylist("pujo ganteng");
    addSongtoPlaylist(playlists, songs);
    addSongtoPlaylist(playlists, songs1);
    playlists = addNewPlaylist(playlists, "Pujo sedih");
    playlists = addNewPlaylist(playlists, "Pujo bahagia");
    printPlaylist(playlists);
    printSongInsidePlaylist(playlists);
    free(songs);
    free(playlists);

    return 0;
}