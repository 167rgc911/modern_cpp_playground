/*
 * =====================================================================================
 *
 *       Filename:  timer3_1.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  03/30/24 07:20:55
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:  
 *
 * =====================================================================================
 */

#include <iostream>

#include "timer.h"

std::ostream &operator<<(std::ostream &os, const timer3 &t)
{
  t.pr();
  return os;
}

std::ostream &operator<<(std::ostream &os, const timer2 &t)
{
  t.pr();
  return os;
}

int
main (void)
{
  {
  timer3 d0;
  d0.rs (128);
  d0.st (__LINE__);
  d0.st (__LINE__);
  std::cout << d0;

  timer3 d1;
  d1.rs (128);
  d1.st (__LINE__);
  d1.st (__LINE__);
  std::cout << d1;
  }

  timer2 d2;
  std::pair<uint64_t, std::chrono::high_resolution_clock::time_point> p {};
  d2.rs (128);
  d2.st (__LINE__);
  p = std::make_pair(0, std::chrono::high_resolution_clock::now());
  d2.st (__LINE__);
  p = std::make_pair(1, std::chrono::high_resolution_clock::now());
  d2.st (__LINE__);
  p = std::make_pair(2, std::chrono::high_resolution_clock::now());
  d2.st (__LINE__);
  p = std::make_pair(3, std::chrono::high_resolution_clock::now());
  d2.st (__LINE__);
  p = std::make_pair(4, std::chrono::high_resolution_clock::now());
  d2.st (__LINE__);
  std::cout << d2;
}
