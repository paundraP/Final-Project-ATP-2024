#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "controller.h"
#include "sorting.h"


#define MAX_LEN 128
void SpotifyText(){
    printf("\033[1;32m");
    printf("\n          ██████████                                                                                            \n");
    printf("        ██████████████████                                                                                        \n");
    printf("     ████████████████████████                                                                                     \n");
    printf("    ██████████████████████████                                                                                    \n");
    printf("  ██████████████████████████████                                                       ███                        \n");
    printf(" █████                  █████████        █████████                             ███    ████   █████                \n");
    printf(" █████      █████           █████       ███    ███                             ███          ███                   \n");
    printf("█████████████████████████    █████      ███         ███ ██████     ████████   ████████ ███ █████████     ████ ██  \n");
    printf("███████               ████████████      ████████    ████    ████  ████   ████  ████    ███  ███   ███    ███      \n");
    printf("███████   ████████        ████████         ███████  ███      ███ ███      ████ ███     ███  ███    ███  ███       \n");
    printf("████████████████████████   ███████              ███ ███      ███ ███      ████ ███     ███  ███    ███████        \n");
    printf(" ██████               ███████████       ███     ███ ████    ████  ███    ████  ████    ███  ███     ██████        \n");
    printf(" ████████████████████    ████████       ██████████  ███████████    █████████    █████  ███  ███      ████         \n");
    printf("  ██████████████████████████████                    ███                                           █  ███          \n");
    printf("    ██████████████████████████                      ███                                           █████           \n");
    printf("     ████████████████████████                                                                                     \n");
    printf("        ██████████████████                                                                                        \n");
    printf("           ████████████                                                                                          \n");
    printf("\033[0m");

}
void printSongInsidePlaylist(Playlist* playlist, int index) {
    Playlist* curr = findPlaylistByIndex(playlist, index);
    if(curr != NULL){
        int nameLength = strlen(playlist->playlistName);
        int padding = (159 - nameLength - 10) / 2;
        Song* song = curr->song; 
        if(song != NULL){
            printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", playlist->playlistName, padding, "=======================================================================================");
            printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");
                while (song != NULL) {  
                    printf("%-50s %-50s %-50s %.2f\n", song->title, song->singer, song->album, song->time);
                    song = song->next; 
                }
                curr = curr->next; 
            printf("\n");
        }else{
            printf("\nNo songs in this playlist\n");
        }
    }else{
        printf("\nInvalid number, playlist not exists\n");
    }
}

void printPlaylist(Playlist* playlist) {
    Playlist* curr = playlist;
    printf("\nPlaylists you've created:\n\n");
    int i = 1;
    printf("%-3s %-50s\n", "No.", "Playlist Name");
    while (curr != NULL) {
        printf("%-3d %-50s\n", i, curr->playlistName);
        i++;
        curr = curr->next;
    }
    printf("NULL\n");
}

