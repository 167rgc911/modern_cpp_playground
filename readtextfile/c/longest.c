/*
 * =====================================================================================
 *
 *       Filename:  longest.c
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/13/24 13:41:24
 *       Revision:  none
 *       Compiler:  gcc -std=c99 -Wall -Werror -Wpedantic -Wextra
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_CHARS 1024
const int NUM_WORDS = 10;

typedef struct
{
  int len;
  char str[MAX_CHARS];
} word_t;

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
  word_t longest_words[NUM_WORDS];
  memset (longest_words, 0, sizeof (longest_words));

  char buf[MAX_CHARS];
  while (fgets (buf, sizeof (buf), fp) != NULL)
    {
      int len = strlen (buf);
      for (int i = 0; i < NUM_WORDS; ++i)
        {
          if (longest_words[i].len < len)
            {
              memcpy (longest_words[i].str, buf, len);
              /* store string length; prevent calling strlen() multiple times */
              longest_words[i].len = len;
              /* tradeoff: or save space; and call strlen() multiple times */
              break;
            }
        }
      /* pedantic */
      memset (buf, 0, MAX_CHARS);
    }

  for (int i = 0; i < NUM_WORDS; ++i)
    {
      fprintf (stdout, "%s", longest_words[i].str);
    }

  return EXIT_SUCCESS;
}
