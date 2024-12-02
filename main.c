#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "controller.h"
#include "sorting.h"

void printSongInsidePlaylist(Playlist* playlist, int index) {
    Playlist* curr = findPlaylistByIndex(playlist, index);
    int nameLength = strlen(playlist->playlistName);
    int padding = (159 - nameLength - 10) / 2;

    printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", playlist->playlistName, padding, "=======================================================================================");
    printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");
        Song* song = curr->song; 
        while (song != NULL) {  
            printf("%-50s %-50s %-50s %.2f\n", song->title, song->singer, song->album, song->time);
            song = song->next; 
        }
        curr = curr->next; 
    printf("\n");
}

void printPlaylist(Playlist* playlist) {
    Playlist* curr = playlist;
    printf("Playlists you've created:\n");
    int i = 1;
    printf("%-3s %-50s\n", "No.", "Playlist Name");
    while (curr != NULL) {
        printf("%-3d %-50s\n", i, curr->playlistName);
        i++;
        curr = curr->next;
    }
    printf("\n");
}

void playlistDetail(Playlist* playlist){
    // nantinya buat ngesorting isi detail playlist jika user minta.
}

void dashboardMenu(Playlist* playlist){
    char choice;
    char playlistName[50];

    do {
        printf("\n--- Song App Menu ---\n");
        printf("What do you want to do?\n");
        printf("a. Create playlist\n");
        printf("b. See playlist\n");
        printf("c. Save playlist to file\n");
        // printf("f. Insert your playlist from existing file\n");
        printf("d. Exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();
        switch (choice) {
            case 'a':
                printf("Enter playlist name: ");
                fgets(playlistName, sizeof(playlistName), stdin); 
                playlistName[strcspn(playlistName, "\n")] = '\0';
                // printf("%s",playlistName);
		        playlist = addNewPlaylist(playlist, playlistName);
                printf("Playlist created\n");
                break;

            case 'b':
                if (playlist == NULL) {
                    printf("The playlists list is empty.\n");
                } else {
                    printPlaylist(playlist);
                    printf("\npress n for back to menu...\n");
                    while (getchar() != 'n');
                    printf("\033[2J\033[H");                    
                }
                break;

            case 'c':
                printf("coming soon - beta version\n");
                printf("\npress n for back to menu...\n");
                while (getchar() != 'n');
                printf("\033[2J\033[H");
                break;

            case 'd':
                return;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'd');

}


int main() {
    // dashboardMenu(playlists);
    Playlist* playlists = createPlaylist("pujo ganteng");
    Song* songs = createSong("the 1975", "zimbabwe", "dont know", 5.45);
    addSongtoPlaylist(playlists, songs, 1);
    Song* songs1 = createSong("cas", "testing", "dont know", 6.32);
    playlists = addNewPlaylist(playlists, "Pujo sedih");
    addSongtoPlaylist(playlists, songs1, 2);
    // Song* songs2 = createSong("test", "test", "test", 4.32);
    // addSongtoPlaylist(playlists, songs1, 1);
    // playlists = addNewPlaylist(playlists, "Pujo bahagia");
    // addSongtoPlaylist(playlists, songs2, 2);
    // printPlaylist(playlists);
    // sortByTitle(songs);
    // printSongInsidePlaylist(playlists, 2);
    // savePlaylist(playlists, 2);
    // savePlaylist(playlists, 1);
    free(songs);
    free(playlists);

    return 0;
}
