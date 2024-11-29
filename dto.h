struct Song {
    char title[50];
    char singer[50];
    char album[50];
    double time;
    struct Song* next; 
};

struct Playlist {
    char playlistName[50];
    struct Song* song;
    struct Playlist* next;
};