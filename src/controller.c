#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include <dirent.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>
#include <math.h>
#include <termios.h>
#include <fcntl.h> 
#include <fcntl.h>
#include <mpg123.h>
#include "dto.h"
#include "mpg123.h"

void SpotifyText(){
    printf("\033[1;32m"); // Set text color to bright green
    printf("\n          ██████████                                                                            ████████████████████████████   ████████████   ");
    printf("\n        ██████████████████                                                                      ████████████████████████████   ████████████   ");
    printf("\n     ████████████████████████                                                                   ████████████████████████████   ████████████   ");
    printf("\n    ██████████████████████████                                                                  ████████████████████████████   ████████████   ");
    printf("\n  ██████████████████████████████                                                                                ████████████                  ");
    printf("\n █████                  █████████        █████████                            ████  ███         ████████████    ████████████                  ");
    printf("\n █████      █████           █████       ███    ███                                  ███         ████████████    ████████████                  ");
    printf("\n█████████████████████████    █████      ███         ███ ██████     ████████    ███ ████████     ████████████    ████████████                  ");
    printf("\n███████               ████████████      ████████    ████    ████  ████   ████  ███  ████        ████████████    ████████████                  ");
    printf("\n███████   ████████        ████████         ███████  ███      ███ ███      ████ ███  ███         ████████████    ████████████                  ");
    printf("\n████████████████████████   ███████              ███ ███      ███ ███      ████ ███  ███         ████████████    ████████████                  ");
    printf("\n ██████               ███████████       ███     ███ ████    ████  ███    ████  ███  ████        ████████████    ████████████                  ");
    printf("\n ████████████████████    ████████       ██████████  ███████████    █████████   ███   █████      ████████████    ████████████                  ");
    printf("\n  ██████████████████████████████                    ███                                         ████████████    ████████████                  ");
    printf("\n    ██████████████████████████                      ███                                         ████████████    ████████████                  ");
    printf("\n     ████████████████████████                                                                   ████████████    ████████████                  ");
    printf("\n        ██████████████████                            SUPPORT FOR LINUX/UNIX                    ████████████    ████████████                  ");
    printf("\n           ████████████                                                                         ████████████    ████████████                  ");
    printf("\n"); 
    // printf("\n");
    printf("\n\n\n\n");
    printf("\033[0m"); // Reset text color to default

}

char* escape(char* str) {
    char *escStr;
    int i,
        count = strlen(str),
        ptr_size = count + 3; // Initial size with extra room for double quotes

    escStr = (char *) calloc(ptr_size, sizeof(char));
    if (escStr == NULL) {
        return NULL;
    }
    sprintf(escStr, "\""); // Start with double quote

    for(i = 0; i < count; i++) {
        if (str[i] == '"') {
            ptr_size += 2; // Increase size for escape sequence (\")
            escStr = (char *) realloc(escStr, ptr_size * sizeof(char));
            if (escStr == NULL) {
                return NULL;
            }
            sprintf(escStr, "%s\\\"", escStr); // Escape double quote
        } else {
            ptr_size += 1; // Increase size for one character
            escStr = (char *) realloc(escStr, ptr_size * sizeof(char));
            if (escStr == NULL) {
                return NULL;
            }
            sprintf(escStr, "%s%c", escStr, str[i]); // Add regular character
        }
    }

    sprintf(escStr, "%s\"", escStr); // End with double quote
    return escStr;
}

bool isEmptyOrSpaces(const char *str) {
    while (*str) {
        if (!isspace((unsigned char)*str)) return false; // If a non-space character is found, return false
        str++;
    }
    return true; // If no non-space characters are found, return true
}

void enableNonBlockingInput() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Get current flags
    fcntl(STDIN_FILENO, F_SETFL, flags | O_NONBLOCK); // Set non-blocking
}

