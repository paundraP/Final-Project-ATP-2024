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
        printf("\nPlaylist with the name '%s' already exists.\n\n", playlistname);
        return playlist;
    }else {                            
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

Playlist* deleteHeadPlaylist(Playlist* playlist) {
    if (playlist == NULL) {
        return NULL;
    }
    Playlist* newHead = playlist->next;
    free(playlist);
    return newHead;
}

Playlist* deletePlaylist(Playlist* playlist, int index) {
    if (playlist == NULL) {
        printf("There is no playlist yet\n");
        return playlist;
    }

    Playlist* temp = playlist;

    if (index == 1) {
        playlist = deleteHeadPlaylist(playlist);
        printf("Head deleted\n");
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
    fprintf(fptr, "title, singer, album, duration\n");
    Song* temp = curr->song;
    if(fptr == NULL){
        printf("Error saving file\n\n");
        return;
    }
    else{
        while(temp != NULL){
            fprintf(fptr, "%s, %s, %s, %.2f\n", temp->title, temp->singer, temp->album, temp->time);
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
        perror("\nopendir failed");
        return;

    }
    int idx = 1;
    printf("\nPlaylist files that you can open : \n");
    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2) { 
            char *dot = strrchr(entry->d_name, '.'); 
            if (dot && strcmp(dot, ".txt") == 0) {   
                size_t nameLength = dot - entry->d_name; 
                char nameWithoutExtension[256];        
                strncpy(nameWithoutExtension, entry->d_name, nameLength);
                nameWithoutExtension[nameLength] = '\0'; 
                printf("%d. %s\n", idx, nameWithoutExtension);
                idx++;
            }
        }
    }
    closedir(dir);
}

Playlist* readPlaylist(struct Playlist* playlist, char playlistName[]) {
    char title[50], singer[50], album[50];
    float duration;
    FILE *fptr;
    char readData[1024];
    
    char filePath[50];


    sprintf(filePath, "playlist/%s.txt",  playlistName);
    fptr = fopen(filePath, "r");

    if (fptr == NULL) {
        printf("\nError: Unable to open file\n");
        return 0;
    }
    
    playlist = addNewPlaylist(playlist,playlistName);
    int idx=1;

    if (fgets(readData, sizeof(readData), fptr)) {
        ;
    }

    while (fgets(readData, sizeof(readData), fptr)) {
        readData[strcspn(readData, "\n")] = '\0';

        if (sscanf(readData, "%[^,],%[^,],%[^,],%f", title, singer, album, &duration) == 4) {
            addSongToPlaylist(playlist, idx, title, singer, album, duration);
        }else{
            printf("skipping data in line %d error to parse",idx);
        }
    }
    
    fclose(fptr);
    idx++;

    return playlist;
}