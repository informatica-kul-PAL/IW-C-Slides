#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "playlist.h"

/***************************************************************************/
void song_to_string(const song_t *song, char *str, unsigned size) {
  assert (song != NULL);
  assert (str  != NULL);

  str[0] = '\0'; /* TODO: Replace with your implementation */
}

/***************************************************************************/
unsigned playlist_length(const playlist_t playlist) {
  return 42; /* TODO: Replace with your implementation */
}

/***************************************************************************/
int playlist_add_song(playlist_t *playlist, char *title, char *artist, unsigned duration) {
  assert (playlist != NULL);
  assert (title != NULL);
  assert (artist != NULL);
  assert (strlen(title) <= 50);
  assert (strlen(artist) <= 50);

  return 42; /* TODO: Replace with your implementation */
}

/***************************************************************************/
void playlist_remove_song(playlist_t *playlist, char *title, char *artist) {
  assert (playlist != NULL);
  assert (title != NULL);
  assert (artist != NULL);

  /* TODO: Implement */
}

/***************************************************************************/
void playlist_move_song_to_front(playlist_t *playlist, unsigned index) {
  assert (playlist != NULL);

  /* TODO: Implement */
}

/***************************************************************************/
void playlist_play_next(playlist_t *playlist) {
  assert (playlist != NULL);

  /* TODO: Implement */
}

/***************************************************************************/
void playlist_reverse(playlist_t *playlist) {
  assert (playlist != NULL);

  /* TODO: Implement */
}

/***************************************************************************/
void deallocate_playlist(playlist_t playlist) {
  playlist_node_t *next = NULL;
  for (playlist_node_t *node = playlist.queue; node != NULL; node = next) {
    next = node->next;
    free(node->data);
    free(node);
  }
}

/***************************************************************************/
void playlist_print(const playlist_t *playlist) {
  assert (playlist != NULL);

  printf("Playlist with %u songs in the queue:\n", playlist_length(*playlist));

  char str[120];

  printf("  Current song:\n");
  if (playlist->current != NULL) {
      song_to_string(playlist->current, str, sizeof(str));
      printf("    %s\n", str);
  } else {
      printf("    (none)\n");
  }

  printf("  Queue:\n");

  playlist_node_t * node = playlist->queue;
  if (node == NULL) {
    printf("    (empty)\n");
  }
  while (node != NULL) {
    song_to_string(node->data, str, sizeof(str));
    printf("    %s\n", str);
    node = node->next;
  }
}