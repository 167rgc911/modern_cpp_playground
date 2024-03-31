/*
 * =====================================================================================
 *
 *       Filename:  search3.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/25/24 17:18:05
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "csv.h"

int
main (void)
{
  int retval{ 0 };

  const std::vector<std::map<std::string, std::string>> vmss{
    { { "line", "1" }, { "one", "1" }, { "two", "2" } },
    { { "line", "2" }, { "one", "1" }, { "two", "2" } },
    { { "line", "3" }, { "one", "1" }, { "two", "2" } }
  };

  const std::vector<std::map<std::string, std::string>> match_items{
    {
        { "line", "1" },
    },
  };

  for (const auto m : match_items)
    {
      std::cout << "match_items: ";
      auto r = map_contains (vmss, m, retval);
      std::cout << retval << '\n';
      retval = !retval;
    }

  return retval;
}
