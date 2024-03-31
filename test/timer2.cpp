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
  timer2 t;
  t.nt ();
  t.rs (128);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.st (__LINE__);
  t.pr ();
  t.prn ();
}
