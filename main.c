#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "controller.h"
#include "sorting.h"

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
        printf("\nInvalid option\n");
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
    // printf("\n");
}

void playlistDetail(Playlist* playlist){
    // nantinya buat ngesorting isi detail playlist jika user minta.
}

void playlistMenu(Playlist* playlist) {
    char choice;
    char songName[50];

    do {
        printf("\n--- Playlist Menu ---\n");
        printf("1. See songs in playlist\n");
        printf("2. Add a song to playlist\n");
        printf("3. Remove a song from playlist\n");
        printf("4. Back to main menu\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        getchar();

        switch (choice) {
            case '1':
                // if (playlist->songs == NULL) {
                    // printf("No songs in the playlist.\n");
                // } else {
                //     printSongs(playlist); // Assuming a function exists to print songs in the playlist
                // }
                printf("Choose playlist number:");
                int idx;
                scanf("%d",&idx);
                printSongInsidePlaylist(playlist,idx);
                break;

            case '2':
                printf("Enter the name of the song to add: ");
                // fgets(songName, sizeof(songName), stdin);
                // songName[strcspn(songName, "\n")] = '\0';
                // addSongToPlaylist(playlist, songName); // Assuming a function exists to add songs
                printf("\nSong added to playlist.\n");
                break;

            case '3':
                printf("Enter the name of the song to remove: ");
                // fgets(songName, sizeof(songName), stdin);
                // songName[strcspn(songName, "\n")] = '\0';
                // if (removeSongFromPlaylist(playlist, songName)) { // Assuming a function exists to remove songs
                //     printf("Song removed from playlist.\n");
                // } else {
                //     printf("Song not found in playlist.\n");
                // }
                break;

            case '4':
                printf("\033[2J\033[H");                    
                break;

            default:
                printf("\nInvalid choice. Please try again.\n\n");
        }
    } while (choice != '4');
    
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
		        playlist = addNewPlaylist(playlist, playlistName);
                printf("\nPlaylist created\n\n");
                break;

            case 'b':
                // printPlaylist(playlist);
                if (playlist == NULL) {
                    printf("\nThe playlists list is empty.\n");
                } else {
                    printPlaylist(playlist);
                    // printSongInsidePlaylist(playlist,1);
                    playlistMenu(playlist);
                    // while (getchar() != '4');
                    // printf("\033[2J\033[H");                    
                }
                break;

            case 'c':
                printf("\ncoming soon - beta version\n");
                printf("\npress n for back to menu...\n");
                while (getchar() != 'n');
                printf("\033[2J\033[H");
                break;

            case 'd':
                free(playlist);
                return;
                // break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }
    } while (choice != 'd');

}


int main() {
    Playlist* playlists = NULL;
    dashboardMenu(playlists);
    // Playlist* playlists = createPlaylist("pujo ganteng");
    // Song* songs = createSong("the 1975", "zimbabwe", "dont know", 5.45);
    // addSongtoPlaylist(playlists, songs, 1);
    // Song* songs1 = createSong("cas", "testing", "dont know", 6.32);
    // playlists=addNewPlaylist(playlists, "Pujo sedih");
    // addSongtoPlaylist(playlists, songs1, 2);
    // Song* songs2 = createSong("test", "test", "test", 4.32);
    // addSongtoPlaylist(playlists, songs1, 1);
    // playlists = addNewPlaylist(playlists, "Pujo bahagia");
    // addSongtoPlaylist(playlists, songs2, 2);
    // printPlaylist(playlists);
    // sortByTitle(songs);
    // printSongInsidePlaylist(playlists, 1);
    // savePlaylist(playlists, 2);
    // savePlaylist(playlists, 1);
    // free(songs);
    free(playlists);

    return 0;
}