void disableNonBlockingInput() {
    int flags = fcntl(STDIN_FILENO, F_GETFL, 0); // Get current flags
    fcntl(STDIN_FILENO, F_SETFL, flags & ~O_NONBLOCK); // Unset non-blocking
}

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

Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time,char url[], char status[]){
    Song* new_song = (Song*)malloc(sizeof(Song));
    strcpy(new_song->title, new_title);
    strcpy(new_song->singer, new_singer);
    strcpy(new_song->album, new_album);
    strcpy(new_song->url, url);
    strcpy(new_song->status, status);
    new_song->time = new_time;
    new_song->next = NULL;
    return new_song;
}


void addSongToPlaylist(Playlist* playlist, int index, char title[], char singer[], char album[], double time, char url[], char status[]) {
    Playlist* targetPlaylist = findPlaylistByIndex(playlist, index);
    if (targetPlaylist == NULL) {
        printf("\n\033[0;37;41mPlaylist not found.\033[0m\n");
        return;
    }else{
        if (isSongInPlaylist(targetPlaylist->song, title)) {
            printf("\n\033[0;37;41mSong '%s' already exists in the playlist '%s'.\033[0m\n", title, targetPlaylist->playlistName);
            return;
        }else{
            Song* newSong = createSong(singer, title, album, time, url, status);
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


Playlist* addNewPlaylist(Playlist* playlist, char playlistname[]){
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
        printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
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
        printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
        return;
    }
    
    if (curr->song == NULL){
        printf("\n\033[0;37;41mThe playlist you want to save is empty yet\033[0m\n");
        return;
    }
    FILE *fptr;
    char filename[113];
    snprintf(filename, sizeof(filename), "playlists/%s.txt", curr->playlistName);

    fptr = fopen(filename, "w");
    fprintf(fptr, "title, singer, album, duration, source, status\n");
    Song* temp = curr->song;
    if(fptr == NULL){
        printf("\n\033[0;37;41mError saving file\033[0m\n\n");
        return;
    }
    else{
        while(temp != NULL){
            fprintf(fptr, "%s, %s, %s, %.2f, %s, %s\n", temp->title, temp->singer, temp->album, temp->time, temp->url, temp->status);
            temp = temp->next;
        }
    }
    fclose(fptr);
    printf("\n\033[0;42mThe playlist %s save to playlist/%s.txt\033[0m\n",curr->playlistName,curr->playlistName);

}

int listFileInPlaylistFolder(){
    DIR *dir;
    struct dirent *entry;
    dir = opendir("playlists");
    int filesFound = 0;

    if (dir == NULL) {
        perror("\n\033[0;37;41mopendir failed\033[0m");
        return 0;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        if (strlen(entry->d_name) > 2) {  
            char *dot = strrchr(entry->d_name, '.'); 
            if (dot && strcmp(dot, ".txt") == 0) {  
                if (!filesFound) {
                    printf("\nPlaylist files that you can open : \n");  
                    filesFound = 1;  
                }
                size_t nameLength = dot - entry->d_name;
                char nameWithoutExtension[256];        
                strncpy(nameWithoutExtension, entry->d_name, nameLength);
                nameWithoutExtension[nameLength] = '\0'; 
                printf("- %s\n", nameWithoutExtension);
            }
        }
    }

    if (!filesFound) {
        printf("\n\033[0;37;41mError: No playlist file found in the directory.\n\033[0m");
        return 0;
    }

    closedir(dir);
    return 1;
    
}

Playlist* readPlaylist(Playlist* playlist, char playlistName[]) {
    char title[50], singer[50], album[50], url[256], status[20], path[64], command[256];

    float duration;
    FILE *fptr;
    char readData[1024];
    
    char filePath[50];


    sprintf(filePath, "playlists/%s.txt",  playlistName);
    fptr = fopen(filePath, "r");

    if (fptr == NULL) {
        printf("\n\033[0;37;41mError: Unable to open file\033[0m\n");
        return playlist;
    }
    
    // playlist = addNewPlaylist(playlist,playlistName);
    // Playlist* targetPlaylist = findPlaylistByName(playlist, playlistName);
     if (playlistExists(playlist, playlistName)) {                   
        printf("\n\033[0;37;41mPlaylist with the name '%s' already exists.\033[0m\n\n", playlistName);
        return playlist;
    }          
    struct Playlist* targetPlaylist = createPlaylist(playlistName);                
    printf("\n\033[0;42mplaylist %s created\033[0m\n\n", playlistName);


    if (isSongInPlaylist(targetPlaylist->song, title)) {
        printf("\n\033[0;37;41mSong '%s' already exists in the playlist '%s'.\033[0m\n", title, targetPlaylist->playlistName);
        return playlist;
    }
    int idx=1;

    if (fgets(readData, sizeof(readData), fptr)) {
        ;
    }

    while (fgets(readData, sizeof(readData), fptr)) {
        readData[strcspn(readData, "\n")] = '\0';
        if (sscanf(readData, "%[^,],%[^,],%[^,],%f,%[^,],%[^,]", title, singer, album, &duration, url, status) == 6) {    
            if (isEmptyOrSpaces(title)) {
                system("clear");
                SpotifyText();
                printf("\033[0;37;41mError: Title is empty on line %d. Aborting process (playlist deleted).\033[0m\n", idx);
                fclose(fptr);
                // playlist = findPlaylistByName(playlist, playlistName);
                // free(playlist);
                return playlist; // Return original playlist, no changes made
            }
            if (isEmptyOrSpaces(singer)) strcpy(singer, "unknown");
            if (isEmptyOrSpaces(album)) strcpy(album, "unknown");
            if (isEmptyOrSpaces(url)) strcpy(url, "-");
            if (isEmptyOrSpaces(status)) strcpy(status, "Unavailable to play");

            strip(title);
            strip(singer);
            strip(album);            
            strip(url);
            strip(status);
            // addSongToPlaylist(playlist, idx, title, singer, album, duration, url, status);
            Song* newSong = createSong(singer, title, album, duration, url, status);
            if (!targetPlaylist->song) {
                targetPlaylist->song = newSong;
            } else {
                Song* temp = targetPlaylist->song;
                while (temp->next) {
                    temp = temp->next;
                }
                temp->next = newSong; 
            }

            if (strcmp(status, "Available to play") == 0 && strcmp(url, "-") != 0) {
                printf("\nTry download music from %s.......\n",url);   
                snprintf(path, sizeof(path), "songs/%s.mp3",title );
                char* songName = escape(path);
                char* link = escape(url);
                snprintf(command, sizeof(command), "yt-dlp -q -x --audio-format mp3 --audio-quality 0 -o %s %s --no-warnings", songName,link);
                system(command);
                printf("\n\033[0;42mSong '%s' added to playlist '%s' and available to play.\033[0m\n", title, targetPlaylist->playlistName);
            }else{
                printf("\n\033[0;42mSong '%s' added to playlist '%s' but unavailable to play.\033[0m\n", title, targetPlaylist->playlistName);
            }
        }else{
            printf("\033[0;37;41mskipping data in line %d error to parse\033[0m",idx);
        }
    }
    
    fclose(fptr);
    idx++;

    if(playlist == NULL){
        return targetPlaylist;
    }
    Playlist* temp = playlist;
    while(temp->next != NULL) {
        temp = temp->next;
    }
    temp->next = targetPlaylist;


    return playlist;
}

int playable(char songName[]){
    DIR *dir;
    struct dirent *entry;
    dir = opendir("songs");
    if (dir == NULL) {
        perror("\n\033[0;37;41mopendir failed\033[0m");
        return 0;
    }
    
    while ((entry = readdir(dir)) != NULL) {
        char *filename = entry->d_name;
        char *dot = strrchr(filename, '.');
        if(dot && strcmp(dot, ".mp3") == 0) {
            char nameWithoutExtension[256];
            strncpy(nameWithoutExtension, filename, dot - filename);
            nameWithoutExtension[dot - filename] = '\0';

            if(strcmp(nameWithoutExtension, songName) == 0){
                closedir(dir);
                return 1;
            }
        }
    }
    closedir(dir);
    return 0;
}

void playProgressBar(int totalSeconds) {
    const int progressBarWidth = 100;
    
    printf("\n\n\t\t\tSong Progress:\n\n");
    fflush(stdout);

    enableNonBlockingInput();

    for (int elapsed = 0; elapsed <= totalSeconds; elapsed++) {
        int c = getchar();
        if (c != EOF) { 
            if (c == '\n') {
                disableNonBlockingInput();
                printf("\n\t\t\t\033[0;37;41mProgress interrupted.\033[0m\n");
                return;
            }
        }
        int progress = (progressBarWidth * elapsed) / totalSeconds; 
        printf("\r\t\t\t[");
        for (int i = 0; i < progress; i++) 
            printf("\033[0;42m#\033[0m");
        for (int i = progress; i < progressBarWidth; i++) 
            printf(" ");
        printf("] %3d%%", (progress * 100) / progressBarWidth);
        
        fflush(stdout);
        sleep(1);
    }
    
    disableNonBlockingInput();
}

void playSong(Playlist* playlist, int index, char songName[]) {
    Playlist* temp = findPlaylistByIndex(playlist, index);
    if (temp == NULL) {
        printf("\033[0;37;41mIndex out of bounds!\033[0m\n");
        return;
    }

    Song* curr = temp->song;
    while (curr != NULL) {
        if (strcmp(curr->title, songName) == 0 && playable(songName)) {
            int minutes = (int)curr->time / 60;
            int seconds = (int)curr->time % 60;

            printf("+=====================================================================================================================+\n");
            printf("|                                                   Now playing:                                                      |\n");
            printf("+=====================================================================================================================+\n");
            printf("| Source: %-108s|\n", curr->url);
            printf("| Title: %-109s|\n", curr->title);
            printf("| Singer: %-108s|\n", curr->singer);
            printf("| Album: %-109s|\n", curr->album);
            printf("| Duration: %2d min %2d sec %-92s|\n", minutes, seconds," ");
            printf("+=====================================================================================================================+\n");

            char command[256];
            // char* songNamewithEscape = escape(songName);
            int duration = (int)curr->time + 1;

            snprintf(command, sizeof(command), "mpg123 -q 'songs/%s.mp3'", songName);

            pid_t pid = fork();
            if (pid == 0) {
                system(command);
                _exit(0); 
            } else if (pid > 0) {
                printf("\nPress 'q' + 'enter' to stop playback.\n");
                playProgressBar(duration);
                wait(NULL);
            } else {
                perror("fork failed");
                return;
            }
            // if(getchar() == "q"){
            //     printf("\n\033[0;42mSong stopped\n\033[0m");
            //     return;
            // }
            printf("\n\033[0;42mSong Completed\033[0m\n");
            // }
            return;

        }
        curr = curr->next;
    }

    if (curr == NULL) {
        printf("\n\033[0;37;41mSong not found or not playable!\033[0m\n");
    }
    return;
}


float getSongDuration(char filename[]){
    mpg123_init();
    mpg123_handle *mh = mpg123_new(NULL, NULL);
    
    if (mpg123_open(mh, filename) != MPG123_OK) {
        printf("Gagal membuka file MP3\n");
        return -1;
    }

    long rate;
    int channels, encoding;
    mpg123_getformat(mh, &rate, &channels, &encoding);
    
    off_t samples = mpg123_length(mh);
    float duration = (float)samples / rate;
    duration = ((int)(duration * 100 + 0.5)) / 100.0f;


    mpg123_close(mh);
    mpg123_delete(mh);
    mpg123_exit();

    return duration;
}

