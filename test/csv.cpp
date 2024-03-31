/*
 * =====================================================================================
 *
 *       Filename:  csv.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/16/24 08:18:19
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
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

#include "csv.h"

int
main (void)
{
  int retval = 0;

  const auto csv_text_ = read_csv_file ("files/colrowhdr.csv", retval);
  for (const auto &line : csv_text_)
    {
      /* std::cout << line << '\n' << '\n'; */
      auto r_ = split (line, ',', retval);
      std::for_each (r_.begin (), r_.end (), [] (const std::string &col) {
        std::cout << col << ", ";
      });
      std::cout << '\n';
    }

  return retval;
}
