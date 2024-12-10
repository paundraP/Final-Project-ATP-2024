#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "controller.h"
#include "sorting.h"

#define MAX_LEN 128


void printSongInsidePlaylist(Playlist* playlist, int index) {
    Playlist* curr = findPlaylistByIndex(playlist, index);
    if(curr != NULL){
        Song* song = curr->song; 
        int len = strlen(curr->playlistName);
        int width = len > 100 ? len : 100;
        int textLength = strlen(curr->playlistName);
        int leftPadding = (width - textLength) / 2;
        int rightPadding = width - textLength - leftPadding + 7 ;
        if(song != NULL){
            printf("+%.*s+\n", 148, "=====================================================================================================================");
            printf("|\033[1;32m");
            printf("%*sPlaylist: %s%*s\033[0m|\n", leftPadding, "", curr->playlistName, rightPadding, "");
            // printf("");
            printf("+%.*s+\n", 148, "=====================================================================================================================");

            // Header tabel
            printf("| %-25s | %-25s | %-25s | %-8s | %-20s |\n", "Title", "Singer", "Album", "Duration", "Status");
            printf("+---------------------------+---------------------------+---------------------------+----------+----------------------\n");

            // Baris data tabel
            while (song != NULL) {
                printf("| %-25s | %-25s | %-25s | %-8.2f | %-20s |\n", song->title, song->singer, song->album, song->time, song->status);
                song = song->next;
                printf("+%.*s+\n", 148, "=====================================================================================================================");
            }
        }else{
            printf("\n\033[0;37;41mNo songs in this playlist.\033[0m\n");
            return;
        }
    }else{
        printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
        return;
    }
}

void printPlaylist(Playlist* playlist) {
    Playlist* temp = playlist;
    int index = 1;
    if (temp == NULL) {
        printf("\n\033[0;37;41mNo playlists available.\033[0m\n");
        return;
    }
    printf("\nNo.   Playlist Name\n");
    while (temp != NULL) {
        printf("%d.     %s\n", index++, temp->playlistName);
        temp = temp->next;
    }
}