void playlistMenu(Playlist* playlist) {
    char choice, extra;
    char title[50], singer[50], album[50], remove[50];
    float duration;
    int idx, idxtoremove;

    do {
        // SpotifyText();
        printf("\033[1;32m");
        printf("\033[1m\n-- PLAYLIST MANAGER --\033[0m\n");
        printf("\033[0m");
        printf("1. See songs in playlist\n");
        printf("2. Add a song to playlist\n");
        printf("3. Remove a song from playlist\n");
        printf("4. Delete playlist\n");
        printf("5. Back to main menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();

        switch (choice) {
            case '1':         
                printf("\033[2J\033[H");
                SpotifyText();
                printPlaylist(playlist);
                printf("see song inside playlist!\n");
                printf("Choose playlist number: ");
                scanf("%d",&idx);
                printSongInsidePlaylist(playlist,idx);
                break;

            case '2':
                printf("\033[2J\033[H");
                SpotifyText();
                printPlaylist(playlist);
                printf("add song to playlist!\n");
                printf("Choose playlist number: ");
                scanf("%d",&idx);
                getchar();

                printf("Enter the singer of the song to add: ");
                fgets(singer, sizeof(singer), stdin); 
                singer[strcspn(singer, "\n")] = '\0';
                if(singer[0] == '\0'){
                    printf("the singer is required\n");
                    break;
                }

                printf("Enter the title of the song to add: ");
                fgets(title, sizeof(title), stdin); 
                title[strcspn(title, "\n")] = '\0';
                if(title[0] == '\0'){
                    printf("the title is required\n");
                    break;
                }

                printf("Enter the album of the song to add: ");
                fgets(album, sizeof(album), stdin); 
                album[strcspn(album, "\n")] = '\0';
                if(album[0] == '\0'){
                    printf("the album is required\n");
                    break;
                }

                printf("Enter the duration of the song to add with format (0.00): ");
                if (scanf("%f%c", &duration, &extra) == 2 && extra == '\n');
                else {
                    printf("Invalid input. must be a float.\n");
                    while ((extra = getchar()) != '\n' && extra != EOF);
                    break;
                }
                
                addSongToPlaylist(playlist, idx, title, singer, album, duration);
                sortByTitle(playlist);
                break;

            case '3':
                printf("\033[2J\033[H");
                SpotifyText();
                printPlaylist(playlist);
                printf("enter the number of the playlist that contains the song you want to delete: ");
                scanf(" %d",&idxtoremove);
                getchar();
                printSongInsidePlaylist(playlist,idxtoremove);
                printf("Enter the name of the song to remove: ");
                fgets(remove, sizeof(remove), stdin); 
                remove[strcspn(remove, "\n")] = '\0';
                deleteSongFromPlaylist(playlist, idxtoremove, remove);
                break;
            
            case '4':
                printf("\033[2J\033[H");
                SpotifyText();
                printPlaylist(playlist);
                printf("enter the number of the playlist you want to delete: ");
                scanf(" %d", &idxtoremove);
                deletePlaylist(playlist, idxtoremove);
                break;
            case '5':
                printf("\033[2J\033[H");       
                SpotifyText();             
                break;

            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }
    } while (choice != '5');
    
}

void dashboardMenu(Playlist* playlist){
    char choice;
    int save;
    char playlistName[50];

    do {
        // SpotifyText();
        printf("\033[1;32m");
        printf("\033[1m\n-- SONG APP MENU --\033[0m\n");
        printf("\033[0m");
        printf("What do you want to do? 😊\n");
        printf("a. Create playlist\n");
        printf("b. See playlist\n");
        printf("c. Save playlist to file\n");
        printf("d. Insert your playlist from existing file\n");
        printf("e. Exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();
        switch (choice) {
            case 'a':
                printf("Enter playlist name: ");
                fgets(playlistName, sizeof(playlistName), stdin); 
                playlistName[strcspn(playlistName, "\n")] = '\0';
		        playlist = addNewPlaylist(playlist, playlistName);
                SpotifyText();
                break;


            case 'b':
                if (playlist == NULL) {
                    printf("\nThe playlists list is empty.\n");
                } else {
                    printf("\033[2J\033[H");    
                    SpotifyText();                
                    printPlaylist(playlist);
                    playlistMenu(playlist);
                }
                break;

            case 'c':
                printf("\033[2J\033[H");   
                SpotifyText();
                if(playlist == NULL){
                    printf("youre playlist is empty yet");
                }else{
                    printPlaylist(playlist);
                    printf("Which playlist you want to save? ");
                    scanf(" %d", &save);
                    savePlaylist(playlist, save);
                }
                    printf("\npress n for back to menu...\n");
                    while (getchar() != 'n');
                    printf("\033[2J\033[H");
                    SpotifyText();
                    break;                
            case 'd':
                printf("Coming soon - Beta version");
                break;

            case 'e':
                free(playlist);
                return;
                // break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 'e');

}

int main(){
    Playlist* playlists = NULL;
    // listFileInPlaylistFolder();
    // readPlaylist();
    SpotifyText();
    dashboardMenu(playlists);
    return 0;
}
