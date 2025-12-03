#ifndef PLAYLIST_H
#define PLAYLIST_H

/*****************************************************************************
 *
 * Declaration of the data structures that are used in our playlist representation.
 *
 *****************************************************************************/

typedef struct song_s {
   char title[50];
   char artist[50];
   unsigned duration;      // in seconds
} song_t;

typedef struct playlist_node_s {
   song_t *data;
   struct playlist_node_s *next;
} playlist_node_t;

typedef struct playlist_s {
   playlist_node_t *queue; // The queue of next songs
   song_t *current;        // The "currently playing" song
} playlist_t;

/*****************************************************************************
 *
 * Declaration and documentation of the functions that you have to implement.
 * The documentation of each function starts with the function signature.
 *
 *****************************************************************************/

/* -----------------------------------------------------------------
 * void song_to_string(const song_t *song, char *str, unsigned size)
 * -----------------------------------------------------------------
 *
 * Stores the string representation of the given song 'song' into the character
 * string (a memory region) pointed to by 'str' according to the format
 * specified below. The variable 'size' specifies the available size of the
 * given memory region specified in number of characters.
 * 
 * Format: <artist> " - " <title> " (" <duration> ")"
 *
 * Additional constraints:
 *   - Display the duration as a timestamp mm:ss
 *      - Use two places for both the minutes and seconds
 *      - Pad minutes lower than 10 with leading spaces
 *      - Pad seconds lower than 10 with leading zeros
 * 
 * You must use snprintf to implement this. snprintf is one of the functions
 * that are provided by the C standard library. "man snprintf" will give you
 * access to its extensive documentation.
 *
 * Example: A song with artist "Rick Astley", title "Never Gonna Give You Up" and 
            duration 214 has the following string presentation:
            "Rick Astley - Never Gonna Give You Up (3:34)"
 *
 * PRECONDITIONS: 
 *   - song != NULL
 *   - str != NULL
 *   - for every i in 0..size, (str+i) points to valid memory
 *   - size > 0
 */
void song_to_string(const song_t *song, char *str, unsigned size);

/* -----------------------------------------------
 * unsigned playlist_length(const playlist_t playlist)
 * -----------------------------------------------
 *
 * Counts and returns the amount of playlist nodes in the queue.
 */
unsigned playlist_length(const playlist_t playlist);

/* -------------------------------------------------------------------------------------------------
 * int playlist_add_song(playlist_t *playlist, char *title, char *artist, unsigned duration)
 * -------------------------------------------------------------------------------------------------
 *
 * Allocates memory for a new song and playlist node and adds it to the given playlist.
 *
 * The new playlist node is inserted *at the end* of the playlist.
 *
 * Returns 0 when the dynamic memory allocation fails. Returns 1 otherwise.
 *
 * HINT:
 *  - Use `strcpy` to copy the given strings to the song_s struct
 *
 * PRECONDITIONS:
 *  - playlist is properly intialised
 *  - title is properly intialised
 *  - artist is properly intialised
 */
int playlist_add_song(playlist_t *playlist, char *title, char *artist, unsigned duration);

/* -------------------------------------------------------------------------------
 * void playlist_remove_song(playlist_t *playlist, char *title, char *artist)
 * -------------------------------------------------------------------------------
 *
 * Removes all song with the given artist and the given title from the given
 * playlist.
 *
 * The memory that was allocated by a previous call to playlist_add_song must
 * be released for every song that is removed from the playlist.
 *
 * HINT:
 *  - Use `strcmp` to compare strings, a return value of 0 means that the strings match
 *
 * PRECONDITIONS:
 *  - playlist != NULL
 *  - title != NULL
 *  - artist != NULL
 */
void playlist_remove_song(playlist_t *playlist, char *title, char *artist);

/* --------------------------------------------------------------
 * void playlist_move_song_to_front(playlist_t *playlist, unsigned index)
 * --------------------------------------------------------------
 *
 * Moves the song at the given index to the front of the queue
 * Does nothing if index >= length(queue)
 *
 * PRECONDITIONS:
 *  - playlist != NULL
 */
void playlist_move_song_to_front(playlist_t *playlist, unsigned index);

/* ---------------------------------------------
 * void playlist_play_next(playlist_t *playlist)
 * ---------------------------------------------
 *
 * Frees the song currently in `current`
 * Moves the song at the front of the queue to `current` if the queue is not empty
 * Removes and frees the first playlist node 
 *   (NOTE: Do not free the song unless you copy its values to a new song_t)
 * 
 * PRECONDITIONS:
 *  - playlist != NULL
 */
void playlist_play_next(playlist_t *playlist);

/* ----------------------------------------
 * void playlist_reverse(playlist_t *playlist)
 * ----------------------------------------
 *
 * Reverses the order of the playlist
 *
 * PRECONDITIONS:
 *  - playlist != NULL
 */
void playlist_reverse(playlist_t *playlist);

// We've implemented this one for you
void deallocate_playlist(playlist_t playlist);

// We've implemented this one for you
void playlist_print(const playlist_t *playlist);

#endif