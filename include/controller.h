#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "dto.h"

Playlist* findPlaylistByIndex(Playlist* playlist, int index);
Playlist* createPlaylist(char name[]);
Song* createSong(char new_singer[], char new_title[], char new_album[], double new_time,char url[], char status[]);
void addSongToPlaylist(Playlist* playlist, int index, char title[], char singer[], char album[], double time, char url[], char status[]);
Playlist* addNewPlaylist(Playlist* playlist, char playlistname[]);
int playlistExists(struct Playlist* playlist, char playlistname[]);
int isSongInPlaylist(Song* songList, const char* title);
Playlist* deleteSongFromPlaylist(Playlist* playlist, int index, char songName[]);
Playlist* deletePlaylist(Playlist* playlist, int index);
void savePlaylist(Playlist* playlist, int index);
int listFileInPlaylistFolder();
Playlist* findPlaylistByName(Playlist* head, char playlistName[]);
Playlist* readPlaylist(struct Playlist* playlist, char playlistName[]);
char* strip(char* str);
void playSong(Playlist* playlist, int index, char songName[]);
double getSongDuration(const char* songName);
void playProgressBar(int totalSeconds);
#endif
