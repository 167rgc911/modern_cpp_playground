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
 *         Author:  rgc (), sessyargc.jp@gmail.com
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "LoremIpsumGenerator.hpp"

#include "readtextfile.h"

std::vector<std::string>
get_lines (int &retval)
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

  const auto lines_ = get_lines (retval);

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
          for (auto lw : lw_vw)
            {
              std::cout << lw << '\n';
            }
        }
    }

  return retval;
}
