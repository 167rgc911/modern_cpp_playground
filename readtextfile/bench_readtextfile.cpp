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
#include <ranges>

#include "LoremIpsumGenerator.hpp"
#include "benchmark/benchmark.h"
#include "readtextfile.h"

int
test (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {
      std::vector<std::string> ll;
      for (auto &line : lines_)
        {
          auto r_ = split (line, ' ', retval);
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

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {

      std::vector<std::string> ll;
      auto f = [] (std::string &s1, std::string &s2) {
        return s1.length () < s2.length ();
      };
      for (auto &line : lines_)
        {
          auto r_ = split (line, ' ', retval);
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

int
test_ranges (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {
      std::vector<std::string> ll{};

      auto f = [] (std::string &s1, std::string &s2) {
        return s1.length () < s2.length ();
      };
      for (auto &line : lines_)
        {
          auto r_ = split (line, ' ', retval);
          auto me = std::max_element (r_.begin (), r_.end (), f);
          if (me != r_.end ())
            {
              ll.push_back (*me);
            }
        }

      // remove dupes
      ll.erase (std::unique (ll.begin (), ll.end ()), ll.end ());

      // get the longest element
      auto m = std::max_element (ll.begin (), ll.end (), f);
      if (m != ll.end ())
        {
          auto lw_sz = m->length ();
          // get a view that contains strings with max length
          auto lw_vw = std::views::filter (
              ll, [lw_sz] (std::string s) { return s.length () == lw_sz; });
        }
    }

  return retval;
}

static void
BM_test_ranges (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_ranges (test_string0);
}

BENCHMARK (BM_test_ranges);

BENCHMARK_MAIN ();
