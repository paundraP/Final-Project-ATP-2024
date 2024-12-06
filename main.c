#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "controller.h"
#include "sorting.h"


#define MAX_LEN 128
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
    printf("\n        ██████████████████                                                                      ████████████    ████████████                  ");
    printf("\n           ████████████                                                                         ████████████    ████████████                  ");
    printf("\n\n\n\n");
    printf("\033[0m"); // Reset text color to default

}

void printSongInsidePlaylist(Playlist* playlist, int index) {
    Playlist* curr = findPlaylistByIndex(playlist, index);
    if(curr != NULL){
        Song* song = curr->song; 
        int len = strlen(curr->playlistName);
        int width = len > 159 ? len : 159;
        int textLength = strlen(curr->playlistName);
        int leftPadding = (width - textLength) / 2; // Calculate left padding
        int rightPadding = width - textLength - leftPadding; // Calculate right padding
        if(song != NULL){
            printf("+%.*s+\n", 200, "=========================================================================================================================================================================");
            printf("|\033[1;32m");
            printf("%*sPlaylist: %s%*s\033[0m|\n", leftPadding, "", curr->playlistName, rightPadding, "");
            // printf("");
            printf("+%.*s+\n", 200, "=========================================================================================================================================================================");

            // Header tabel
            printf("| %-50s | %-50s | %-50s | %-8s |\n", "Judul", "Penyanyi", "Album", "Waktu");
            printf("+----------------------------------------------------+----------------------------------------------------+----------------------------------------------------+----------+\n");

            // Baris data tabel
            while (song != NULL) {
                printf("| %-50s | %-50s | %-50s | %-8.2f |\n", song->title, song->singer, song->album, song->time);
                song = song->next;
                printf("+%.*s+\n", 200, "=========================================================================================================================================================================");
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
    char choice, extra;
    char title[50], singer[50], album[50], remove[50];
    float duration;
    int idx, idxtoremove;

    do {
        // SpotifyText();
        printf("\033[1;32m");
        printf("\033[1m\n-- PLAYLIST MANAGER --\033[0m\n");
        printf("\033[0m");
        printf("a. See songs in playlist\n");
        printf("b. Add a song to playlist\n");
        printf("c. Remove a song from playlist\n");
        printf("d. Back to main menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();

        switch (choice) {
            case 'a':         
                // printf("\033[2J\033[H");
                // system("clear");
                system("clear");
                SpotifyText();
                printPlaylist(playlist);
                printf("see song inside playlist!\n");
                printf("Choose number of playlist: ");
                scanf("%d",&idx);
                printSongInsidePlaylist(playlist,idx);
                break;

            case 'b':
                // printf("\033[2J\033[H");
                system("clear");
                SpotifyText();
                printPlaylist(playlist);
                printf("\nadd song to playlist!\n");
                printf("Choose number of playlist: ");
                scanf("%d",&idx);
                getchar();

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
                    printf("\n\033[0;37;41mThe album is required.\033[0m\n");
                    break;
                }

                printf("Enter the duration of the song to add with format (0.00): ");
                if (scanf("%f%c", &duration, &extra) == 2 && extra == '\n');
                else {
                    printf("\n\033[0;37;41mInvalid input. must be a float.\033[0m\n");
                    while ((extra = getchar()) != '\n' && extra != EOF);
                    break;
                }
                strip(title);
                strip(singer);
                strip(album);
                addSongToPlaylist(playlist, idx, title, singer, album, duration);
                sortByTitle(playlist);
                break;
            
            
            case 'c':
                // printf("\033[2J\033[H");
                system("clear");
                SpotifyText();
                printPlaylist(playlist);
                printf("enter the number of the playlist that contains the song you want to delete: ");
                scanf(" %d",&idxtoremove);
                getchar();
                if(findPlaylistByIndex(playlist,idxtoremove)){
                    printSongInsidePlaylist(playlist,idxtoremove);
                    printf("Enter the name of the song to remove: ");
                    fgets(remove, sizeof(remove), stdin); 
                    remove[strcspn(remove, "\n")] = '\0';
                    strip(remove);
                    deleteSongFromPlaylist(playlist, idxtoremove, remove);
                }else{
                    printf("\n\033[0;37;41mPlaylist not found.\033[0m\n");
                }
                break;

            case 'd':
                // printf("\033[2J\033[H");       
                system("clear");
                SpotifyText();             
                break;

            default:
                printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
        }
    } while (choice != 'd');
    return playlist;
}

Playlist* dashboardMenu(Playlist* playlist){
    char choice;
    int save, idxtoremove;
    char playlistName[50];

    do {
        // SpotifyText();
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
        getchar();
        switch (choice) {
            case 'a':
                printf("Enter playlist name: ");
                fgets(playlistName, sizeof(playlistName), stdin); 
                playlistName[strcspn(playlistName, "\n")] = '\0';
                // printf("\033[2J\033[H");
                system("clear");
                SpotifyText();
                strip(playlistName);
		        playlist = addNewPlaylist(playlist, playlistName);  

                break;


            case 'b':
                if (playlist == NULL) {
                    printf("\n\033[0;37;41mThe playlists list is empty.\033[0m\n");
                } else {
                    // printf("\033[2J\033[H");    
                    system("clear");
                    SpotifyText();                
                    printPlaylist(playlist);
                    playlist = playlistMenu(playlist);
                }
                break;

            case 'c':
                // printf("\033[2J\033[H");
                system("clear");
                SpotifyText();
                printPlaylist(playlist);
                if(playlist!=NULL){
                    printf("enter the number of the playlist you want to delete: ");
                    scanf(" %d", &idxtoremove);
                    playlist = deletePlaylist(playlist, idxtoremove);
                }
                break;

            case 'd':
                // printf("\033[2J\033[H");   
                system("clear");
                SpotifyText();
                if(playlist == NULL){
                    // printf("\033[2J\033[H");
                    system("clear");
                    SpotifyText();
                    printf("\033[0;37;41myoure playlist is empty yet\033[0m");
                }else{
                    printPlaylist(playlist);
                    printf("Which playlist you want to save? (choose number of playlist): ");
                    scanf(" %d", &save);
                    // printf("\033[2J\033[H");
                    system("clear");
                    SpotifyText();
                    savePlaylist(playlist, save);
                }
                break;                
            case 'e':
                listFileInPlaylistFolder();
                printf("Enter playlist name: ");
                fgets(playlistName, sizeof(playlistName), stdin); 
                playlistName[strcspn(playlistName, "\n")] = '\0';
                // printf("\033[2J\033[H");
                system("clear");
                SpotifyText();
                strip(playlistName);
                playlist = readPlaylist(playlist,playlistName);
                break;

            case 'f':
                return playlist;

            default:
                printf("\n\033[0;37;41mInvalid choice. Please try again.\033[0m\n");
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
