/*
 * =====================================================================================
 *
 *       Filename:  exception_at_pos.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/25/24 18:26:58
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
    { { "line", "4" }, { "one", "1" }, { "two", "2" } },
  };

  auto r = map_at_pos (vmss, 99, retval);
  retval = !retval;

  return retval;
}
