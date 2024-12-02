#ifndef DTO_H
#define DTO_H

typedef struct Song {
    char title[100];
    char singer[100];
    char album[100];
    double time;
    struct Song* next;
} Song;

typedef struct Playlist {
    char playlistName[100];
    struct Song* song;
    struct Playlist* next;
} Playlist;

#endif