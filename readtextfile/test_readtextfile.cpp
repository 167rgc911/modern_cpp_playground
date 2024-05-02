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

  // generate text
  auto test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {

      std::vector<std::string> ll {};
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
              std::cout << *me << '\n';
            }
        }

      auto m = std::max_element (ll.begin (), ll.end (), f);
      // does not account for other words
      if (m != ll.end ())
        {
          std::cout << "longest word: " << *m << '\n';
        }
    }

  return retval;
}
