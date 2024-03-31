/*
 * =====================================================================================
 *
 *       Filename:  timer_benchmark.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/31/24 05:47:42
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include "benchmark/benchmark.h"

#include "timer.h"

std::ostream &
operator<< (std::ostream &os, const timer2 &t)
{
  t.pr ();
  return os;
}

int
test (void)
{
  timer2 d2;
  std::pair<uint64_t, std::chrono::high_resolution_clock::time_point> p{};
  d2.rs (128);
  d2.st (__LINE__);
  p = std::make_pair (0, std::chrono::high_resolution_clock::now ());
  d2.st (__LINE__);
  p = std::make_pair (1, std::chrono::high_resolution_clock::now ());
  d2.st (__LINE__);
  p = std::make_pair (2, std::chrono::high_resolution_clock::now ());
  d2.st (__LINE__);
  p = std::make_pair (3, std::chrono::high_resolution_clock::now ());
  d2.st (__LINE__);
  p = std::make_pair (4, std::chrono::high_resolution_clock::now ());
  d2.st (__LINE__);
  std::cout << d2;

  return 0;
}

static void
BM_test (benchmark::State &state)
{
  for (auto _ : state)
    test ();
}

BENCHMARK (BM_test);
BENCHMARK_MAIN ();
