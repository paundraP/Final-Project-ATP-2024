#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include "dto.h"

int isSongInPlaylist(struct Song* songList, char title[]) {
    struct Song* temp = songList;
    while (temp != NULL) {
        if (strcmp(temp->title, title) == 0) {
            return 1; 
        }
        temp = temp->next;
    }
    return 0; 
}

int playlistExists(struct Playlist* playlist, char playlistname[]) {
    struct Playlist* temp = playlist;
    while (temp != NULL) {
        if (strcmp(temp->playlistName, playlistname) == 0) {
            return 1; 
        }
        temp = temp->next;
    }
    return 0;
}

Playlist* findPlaylistByIndex(Playlist* playlist, int index){
    Playlist* curr = playlist;
    int count = 0;
    while(curr != NULL && count < index - 1) {
        curr = curr->next;
        count++;
    }
    if(curr == NULL){
        return NULL;
    }
    return curr;
}

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


void addSongToPlaylist(Playlist* playlist, int index, char title[], char singer[], char album[], double time) {
    Playlist* targetPlaylist = findPlaylistByIndex(playlist, index);
    if (targetPlaylist == NULL) {
        printf("\nPlaylist not found.\n");
        return;
    }else{
        if (isSongInPlaylist(targetPlaylist->song, title)) {
            printf("\nSong '%s' already exists in the playlist '%s'.\n", title, targetPlaylist->playlistName);
            return;
        }else{
            Song* newSong = createSong(singer, title, album, time);
            if (!newSong) {
                return;
            }
            if (!targetPlaylist->song) {
                targetPlaylist->song = newSong;
            } else {
                Song* temp = targetPlaylist->song;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newSong; 
            }
            printf("\nSong '%s' added to playlist '%s'.\n", title, targetPlaylist->playlistName);
            return;
        }
    }
}


Playlist* addNewPlaylist(struct Playlist* playlist, char playlistname[]){
    if (playlistExists(playlist, playlistname)) {
        printf("\033[2J\033[H");                    
        printf("\nPlaylist with the name '%s' already exists.\n\n", playlistname);
        return playlist;
    }else {
        printf("\033[2J\033[H");                    
        printf("\nplaylist %s created\n\n", playlistname);
    }

    struct Playlist* new_playlist = createPlaylist(playlistname);
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

Playlist* deleteSongFromPlaylist(Playlist* playlist, int index, char songName[]) {
    Playlist* temp = findPlaylistByIndex(playlist, index);
    if (temp == NULL) {
        printf("Index out of bound!\n");
        return playlist;
    }

    Song* current = temp->song;
    Song* previous = NULL;

    while (current != NULL) {
        if (strcmp(current->title, songName) == 0) {
            if (previous == NULL) {
                temp->song = current->next;
            } else {
                previous->next = current->next;
            }
            free(current);
            printf("Song deleted successfully.\n");
            return playlist;
        }
        previous = current;
        current = current->next;
    }

    printf("The song you want to delete is not known, or you're mistyping.\n");
    return playlist;
}

Playlist* deletePlaylist(Playlist* playlist, int index) {
    if (playlist == NULL) {
        printf("There is no playlist yet\n");
        return playlist;
    }

    Playlist* temp = playlist;

    if (index == 1) {
        playlist = temp->next; 
        free(temp);            
        printf("Successfully deleted the playlist\n");
        return playlist;
    }

    Playlist* prev = NULL;
    for (int i = 1; temp != NULL && i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("Error: Invalid index\n");
        return playlist;
    }
    prev->next = temp->next; 
    free(temp);             
    printf("Successfully deleted the playlist\n");

    return playlist;
}

void savePlaylist(Playlist* playlist, int index){
    Playlist* curr = findPlaylistByIndex(playlist, index);
    if(curr == NULL) {
        printf("The playlist you want to save is unknow, or youre mistyping\n");
        return;
    }
    if (curr->song == NULL){
        printf("The playlist you want to save is empty yet\n");
        return;
    }
    FILE *fptr;
    char filename[113];
    snprintf(filename, sizeof(filename), "playlist/%s.txt", curr->playlistName);

    fptr = fopen(filename, "w");
    Song* temp = curr->song;
    if(fptr == NULL){
        printf("Error saving file\n\n");
        return;
    }
    else{
        while(temp != NULL){
            fprintf(fptr, "Title: %s\nSinger: %s\nAlbum: %s\nTime: %.2f\n\n", temp->title, temp->singer, temp->album, temp->time);
            temp = temp->next;
        }
    }
    fclose(fptr);
}

void listFileInPlaylistFolder(){
    DIR *dir;
    struct dirent *entry;
    dir = opendir("playlist");
    if (dir == NULL) {
        perror("opendir failed");
        return;

    }
    int idx = 1;
    printf("Playlist files that you can open : \n");
    while ((entry = readdir(dir)) != NULL) {
        if(strlen(entry->d_name) > 2){
            printf("%d %s\n", idx, entry->d_name); 
            idx++;
        }
    }
    closedir(dir);
}

void readPlaylist() {
    FILE *fptr;
    char readData[1024];
    Song* song = NULL; 

    fptr = fopen("playlist/pujo.txt", "r");
    if (fptr == NULL) {
        printf("Error: Unable to open file\n");
        return;
    }

    while (fgets(readData, 1024, fptr) != NULL) {
        if (strncmp(readData, "Title: ", 7) == 0) {
            sscanf(readData, "Title: %99[^\n]", song->title);
        } else if (strncmp(readData, "Singer: ", 8) == 0) {
            sscanf(readData, "Singer: %99[^\n]", song->singer);
        } else if (strncmp(readData, "Album: ", 7) == 0) {
            sscanf(readData, "Album: %99[^\n]", song->album);
        } else if (strncmp(readData, "Time: ", 6) == 0) {
            sscanf(readData, "Time: %lf", &song->time);
        }
    }
    fclose(fptr);

    printf("Data successfully read from playlist:\n");
    printf("%s\n", song->title);
    printf("%s\n", song->singer);
    printf("%s\n", song->album);
    printf("%.2f\n", song->time);
}