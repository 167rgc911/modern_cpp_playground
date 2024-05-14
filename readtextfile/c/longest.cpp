// =====================================================================================
//
//       Filename:  longest.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  05/14/24 04:45:58
//       Revision:  none
//       Compiler:  g++ -std=c99 -Wall -Werror -Wpedantic -Wextra
//
//         Author:  rgc (), sessyargc.jp@gmail.com
//   Organization:
//
// =====================================================================================

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

const int MAX_CHARS = 1024; // only line modified from longest.c
const int NUM_WORDS = 10;

/*
IMPL_1 uses an array of struct. the newly defined struct stores the length of
the word as well as the word itself, this prevents multiple strlen() API calls
but storage use +40bytes (sizeof(int) * NUM_WORDS)

IMPL_2 uses a straight array. calls strlen() many times in the insertion loop.
no storage tradeoff .. but might have a speed performance tradeoff depends
if a pointer access is faster than an inline fn call (assumes strlen() is
inlined)
 */

#define IMPL_1
/* #undef IMPL_1 */

#ifdef IMPL_1
typedef struct
{
  int len;
  char str[MAX_CHARS];
} word_t;
#endif

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      fprintf (stderr, "Usage: %s wordlist.txt\n", argv[0]);
      return EXIT_FAILURE;
    }

  FILE *fp = fopen (argv[1], "r");
  if (fp == NULL)
    {
      perror (argv[1]);
      return EXIT_FAILURE;
    }

    /* no dynamic memory allocations */
#ifdef IMPL_1
  word_t longest_words[NUM_WORDS];
  memset (longest_words, 0, sizeof (longest_words));
#else
  char longest_words[NUM_WORDS][MAX_CHARS];
  memset (longest_words, 0, sizeof (longest_words));
#endif

  char buf[MAX_CHARS];
  while (fgets (buf, sizeof (buf), fp) != NULL)
    {
#ifdef IMPL_1
      int len = strlen (buf);
#else
      unsigned int len = strlen (buf);
#endif
      for (int i = 0; i < NUM_WORDS; ++i)
        {
#ifdef IMPL_1
          if (longest_words[i].len < len)
            {
              memcpy (longest_words[i].str, buf, len);
              longest_words[i].len = len;
              break;
            }
#else
          if (strlen (longest_words[i]) < len)
            {
              memcpy (longest_words[i], buf, len);
              break;
            }
#endif
        }
      /* pedantic */
      memset (buf, 0, MAX_CHARS);
    }

  for (int i = 0; i < NUM_WORDS; ++i)
    {
#ifdef IMPL_1
      fprintf (stdout, "%s", longest_words[i].str);
#else
      fprintf (stdout, "%s", longest_words[i]);
#endif
    }

  return EXIT_SUCCESS;
}
