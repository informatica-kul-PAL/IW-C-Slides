#include <stdio.h>
#include <stdlib.h>


#include "playlist.h"
#include "test.h"

int main(void)
{
  setvbuf(stdout, NULL, _IONBF, 0);
  setvbuf(stderr, NULL, _IONBF, 0);

  /* 1. Run PAL tests */
  fprintf(stdout, "--------------------------------------------------------\n");
  fprintf(stdout, "PAL test suite\n");
  fprintf(stdout, "--------------------------------------------------------\n");
  pal_test();

  /* 2. How to use the playlist API */
  fprintf(stdout, "\n");
  fprintf(stdout, "--------------------------------------------------------\n");
  fprintf(stdout, "Example code\n");
  fprintf(stdout, "--------------------------------------------------------\n");

  /* 2.1 Create an empty playlist with default values (NULL). */
  playlist_t playlist = { NULL, NULL };

  /* 2.2 Add a song to the playlist */
  if (playlist_add_song(&playlist, "Rick Astley", "Never gonna give you up", 214) != 0)
  {
      fprintf(stderr, "playlist_add_song() failed\n");
  }

  /* 2.3 Add more songs.
      *
      * NOTE: In general it is bad practice to ignore the return code of
      *       functions. We do it here to keep the example code compact.
      */
  (void) playlist_add_song(&playlist, "Kaslai", "Program in C", 51);
  (void) playlist_add_song(&playlist, "Michael Littman", "The Sorter", 212);

  /* 2.4 Print the playlist */
  playlist_print(&playlist);

  printf("\n");

  /* 2.5 Play the next song */
  playlist_play_next(&playlist);

  playlist_print(&playlist);

  /* 2.5 Release the memory that was allocated for the playlist */
  deallocate_playlist(playlist);

  /* 3. Run student tests */
  fprintf(stdout, "\n");
  fprintf(stdout, "--------------------------------------------------------\n");
  fprintf(stdout, "Student test suite\n");
  fprintf(stdout, "--------------------------------------------------------\n");

  student_test();

  return 0;
}
