/*
 * =====================================================================================
 *
 *       Filename:  test_readtextfile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  04/27/24 18:13:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <algorithm>
#include <fstream>
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

  // generate text; 24 doesn't mean 24 lines with '\n'
  auto test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);

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

      auto m = std::max_element (ll.begin (), ll.end (), f);
      // does not account for other words with the same max length
      if (m != ll.end ())
        {
          std::cout << "longest word: " << *m << '\n';
        }
    }

  return retval;
}
