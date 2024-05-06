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
 *         Author:  rgc (), sessyargc.jp@gmail.com
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

std::string
read_file (const std::string &f)
{
  // possible issue with LARGE files
  std::ifstream ifs_{ f, std::ios::ate };
  if (ifs_.is_open ())
    {
      auto sz_ = ifs_.tellg ();
      ifs_.seekg (0, std::ios::beg);
      /* std::cout << '\t' << sz_ << '\n'; */

      std::string s_ (sz_, '\0');
      ifs_.read (&s_[0], sz_);

      return s_;
    }
  else
    {
      std::cout << " XXX ifs_.is_open()" << f << '\n';
    }

  ifs_.close ();

  return {};
}

std::vector<std::string>
read_string_lines2 (std::string &s, int &retval)
{
  retval = 0;

  if (not s.empty ())
    {
      auto pl_sanitize = [] (unsigned char c) {
        return std::ispunct (c) or c == '\t' or c == '\r';
      };

      // sanitize
      auto [srf, srl] = std::ranges::remove_if (s, pl_sanitize);
      s.erase (srf, srl);
      if (s.empty ())
        {
          retval = 1;
          return {};
        }

      // normalize to all ASCII lowercase
      std::transform (s.begin (), s.end (), s.begin (),
                      [] (unsigned char c) { return std::tolower (c); });

      return split (s, '\n', retval);
    }
  retval = 1;
  return {};
}

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

int
test_ranges2 (std::string test_string0)
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
      auto [srf, srl] = std::ranges::unique (ll.begin (), ll.end ());
      ll.erase (srf, srl);

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
BM_test_ranges2 (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_ranges2 (test_string0);
}

BENCHMARK (BM_test_ranges2);

static void
BM_bigdata_test1 (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test (test_string0);
}

BENCHMARK (BM_bigdata_test1);

static void
BM_bigdata_test2 (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_ranges (test_string0);
}

BENCHMARK (BM_bigdata_test2);

static void
BM_bigdata_test3 (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_ranges2 (test_string0);
}

BENCHMARK (BM_bigdata_test3);

int
test_hash_ranges (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {
      std::map<std::string, int> ll = split (lines_, ' ', retval);
      auto f = [] (std::pair<const std::string, int> &s1,
                   std::pair<const std::string, int> &s2) {
        return s1.first.length () < s2.first.length ();
      };

      // get the longest element
      auto m = std::max_element (ll.begin (), ll.end (), f);
      if (m != ll.end ())
        {
          auto lw_sz = m->first.length ();
          // get a view that contains strings with max length
          auto lw_vw = std::views::filter (
              ll, [lw_sz] (std::pair<std::string, int> h) {
                return h.first.length () == lw_sz;
              });
        }
    }

  return retval;
}

static void
BM_test_hash_ranges (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_hash_ranges (test_string0);
}

BENCHMARK (BM_test_hash_ranges);

static void
BM_bigdata_hash_ranges (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_hash_ranges (test_string0);
}

BENCHMARK (BM_bigdata_hash_ranges);

int
test_hash_ranges2 (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {
      std::unordered_map<std::string, int> ll = split_u (lines_, ' ', retval);
      auto f = [] (std::pair<const std::string, int> &s1,
                   std::pair<const std::string, int> &s2) {
        return s1.first.length () < s2.first.length ();
      };

      // get the longest element
      auto m = std::max_element (ll.begin (), ll.end (), f);
      if (m != ll.end ())
        {
          auto lw_sz = m->first.length ();
          // get a view that contains strings with max length
          auto lw_vw = std::views::filter (
              ll, [lw_sz] (std::pair<std::string, int> h) {
                return h.first.length () == lw_sz;
              });
        }
    }

  return retval;
}

static void
BM_test_hash_ranges2 (benchmark::State &state)
{
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  for (auto _ : state)
    test_hash_ranges2 (test_string0);
}

BENCHMARK (BM_test_hash_ranges2);

static void
BM_bigdata_hash_ranges2 (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_hash_ranges2 (test_string0);
}

BENCHMARK (BM_bigdata_hash_ranges2);

int
test_read_string_lines (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines (test_string0, retval);
  if (not lines_.empty())
    {
    }

  return retval;
}

static void
BM_read_string_lines (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_read_string_lines (test_string0);
}

BENCHMARK (BM_read_string_lines);

int
test_read_string_lines2 (std::string test_string0)
{
  int retval = 0;

  auto lines_ = read_string_lines2 (test_string0, retval);
  if (not lines_.empty())
    {
    }

  return retval;
}

static void
BM_read_string_lines2 (benchmark::State &state)
{
  std::string test_string0 = read_file ("pg28233.txt");
  for (auto _ : state)
    test_read_string_lines2 (test_string0);
}

BENCHMARK (BM_read_string_lines2);

BENCHMARK_MAIN ();
