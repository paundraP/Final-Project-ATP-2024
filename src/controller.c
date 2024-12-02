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

Playlist* addNewPlaylist(Playlist* playlist, char playlistname[]){
    Playlist* new_playlist = createPlaylist(playlistname);
    if(playlist == NULL){
        return new_playlist;
    }
    Playlist* temp = playlist;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = new_playlist;
    return playlist;
}

Playlist* deleteSongFromPlaylist(Playlist* playlist, char songName[]){
    //implementasi disini
}

Playlist* deletePlaylist(Playlist* playlist){

}