/*
 * =====================================================================================
 *
 *       Filename:  test_future_readtextfile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/01/24 06:15:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * =====================================================================================
 */

#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "LoremIpsumGenerator.hpp"

#include "readtextfile.h"

std::vector<std::string>
get_lines(int &retval)
{
  retval = 0;
  // generate text; note that not all 24 lines/rows end with '\n'
  auto test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);
  return read_string_lines (test_string0, retval);
}

int
main (void)
{
  int retval = 0;

  std::future<std::vector<std::string>> lines_
      = std::async (std::launch::async, [&] () {
          return get_lines (retval);
        });

  std::vector<std::string> ll;
  auto f = [] (std::string &s1, std::string &s2) {
    return s1.length () < s2.length ();
  };
  for (auto &line : lines_.get ())
    {
      auto r_ = split (line, ' ', retval);
      auto me = std::max_element (r_.begin (), r_.end (), f);
      if (me != r_.end ())
        {
          ll.push_back (*me);
        }
    }

  // sort and remove dupes
  std::sort (ll.begin (), ll.end ());
  ll.erase (std::unique (ll.begin (), ll.end ()), ll.end ());

  auto m = std::max_element (ll.begin (), ll.end (), f);
  // does not account for other words with the same max length
  if (m != ll.end ())
    {
      std::cout << "longest word: " << *m << '\n';
    }

  return retval;
}
