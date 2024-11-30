#ifndef INOUT_H
#define INOUT_H

#include "dto.h"

void printSongInsidePlaylist(struct Playlist* head);
void printPlaylist(struct Playlist* head);
void dashboardMenu(char* choice);
void playlistDetail(struct Playlist* head);

#endif 