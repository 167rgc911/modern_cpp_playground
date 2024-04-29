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
  std::string test_string0 = lorem_ipsum::generate_lorem_ipsum_lines (24);

  // sanitize
  test_string0.erase (
      std::remove_if (test_string0.begin (), test_string0.end (),
                      [] (unsigned char c) { return std::ispunct (c); }),
      test_string0.end ());
  std::cout << test_string0 << '\n';

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
          // longest word for each input line
          std::cout << *me << '\n';
        }
    }

  auto m = std::max_element (ll.begin (), ll.end (),
                             [] (std::string &s1, std::string &s2) {
                               return s1.length () < s2.length ();
                             });
  std::cout << "longest word: " << *m << '\n';

  return retval;
}
