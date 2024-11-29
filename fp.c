#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

struct Song {
    char title[50];
    char singer[50];
    char album[50];
    double time;
    struct Song* next; 
};

struct Playlist {
    char playlistName[50];
    struct Song* song;
    struct Playlist* next;
};


struct Playlist* createPlaylist(char name[], struct Song* song){
    struct Playlist* new_playlist = (struct Playlist*)malloc(sizeof(struct Playlist));
    strcpy(new_playlist->playlistName, name);
    new_playlist->song = NULL;
    new_playlist->next = NULL;

    return new_playlist;
}

struct Song* addSong(char new_singer[], char new_title[], char new_album[], double new_time){
    struct Song* new_song = (struct Song*)malloc(sizeof(struct Song));
    strcpy(new_song->title, new_title);
    strcpy(new_song->singer, new_singer);
    strcpy(new_song->album, new_album);
    new_song->time = new_time;
    new_song->next = NULL;
    return new_song;
}