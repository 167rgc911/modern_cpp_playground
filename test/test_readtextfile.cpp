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

#include "readtextfile.h"

int
main (void)
{
  int retval = 0;

  /* const auto csv_text_ = read_csv_file ("files/colrowhdr.csv", retval); */
  std::string test_string0
      = R"(Hello. $100 as-is, distributin'? Government governin.
One of them is muchmuchmuch bigger than the other)";
  std::cout << test_string0 << '\n';

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
      ll.push_back (*me);
      std::cout << *me << '\n';
    }

  auto m = std::max_element (ll.begin (), ll.end (),
                             [] (std::string &s1, std::string &s2) {
                               return s1.length () < s2.length ();
                             });
  std::cout << "longest word: " << *m << '\n';

  return retval;
}
