#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dto.h"

struct Playlist* createPlaylist(char name[]);
struct Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time);
void addSongtoPlaylist(struct Playlist* playlist, struct Song* song);
struct Playlist* addNewPlaylist(struct Playlist* head, char playlistname[]);

#endif