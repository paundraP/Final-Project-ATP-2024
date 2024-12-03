#include <stdio.h>
#include <string.h>
#include "dto.h"
// ALL SORTED ALGORITM IN THIS PROGRAM IS USE BUBLE SORT
// WE CHOOSE BUBLE SORT BECAUSE ITS EASY TO USE AND IMPLEMENT
// BUT ITS SLOW FOR LARGE DATA TO SORTING THEM


void sortByTitle(Playlist* playlist){
    Song* song = playlist->song;
    if (song == NULL) return;

    int swapped;
    Song *ptr1, *lptr = NULL;

    do {
        swapped = 0;
        ptr1 = song;

        while (ptr1->next != lptr) {
            if (strcmp(ptr1->title, ptr1->next->title) > 0) { 
                // Swap the contents of the nodes
                char tempTitle[100], tempSinger[100], tempAlbum[100];
                double tempTime;

                strcpy(tempTitle, ptr1->title);
                strcpy(tempSinger, ptr1->singer);
                strcpy(tempAlbum, ptr1->album);
                tempTime = ptr1->time;

                strcpy(ptr1->title, ptr1->next->title);
                strcpy(ptr1->singer, ptr1->next->singer);
                strcpy(ptr1->album, ptr1->next->album);
                ptr1->time = ptr1->next->time;

                strcpy(ptr1->next->title, tempTitle);
                strcpy(ptr1->next->singer, tempSinger);
                strcpy(ptr1->next->album, tempAlbum);
                ptr1->next->time = tempTime;

                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);
}