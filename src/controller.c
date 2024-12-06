#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include "dto.h"

char* strip(char* str) {
    char* start = str;
    while (isspace((unsigned char)*start)) {
        start++;
    }

    if (*start == '\0') {
        str[0] = '\0';
        return str;
    }

    char* end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) {
        end--;
    }

    *(end + 1) = '\0';

    if (start != str) {
        memmove(str, start, end - start + 2);
    }
    return str;
}

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

Playlist* findPlaylistByName(Playlist* head, char playlistName[]) {
    Playlist* current = head;
    while (current != NULL) {
        if (strcmp(current->playlistName, playlistName) == 0) {
            return current;
        }
        current = current->next;
    }
    return NULL;
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
        printf("\n\033[0;37;41mPlaylist not found.\033[0m\n");
        return;
    }else{
        if (isSongInPlaylist(targetPlaylist->song, title)) {
            printf("\n\033[0;37;41mSong '%s' already exists in the playlist '%s'.\033[0m\n", title, targetPlaylist->playlistName);
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
            printf("\n\033[0;42mSong '%s' added to playlist '%s'.\033[0m\n", title, targetPlaylist->playlistName);
            return;
        }
    }
}


Playlist* addNewPlaylist(struct Playlist* playlist, char playlistname[]){
    if (playlistExists(playlist, playlistname)) {                   
        printf("\n\033[0;37;41mPlaylist with the name '%s' already exists.\033[0m\n\n", playlistname);
        return playlist;
    }else {                            
        printf("\n\033[0;42mplaylist %s created\033[0m\n\n", playlistname);
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
        printf("\033[0;37;41mIndex out of bound!\033[0m\n");
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
            printf("\n\033[0;42mSong deleted successfully.\033[0m\n");
            return playlist;
        }
        previous = current;
        current = current->next;
    }

    printf("\n\033[0;37;41mThe song you want to delete is not known, or you're mistyping.\033[0m\n");
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
        printf("\n\033[0;37;41mThere is no playlist yet\033[0m\n");
        return playlist;
    }

    Playlist* temp = playlist;

    if (index == 1) {
        playlist = deleteHeadPlaylist(playlist);
        printf("\n\033[0;42mSuccessfully deleted the playlist\033[0m\n");
        return playlist;
    }

    Playlist* prev = NULL;
    for (int i = 1; temp != NULL && i < index; i++) {
        prev = temp;
        temp = temp->next;
    }

    if (temp == NULL) {
        printf("\n\033[0;37;41mError: Invalid index\033[0m\n");
        return playlist;
    }
    prev->next = temp->next; 
    free(temp);             
    printf("\n\033[0;42mSuccessfully deleted the playlist\033[0m\n");

    return playlist;
}

void savePlaylist(Playlist* playlist, int index){
    Playlist* curr = findPlaylistByIndex(playlist, index);
    if(curr == NULL) {
        printf("\n\033[0;37;41mThe playlist you want to save is unknown, or youre mistyping\033[0m\n");
        return;
    }
    
    if (curr->song == NULL){
        printf("\n\033[0;37;41mThe playlist you want to save is empty yet\033[0m\n");
        return;
    }
    FILE *fptr;
    char filename[113];
    snprintf(filename, sizeof(filename), "playlist/%s.txt", curr->playlistName);

    fptr = fopen(filename, "w");
    fprintf(fptr, "title, singer, album, duration\n");
    Song* temp = curr->song;
    if(fptr == NULL){
        printf("\n\033[0;37;41mError saving file\033[0m\n\n");
        return;
    }
    else{
        while(temp != NULL){
            fprintf(fptr, "%s, %s, %s, %.2f\n", temp->title, temp->singer, temp->album, temp->time);
            temp = temp->next;
        }
    }
    fclose(fptr);
    printf("\n\033[0;42mThe playlist %s save to playlist/%s.txt\033[0m\n",curr->playlistName,curr->playlistName);

}

void listFileInPlaylistFolder(){
    DIR *dir;
    struct dirent *entry;
    dir = opendir("playlist");
    if (dir == NULL) {
        perror("\n\033[0;37;41mopendir failed\033[0m");
        return;

    }
    
    printf("\nPlaylist files that you can open : \n");
    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2) { 
            char *dot = strrchr(entry->d_name, '.'); 
            if (dot && strcmp(dot, ".txt") == 0) {   
                size_t nameLength = dot - entry->d_name; 
                char nameWithoutExtension[256];        
                strncpy(nameWithoutExtension, entry->d_name, nameLength);
                nameWithoutExtension[nameLength] = '\0'; 
                printf("- %s\n", nameWithoutExtension);
                
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
        printf("\n\033[0;37;41mError: Unable to open file\033[0m\n");
        return 0;
    }
    
    playlist = addNewPlaylist(playlist,playlistName);
    playlist = findPlaylistByName(playlist, playlistName);
    int idx=1;

    if (fgets(readData, sizeof(readData), fptr)) {
        ;
    }

    while (fgets(readData, sizeof(readData), fptr)) {
        readData[strcspn(readData, "\n")] = '\0';

        if (sscanf(readData, "%[^,],%[^,],%[^,],%f", title, singer, album, &duration) == 4) {
            addSongToPlaylist(playlist, idx, title, singer, album, duration);
        }else{
            printf("\033[0;37;41mskipping data in line %d error to parse\033[0m",idx);
        }
    }
    
    fclose(fptr);
    idx++;

    return playlist;
}