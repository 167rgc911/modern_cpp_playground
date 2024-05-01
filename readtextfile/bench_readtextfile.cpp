/*
 * =====================================================================================
 *
 *       Filename:  bench_readtextfile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/30/24 08:03:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <iostream>

#include "LoremIpsumGenerator.hpp"
#include "benchmark/benchmark.h"
#include "readtextfile.h"

int
test (std::string test_string0)
{
  int retval = 0;

  auto input_ = read_string_lines (test_string0, retval);
  std::vector<std::string> lines_;

  try
    {
      lines_ = input_.value ();
    }
  catch (const std::bad_optional_access &e)
    {
      std::cout << e.what () << '\n';
    }

  if (not lines_.empty ())
    {
      std::vector<std::string> ll;
      for (auto &line : lines_)
        {
          auto split_r_ = split (line, ' ', retval);
          auto r_ = split_r_.value ();
          auto me = std::max_element (r_.begin (), r_.end (),
                                      [] (std::string &s1, std::string &s2) {
                                        return s1.length () < s2.length ();
                                      });
          if (me != r_.end ())
            {
              ll.push_back (*me);
              // longest word for each input line
            }
        }

      auto m = std::max_element (ll.begin (), ll.end (),
                                 [] (std::string &s1, std::string &s2) {
                                   return s1.length () < s2.length ();
                                 });
    }

  return retval;
}

static void
BM_test (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test (test_string0);
}

BENCHMARK (BM_test);

int
test_lambda (std::string test_string0)
{
  int retval = 0;

  auto input_ = read_string_lines (test_string0, retval);
  std::vector<std::string> lines_;

  try
    {
      lines_ = input_.value ();
    }
  catch (const std::bad_optional_access &e)
    {
      std::cout << e.what () << '\n';
    }

  if (not lines_.empty ())
    {

      std::vector<std::string> ll;
      auto f = [] (std::string &s1, std::string &s2) {
        return s1.length () < s2.length ();
      };
      for (auto &line : lines_)
        {
          auto split_r_ = split (line, ' ', retval);
          auto r_ = split_r_.value ();
          auto me = std::max_element (r_.begin (), r_.end (), f);
          if (me != r_.end ())
            {
              ll.push_back (*me);
              // longest word for each input line
            }
        }

      auto m = std::max_element (ll.begin (), ll.end (), f);
    }

  return retval;
}

static void
BM_test_lambda (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_lambda (test_string0);
}

BENCHMARK (BM_test_lambda);

BENCHMARK_MAIN ();
