/*
 * =====================================================================================
 *
 *       Filename:  timer2_1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/29/24 19:29:42
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
  timer2 d0;
  d0.rs (128);
  d0.st (__LINE__);
  d0.dummy0 ();
  d0.st (__LINE__);
  d0.pru ();

  timer2 d1;
  d1.rs (128);
  d1.st (__LINE__);
  d1.dummy1 ();
  d1.st (__LINE__);
  d1.pru ();
}
