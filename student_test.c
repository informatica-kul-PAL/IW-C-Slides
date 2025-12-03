#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
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
static void test_song_to_string(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_length(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_add_song(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_remove_song(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_move_song_to_front(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_play_next(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
static void test_playlist_reverse(void)
{
  /* TODO: Add your own test here (see pal_test.c for some inspiration) */
}

/****************************************************************************/
void student_test(void)
{
  memset(&stats, 0, sizeof(stats));

  test_song_to_string();
  test_playlist_length();
  test_playlist_add_song();
  test_playlist_remove_song();
  test_playlist_move_song_to_front();
  test_playlist_play_next();
  test_playlist_reverse();

  fprintf(stdout,
          "Student test suite: %d of %d passed\n",
          stats.pass,
          stats.pass + stats.fail);
}