Playlist* playlistMenu(Playlist* playlist) {
    char choice;
    char title[50], singer[50], album[50], remove[50], play[50], url[256], status[20], command[256], path[64];
    float duration;
    int idx, idxtoremove, idxtoplay;

    do {
        printf("\033[1;32m");
        printf("\033[1m\n-- PLAYLIST MANAGER --\033[0m\n");
        printf("\033[0m");
        printf("a. See songs in playlist\n");
        printf("b. Add a song to playlist\n");
        printf("c. Remove a song from playlist\n");
        printf("d. Play song\n");
        printf("e. Back to main menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);

        if (getchar() != '\n') {
            system("clear");
            SpotifyText();
            printPlaylist(playlist);
            printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
            while (getchar() != '\n');
        }else{
            switch (choice) {
                case 'a':                             
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    printf("see song inside playlist!\n");
                    printf("Choose number of playlist: ");
                    if(scanf("%d",&idx)){
                        printSongInsidePlaylist(playlist,idx);
                    }else{
                        char ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {
                            continue;
                        }
                        printf("\n\033[0;37;41mInvalid number.\033[0m\n");    
                    }
                    break;

                case 'b':
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    printf("\nadd song to playlist!\n");
                    printf("Choose number of playlist: ");
                    if(scanf("%d",&idx)){
                        getchar();
                        if(!findPlaylistByIndex(playlist,idx)){
                            printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
                            break;
                        }
                        printf("Enter the title of the song to add: ");
                        fgets(title, sizeof(title), stdin); 
                        title[strcspn(title, "\n")] = '\0';
                        if(title[0] == '\0'){
                            printf("\n\033[0;37;41mThe title is required.\033[0m\n");
                            break;
                        }

                        printf("Enter the singer of the song to add: ");
                        fgets(singer, sizeof(singer), stdin); 
                        singer[strcspn(singer, "\n")] = '\0';
                        if(singer[0] == '\0'){
                            printf("\n\033[0;37;41mThe singer is required.\033[0m\n");
                            break;
                        }
                        printf("Enter the album of the song to add: ");
                        fgets(album, sizeof(album), stdin); 
                        album[strcspn(album, "\n")] = '\0';
                        if(album[0] == '\0'){
                            strcpy(album, "Unknown");
                            album[strcspn(album, "\n")] = '\0';
                        }

                        printf("Enter the youtube url of the song to add \n(If filled, the music will be available to play): ");
                        fgets(url, sizeof(url), stdin); 
                        url[strcspn(url, "\n")] = '\0';
                        if(url[0] == '\0'){
                            strcpy(status, "Unavailable to play");
                            strcpy(url, "-");
                            url[strcspn(url, "\n")] = '\0';
                        }else{                         
                            printf("processing download song from youtube url...\n");   
                            // char* songName = escape(title);
                            snprintf(path, sizeof(path), "songs/%s.mp3",title );
                            char* songName = escape(path);
                            char* link = escape(url);
                            snprintf(command, sizeof(command), "yt-dlp -x --audio-format mp3 --audio-quality 0 -o %s %s --no-warnings", songName,link);
                            system(command);
                            duration = getSongDuration(path);
                            if(duration >0.00){
                                strcpy(status, "Available to play");
                            }else{
                                duration=0.00;
                                strcpy(status, "Unavailable to play");
                            }
                        }
                        status[strcspn(status, "\n")] = '\0';
                        strip(title);
                        strip(singer);
                        strip(album);
                        strip(url);
                        addSongToPlaylist(playlist, idx, title, singer, album, duration, url, status);
                        sortByTitle(playlist);
                    }else{
                        char ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {
                            continue;
                        }
                        printf("\n\033[0;37;41mInvalid number.\033[0m\n");    
                    }            
                    break;
                case 'c':
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    printf("enter the number of the playlist that contains the song you want to delete: ");
                    if(scanf(" %d",&idxtoremove)){
                        getchar();
                        Playlist* curr=findPlaylistByIndex(playlist,idxtoremove);
                        if(curr == NULL){
                            printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
                            break;
                        }
                        if(curr->song!=NULL){
                            printSongInsidePlaylist(playlist,idxtoremove);
                            printf("Enter the name of the song to remove: ");
                            fgets(remove, sizeof(remove), stdin); 
                            remove[strcspn(remove, "\n")] = '\0';
                            strip(remove);
                            system("clear");
                            SpotifyText();
                            deleteSongFromPlaylist(playlist, idxtoremove, remove);
                        }else{
                            printf("\n\033[0;37;41mPlaylist is empty.\033[0m\n"); 
                        }

                    }else{
                        char ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {
                            continue;
                        }
                        printf("\n\033[0;37;41mInvalid number.\033[0m\n");   
                    }
                    
                    break;
                case 'd':
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    printf("enter the number of playlist that contains the song you want to play: ");
                    if(scanf("%d",&idxtoplay)){
                        getchar();
                        Playlist* curr=findPlaylistByIndex(playlist,idxtoplay);
                        if(curr == NULL){
                            printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
                            break;
                        }

                        if(curr->song!=NULL){

                            printSongInsidePlaylist(playlist, idxtoplay);
                            printf("enter the name of the song you want to play: ");
                            fgets(play, sizeof(play), stdin); 
                            play[strcspn(play, "\n")] = '\0';
                            strip(play);
                            playSong(playlist, idxtoplay, play);
                        }else{
                            printf("\n\033[0;37;41mPlaylist is empty.\033[0m\n"); 
                        }
                        break;
                    }else{
                        char ch;
                        while ((ch = getchar()) != '\n' && ch != EOF) {
                            continue;
                        }
                        printf("\n\033[0;37;41mInvalid number.\033[0m\n");   
                    }
                    break;
                case 'e':                           
                    system("clear");
                    SpotifyText();             
                    break;

                default:
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
                    break;
            }
        }
    } while (choice != 'e');
    return playlist;
}

Playlist* dashboardMenu(Playlist* playlist){
    char choice;
    int save, idxtoremove;
    char playlistName[50];

    do {
        printf("\033[1;32m");
        printf("\033[1m\n-- SONG APP MENU --\033[0m\n");
        printf("\033[0m");
        printf("What do you want to do? 😊\n");
        printf("a. Create playlist\n");
        printf("b. See playlist\n");
        printf("c. Delete playlist\n");
        printf("d. Save playlist to file\n");
        printf("e. Insert your playlist from existing file\n");
        printf("f. Exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        
        if (getchar() != '\n') {
            system("clear");
            SpotifyText();
            printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
            while (getchar() != '\n');
        }else{
            switch (choice) {
                case 'a':
                    system("clear");
                    SpotifyText();
                    printf("Enter playlist name: ");
                    fgets(playlistName, sizeof(playlistName), stdin); 
                    playlistName[strcspn(playlistName, "\n")] = '\0';
                    if(playlistName[0] == '\0'){
                            printf("\n\033[0;37;41mPlaylist name is required.\033[0m\n");
                            break;
                    }
                    strip(playlistName);
                    playlist = addNewPlaylist(playlist, playlistName);                
                    break;

                case 'b':           
                    if (playlist == NULL) {
                        system("clear");
                        SpotifyText();
                        printf("\n\033[0;37;41mThe playlists list is empty.\033[0m\n");
                    } else {                           
                        system("clear");
                        SpotifyText();                
                        printPlaylist(playlist);
                        playlist = playlistMenu(playlist);
                    }
                
                    break;

                case 'c':                  
                    system("clear");
                    SpotifyText();
                    printPlaylist(playlist);
                    if(playlist!=NULL){
                        printf("enter the number of the playlist you want to delete: ");                        
                        if(scanf(" %d",&idxtoremove)){
                            getchar();
                            if(findPlaylistByIndex(playlist,idxtoremove)){
                                playlist = deletePlaylist(playlist, idxtoremove);                                
                            }else{
                                printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
                                break;
                            }

                        }else{
                            char ch;
                            while ((ch = getchar()) != '\n' && ch != EOF) {
                                continue;
                            }
                            printf("\n\033[0;37;41mInvalid number.\033[0m\n");   
                        }
                        
                    }
                    break;
                case 'd':                       
                    system("clear");
                    SpotifyText();
                    if(playlist == NULL){
                        printf("\033[0;37;41myou're playlist is empty yet\033[0m\n\n");
                    }else{
                        printPlaylist(playlist);
                        printf("Which playlist you want to save? (choose number of playlist): ");
                        if(scanf(" %d", &save)){
                            getchar();
                            if(findPlaylistByIndex(playlist,save)){
                                savePlaylist(playlist, save);
                            }else{
                                printf("\n\033[0;37;41mInvalid number, playlist not exists.\033[0m\n");
                                break;
                            }

                        }else{
                            char ch;
                            while ((ch = getchar()) != '\n' && ch != EOF) {
                                continue;
                            }
                            printf("\n\033[0;37;41mInvalid number.\033[0m\n");   
                        }                                                                                 
                    }
                    break;                
                case 'e':
                    system("clear");
                    SpotifyText();
                    int check=listFileInPlaylistFolder();
                    if(check){
                        printf("Enter playlist name: ");
                        fgets(playlistName, sizeof(playlistName), stdin); 
                        playlistName[strcspn(playlistName, "\n")] = '\0';
                        playlist = readPlaylist(playlist,playlistName);
                    }
                    break;

                case 'f':
                    printf("Exiting...\n");
                    return playlist;

                default:
                    system("clear");
                    SpotifyText();
                    printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
            }
        }
    } while (choice != 'f');
    return playlist;
}

int main(){
    Playlist* playlists = NULL;
    SpotifyText();
    playlists = dashboardMenu(playlists);
    free(playlists);
    
    return 0;
}
