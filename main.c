#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "inout.h"
#include "controller.h"
#include "sorting.h"

int main() {
    struct Playlist* playlists = createPlaylist("pujo ganteng");
    dashboardMenu(playlists);
    // Song* songs = createSong("the 1975", "zimbabwe", "dont know", 5.45);
    // Song* songs1 = createSong("cas", "testing", "dont know", 6.32);
    // Playlist* playlists = createPlaylist("pujo ganteng");
    // addSongtoPlaylist(playlists, songs);
    // addSongtoPlaylist(playlists, songs1);
    // playlists = addNewPlaylist(playlists, "Pujo sedih");
    // playlists = addNewPlaylist(playlists, "Pujo bahagia");
    // printPlaylist(playlists);
    // printSongInsidePlaylist(playlists);
    // sortByMinute(songs);
    // sortByTitle(songs);
    // printSongInsidePlaylist(playlists);
    // free(songs);
    free(playlists);

    return 0;
}
