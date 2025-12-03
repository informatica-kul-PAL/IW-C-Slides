#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>

#include "test.h"
#include "playlist.h"

#define TEST(expr) test(expr, __FILE__, __LINE__, #expr)
#define TESTQ(expr) testq(expr, __FILE__, __LINE__)

static struct 
{
  int pass;
  int fail;
} stats;

/****************************************************************************/
static void test(bool pass, char *file, int line, char *expr)
{
  if (pass)
  {
    stats.pass++;
  }
  else
  {
    stats.fail++;
    fprintf(stderr, "%s:%3d: Fail '%s'\n", file, line, expr);
  }
}

/****************************************************************************/
static void testq(bool pass, char *file, int line)
{
  if (pass)
  {
    stats.pass++;
  }
  else
  {
    stats.fail++;
    fprintf(stderr, "%s:%d: Fail\n", file, line);
  }
}

/****************************************************************************/
static void pal_test_song_to_string(void)
{
  char str[120];

  song_t song = {
    "Program in C",
    "Kaslai",
    51
  };

  song_to_string(&song, str, sizeof(str));

  TEST(strcmp(str, "Kaslai - Program in C ( 0:51)") == 0);
}

/****************************************************************************/
static void pal_test_playlist_length(void)
{
  playlist_node_t n1 = {NULL, NULL};
  playlist_node_t n2 = {NULL, &n1};
  playlist_node_t n3 = {NULL, &n2};

  playlist_t playlist = {&n3, NULL};

  TEST(playlist_length(playlist) == 3);
}

/****************************************************************************/
static void pal_test_playlist_add_song(void)
{
  playlist_t playlist = {NULL, NULL};

  playlist_add_song(&playlist, "Kaslai", "Program in C", 51);

  TEST(playlist.queue != NULL);
  if (playlist.queue != NULL) {
    TEST(playlist.queue->next == NULL);
    TEST(playlist.queue->data != NULL);
    if (playlist.queue->data != NULL) {
      TEST(strcmp(playlist.queue->data->artist, "Kaslai") == 0);
      TEST(strcmp(playlist.queue->data->title, "Program in C") == 0);
      TEST(playlist.queue->data->duration == 51);
    }
  }

  playlist_add_song(&playlist, "Michael Littman", "The Sorter", 212);

  TEST(playlist.queue != NULL);
  if (playlist.queue != NULL) {
    TEST(playlist.queue->data != NULL);
    if (playlist.queue->data != NULL) {
      TEST(strcmp(playlist.queue->data->artist, "Kaslai") == 0);
      TEST(strcmp(playlist.queue->data->title, "Program in C") == 0);
      TEST(playlist.queue->data->duration == 51);
    }
    TEST(playlist.queue->next != NULL);
    if (playlist.queue->next != NULL) {
      TEST(playlist.queue->next->next == NULL);
      TEST(playlist.queue->next->data != NULL);
      if (playlist.queue->next->data != NULL) {
        TEST(strcmp(playlist.queue->next->data->artist, "Michael Littman") == 0);
        TEST(strcmp(playlist.queue->next->data->title, "The Sorter") == 0);
        TEST(playlist.queue->next->data->duration == 212);
      }
      TEST(strcmp(playlist.queue->data->artist, "Kaslai") == 0);
      TEST(strcmp(playlist.queue->data->title, "Program in C") == 0);
      TEST(playlist.queue->data->duration == 51);
    }
  }
}

/****************************************************************************/
static void pal_test_playlist_remove_song(void)
{
  song_t *song1 = malloc(sizeof(song_t));
  strcpy(song1->artist, "Kaslai");
  strcpy(song1->title, "Program in C");
  song1->duration = 51;
  
  song_t song2 = {
    "The Sorter",
    "Michael Littman",
    212
  };

  playlist_node_t node2 = {
    &song2,
    NULL
  };

  playlist_node_t *node1 = malloc(sizeof(playlist_node_t));
  node1->data = song1;
  node1->next = &node2;

  playlist_t playlist = {
    node1,
    NULL
  };

  playlist_remove_song(&playlist, "Kaslai", "Program in C");

  TEST(playlist.queue == &node2);
}

/****************************************************************************/
static void pal_test_playlist_move_song_to_front(void)
{
  song_t song1 = {
    "Program in C",
    "Kaslai",
    51
  };  

  song_t song2 = {
    "The Sorter",
    "Michael Littman",
    212
  };

  playlist_node_t node2 = {
    &song2,
    NULL
  };

  playlist_node_t node1 = {
    &song1,
    &node2
  };

  playlist_t playlist = {
    &node1,
    NULL
  };

  playlist_move_song_to_front(&playlist, 1);

  TEST(playlist.queue == &node2);
  TEST(node2.next == &node1);
  TEST(node1.next == NULL);
}

/****************************************************************************/
static void pal_test_play_next(void)
{
  song_t song1 = {
    "Program in C",
    "Kaslai",
    51
  };  

  song_t song2 = {
    "The Sorter",
    "Michael Littman",
    212
  };

  playlist_node_t node2 = {
    &song2,
    NULL
  };

  playlist_node_t *node1 = malloc(sizeof(playlist_node_t));
  node1->data = &song1;
  node1->next = &node2;

  playlist_t playlist = {
    node1,
    NULL
  };

  playlist_play_next(&playlist);

  TEST(playlist.current == &song1);
  TEST(playlist.queue == &node2);
  TEST(node2.next == NULL);
}

/****************************************************************************/
static void pal_test_playlist_reverse(void)
{
  song_t song1 = {
    "Program in C",
    "Kaslai",
    51
  };

  song_t song2 = {
    "The Sorter",
    "Michael Littman",
    212
  };

  song_t song3 = {
    "Never Gonna Give You Up",
    "Rick Astley",
    214
  };

  playlist_node_t node3 = {
    &song3,
    NULL
  };

  playlist_node_t node2 = {
    &song2,
    &node3
  };

  playlist_node_t node1 = {
    &song1,
    &node2
  };

  playlist_t playlist = {
    &node1,
    NULL
  };

  playlist_reverse(&playlist);

  TEST(playlist.queue == &node3);
  TEST(node3.next == &node2);
  TEST(node2.next == &node1);
  TEST(node1.next == NULL);
}

/****************************************************************************/
void pal_test(void)
{
  memset(&stats, 0, sizeof(stats));

  pal_test_song_to_string();
  pal_test_playlist_length();
  pal_test_playlist_add_song();
  pal_test_playlist_remove_song();
  pal_test_playlist_move_song_to_front();
  pal_test_play_next();
  pal_test_playlist_reverse();

  fprintf(stdout,
          "PAL test suite: %d of %d passed\n",
          stats.pass,
          stats.pass + stats.fail);
}
