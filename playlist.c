#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "playlist.h"

/***************************************************************************/
void song_to_string(const song_t *song, char *str, unsigned size) {
  assert (song != NULL);
  assert (str  != NULL);

    int seconds = song->duration % 60;
    int minutes = song->duration / 60;

    snprintf(str, size, "%s - %s (%2d:%02d)", song->artist, song->title, minutes, seconds);
}

/***************************************************************************/
unsigned playlist_length(const playlist_t playlist) {
    unsigned count = 0;
    playlist_node_t* cur = playlist.queue;
    
    while (cur != NULL) {
        count++;
        cur = cur->next;
    }

  return count; 
}

/***************************************************************************/
int playlist_add_song(playlist_t *playlist, char *title, char *artist, unsigned duration) {
  assert (playlist != NULL);
  assert (title != NULL);
  assert (artist != NULL);
  assert (strlen(title) <= 50);
  assert (strlen(artist) <= 50);

    song_t* song = malloc(sizeof(song_t));    
    if (song == NULL) return 1;

    strncpy(song->artist, artist, 50);
    strncpy(song->title, title, 50);
    song->duration = duration;

    playlist_node_t* node = malloc(sizeof(playlist_node_t));
    node->data = song;
    node->next = NULL;

    if (playlist->queue == NULL) {
        playlist->queue = node;
        return 0;
    }

    playlist_node_t* cur = playlist->queue;
    for (; cur->next != NULL; cur = cur->next) {}
    cur->next = node;
    

  return 0; 
}

/***************************************************************************/
void playlist_remove_song(playlist_t *playlist, char *title, char *artist) {
  assert (playlist != NULL);
  assert (title != NULL);
  assert (artist != NULL);

    // We moeten itereren door de lijst, en bijhouden welke de vorige node was
    // zo kunnen we de twee lijsten die we krijgen door een specifieke song te
    // removen terug "aan elkaar nieten"

    playlist_node_t* cur = playlist->queue;
    playlist_node_t* prev = NULL;

    while (cur != NULL) {
        if (strcmp(cur->data->title, title) == 0 && 
            strcmp(cur->data->artist, artist) == 0) {
            // Geval 1: song om te removen is de head van de lijst
            if (prev == NULL) {
                // nieuwe head is gewoon de next van het verwijderde liedje
                playlist->queue = cur->next;
            } else {
                // Geval 2: song is in het midden of einde
                // het vorige element wijst nu naar de next van het verwijderde liedje
                prev->next = cur->next;
            } 

            // Vergeet niet het geheugen van de song free te geven
            free(cur->data);
            free(cur);
            return;
        }
        prev = cur;
        cur = cur->next;
    }

  /* TODO: Implement */
}

/***************************************************************************/
void playlist_move_song_to_front(playlist_t *playlist, unsigned index) {
  assert (playlist != NULL);
    // Zoek de node op een specifieke index, remove het (zonder free!) en re-insert
    // aan de head
    if (playlist->queue == NULL || index == 0) {
        return;
    }

    playlist_node_t* cur = playlist->queue;
    playlist_node_t* prev = NULL;
    unsigned i = 0;

    while (cur != NULL && i < index) {
        prev = cur;
        cur = cur->next;
        i++;
    }

    // index out of bounds
    if (cur == NULL) {
        return;
    }

    // detach de node van zijn huidige plaats
    prev->next = cur->next;
    // plaats node aan het begin
    cur->next = playlist->queue;
    playlist->queue = cur;
}

/***************************************************************************/
void playlist_play_next(playlist_t *playlist) {
  assert (playlist != NULL);

    // als een song aan het spelen is, vergeet niet te freeen
    if (playlist->current != NULL) {
        free(playlist->current);
        playlist->current = NULL;
    }

    // als de queue leeg is, stop
    if (playlist->queue == NULL) {
        return;
    }

    // pop head van queue en steek het in current
    playlist_node_t* head = playlist->queue;
    playlist->current = head->data;

    // nieuwe head is next van de reeds gepopte head
    playlist->queue = head->next;

    // Hier geven we het geheugen van head vrij, maar NIET de data, deze zit nu
    // in playlist->current, en zal vrijgegeven worden als het volgende liedje
    // gespeeld wordt
    free(head);
}

/***************************************************************************/
void playlist_reverse(playlist_t *playlist) {
  assert (playlist != NULL);

    if (playlist->queue == NULL) {
        return;
    }

    playlist_node_t* prev = NULL;
    playlist_node_t* cur = playlist->queue;
    playlist_node_t* next = NULL;

    while (cur != NULL) {
        next = cur->next;   // bewaar een reference in de next node
        cur->next = prev;   // draai de pointer om
        prev = cur;         // verschuif prev voorwaarts
        cur = next;         // verschuif cur voorwaarts
    }

    // reset de head naar de laatste node die we hebben gezien (zit in prev)
    playlist->queue = prev;
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
