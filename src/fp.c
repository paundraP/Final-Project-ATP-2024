#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "dto.h"
#include "inout.h"
#include "controller.h"

int main() {
//    dashboardMenu();
   //struct Song* songs = createSong("the 1975", "about you", "dont know", 5.45);
   // struct Song* songs1 = createSong("the 1975", "about you", "dont know", 5.45);
    struct Playlist* playlists = createPlaylist("pujo ganteng");
    dashboardMenu(playlists);
//    addSongtoPlaylist(playlists, songs);
  //  addSongtoPlaylist(playlists, songs1);
  //  playlists = addNewPlaylist(playlists, "Pujo sedih");
  //  playlists = addNewPlaylist(playlists, "Pujo bahagia");
   // printPlaylist(playlists);
  //  printSongInsidePlaylist(playlists);
  //  free(songs);
   // free(playlists);

    return 0;
}
