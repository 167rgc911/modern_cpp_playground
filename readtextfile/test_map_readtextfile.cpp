/*
 * =====================================================================================
 *
 *       Filename:  test_map_readtextfile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/05/24 09:26:46
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <memory>
#include <ranges>
#include <string>
#include <vector>

#include "LoremIpsumGenerator.hpp"

#include "readtextfile_tomap.h"

int
main (void)
{
  int retval = 0;

  // generate text; 24 doesn't mean 24 lines with '\n'
  auto test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);

  auto lines_ = read_string_lines (test_string0, retval);

  if (not lines_.empty ())
    {

      std::map<std::string, int> ll = split (lines_, ' ', retval);
      auto f = [] (std::pair<const std::string, int> &s1,
                   std::pair<const std::string, int> &s2) {
        return s1.first.length () < s2.first.length ();
      };

      // remove dupes
      // not needed std::map should be unique

      auto m = std::max_element (ll.begin (), ll.end (), f);
      // does not account for other words with the same max length
      if (m != ll.end ())
        {
          auto lw_sz = m->first.length ();
          // get a view that contains strings with max length
          auto lw_vw = std::views::filter (
              ll, [lw_sz] (std::pair<std::string, int> h) {
                return h.first.length () == lw_sz;
              });
          for (auto lw : lw_vw)
            {
              std::cout << lw.first << '\n';
            }

        }
    }

  return retval;
}
