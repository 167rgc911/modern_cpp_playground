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

  // sanitize
  test_string0.erase (
      std::remove_if (test_string0.begin (), test_string0.end (),
                      [] (unsigned char c) { return std::ispunct (c); }),
      test_string0.end ());

  // input text file -> std::vector
  // can be n .. n + x lines
  const auto csv_text_ = read_csv_string (test_string0, retval);

  std::vector<std::string> ll;
  for (const auto &line : csv_text_)
    {
      auto r_ = split (line, ' ', retval);
      auto me = std::max_element (r_.begin (), r_.end (),
                                  [] (std::string &s1, std::string &s2) {
                                    return s1.length () < s2.length ();
                                  });
      if (me != r_.end ())
        {
          ll.push_back (*me);
        }
    }

  auto m = std::max_element (ll.begin (), ll.end (),
                             [] (std::string &s1, std::string &s2) {
                               return s1.length () < s2.length ();
                             });
  return 0;
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
test_wos (std::string test_string0)
{
  int retval = 0;

  // input text file -> std::vector
  // can be n .. n + x lines
  const auto csv_text_ = read_csv_string (test_string0, retval);

  std::vector<std::string> ll;
  for (const auto &line : csv_text_)
    {
      auto r_ = split (line, ' ', retval);
      auto me = std::max_element (r_.begin (), r_.end (),
                                  [] (std::string &s1, std::string &s2) {
                                    return s1.length () < s2.length ();
                                  });
      if (me != r_.end ())
        {
          ll.push_back (*me);
        }
    }

  auto m = std::max_element (ll.begin (), ll.end (),
                             [] (std::string &s1, std::string &s2) {
                               return s1.length () < s2.length ();
                             });
  return 0;
}

static void
BM_test_wos (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_wos (test_string0);
}

BENCHMARK (BM_test_wos);

BENCHMARK_MAIN ();
