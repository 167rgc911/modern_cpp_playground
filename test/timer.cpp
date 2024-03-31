/*
 * =====================================================================================
 *
 *       Filename:  timer.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/28/24 19:16:36
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include "timer.h"

int
main (void)
{
  timer t;
  t.nt ();
  t.st ("a");
  t.st ("b");
  t.st ("c");
  t.st ("d");
  t.st ("e");
  t.st ("f");
  t.st ("g");
  t.st ("h");
  t.st ("i");
  t.st ("j");
  t.st ("k");
  t.st ("l");
  t.st ("m");
  t.st ("n");
  t.st ("o");
  t.st ("p");
  t.st ("q");
  t.st ("r");
  t.st ("s");
  t.st ("t");
  t.st ("kilobytes");
  t.st ("Bjarne Stroustrup");
  t.st ("Herb Sutter");
  t.pr ();
}
