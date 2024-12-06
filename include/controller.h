#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dto.h"

Playlist* findPlaylistByIndex(Playlist* playlist, int index);
Playlist* createPlaylist(char name[]);
Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time);
void addSongToPlaylist(Playlist* playlist, int index, const char* title, const char* singer, const char* album, double time);
Playlist* addNewPlaylist(Playlist* playlist, char playlistname[]);
int playlistExists(struct Playlist* playlist, char playlistname[]);
int isSongInPlaylist(Song* songList, const char* title);
Playlist* deleteSongFromPlaylist(Playlist* playlist, int index, char songName[]);
Playlist* deletePlaylist(Playlist* playlist, int index);
void savePlaylist(Playlist* playlist, int index);
void listFileInPlaylistFolder();
Playlist* findPlaylistByName(Playlist* head, char playlistName[]);
Playlist* readPlaylist(struct Playlist* playlist, char playlistName[]);
char* strip(char* str);
#endif
