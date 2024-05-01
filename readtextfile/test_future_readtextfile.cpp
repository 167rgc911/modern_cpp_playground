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

int
main (void)
{
  int retval = 0;

  // generate text
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);

  std::future<std::vector<std::string> > lines_
      = std::async (std::launch::async, [&] () {
          return read_string_lines (test_string0, retval);
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
          // longest word for each input line
          std::cout << *me << '\n';
        }
    }

  auto m = std::max_element (ll.begin (), ll.end (), f);
  // does not account for other words
  if (m != ll.end ())
    {
      std::cout << "longest word: " << *m << '\n';
    }

  return retval;
}
