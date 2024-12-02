#include <stdio.h>
#include <string.h>
#include "dto.h"
#include "controller.h"

void printSongInsidePlaylist(Playlist* head) {
    Playlist* curr = head;
    int nameLength = strlen(head->playlistName);
    int padding = (159 - nameLength - 10) / 2;

    printf("%.*s Playlist %s %.*s\n", padding, "=======================================================================================", head->playlistName, padding, "=======================================================================================");
    printf("%-50s %-50s %-50s %s\n", "Judul", "Penyanyi", "Album", "Waktu");

    while (curr != NULL) {
        Song* song = curr->song; 
        while (song != NULL) {  
            printf("%-50s %-50s %-50s %.2f\n", song->title, song->singer, song->album, song->time);
            song = song->next; 
        }
        curr = curr->next; 
    }
    printf("\n");
}

void printPlaylist(Playlist* head) {
    Playlist* curr = head;
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



void dashboardMenu(struct Playlist* head){
    char choice;

    do {
        printf("\n--- Song App Menu ---\n");
        printf("What do you want to do?\n");
        printf("a. Create playlist\n");
        printf("b. Add song to Playlist\n");
        printf("c. See playlist\n");
        printf("d. Remove song from playlist\n");
        printf("e. Save playlist to file\n");
        printf("f. Insert your playlist from existing file\n");
        printf("g. Exit program\n");
        printf("Enter your choice: ");
        scanf(" %c", &choice);
        switch (choice) {
            case 'a':
		head = addNewPlaylist(head, "Pujo sedih");
//		char playlistname[100];
//		char str[100];  // Declare a character array to hold the string
//                break;
//		printf("Enter a string: ");
//		fgets(str, sizeof(str), stdin); 
  //              printf("playlist name %s\n",playlistname);
                break;

	    case 'b':
                printf("a\n");
                break;

            case 'c':
		printPlaylist(head);
		printf("\npress n for back to menu...\n");
		while (getchar() != 'n');
		printf("\033[2J\033[H");
                break;

            case 'd':
                printf("coming soon - beta version\n");
		printf("\npress n for back to menu...\n");
                while (getchar() != 'n');
                printf("\033[2J\033[H");
                break;

            case 'e':
                printf("coming soon - beta version\n");
		printf("\npress n for back to menu...\n");
                while (getchar() != 'n');
                printf("\033[2J\033[H");
                break;

            case 'f':
                printf("coming soon - beta version\n");
		printf("\npress n for back to menu...\n");
                while (getchar() != 'n');
                printf("\033[2J\033[H");
                break;

            case 'g':
                return 0;
                break;

            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 'g');

}

void playlistDetail(Playlist* head){
    // nantinya buat ngesorting isi detail playlist jika user minta.
}
