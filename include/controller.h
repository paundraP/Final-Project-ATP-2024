#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dto.h"

Playlist* findPlaylistByIndex(Playlist* playlist, int index);
Playlist* createPlaylist(char name[]);
Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time);
void addSongtoPlaylist(Playlist* playlist, Song* song, int index);
Playlist* addNewPlaylist(Playlist* playlist, char playlistname[]);
int playlistExists(struct Playlist* head, char playlistname[]);
Playlist* deleteSongFromPlaylist(Playlist* playlist, char playlistname[]);
Playlist* deletePlaylist(Playlist* playlist);
void savePlaylist(Playlist* playlist, int index);

#endif
