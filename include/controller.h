#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dto.h"

Playlist* createPlaylist(char name[]);
Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time);
void addSongtoPlaylist(Playlist* playlist, Song* song);
Playlist* addNewPlaylist(Playlist* head, char playlistname[]);
Playlist* deleteSongFromPlaylist(Playlist* head, char playlistname[]);

#endif