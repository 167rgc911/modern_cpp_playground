/*
 * =====================================================================================
 *
 *       Filename:  csv.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/16/24 08:06:29
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
#include <optional>
#include <sstream>
#include <string>
#include <vector>

std::vector<std::string>
split (std::string &s, const char delim, int &retval)
{
  retval = 0;

  std::vector<std::string> ov;

  std::istringstream ss_ (s);
  for (std::string l; std::getline (ss_, l, delim);)
    {
      ov.push_back (l);
    }
  /* std::cout << ov.size() << '\n'; */

  return ov;
}

std::vector<std::string>
read_string_lines (std::string &s, int &retval)
{
  retval = 0;

  if (not s.empty ())
    {
      auto pl_sanitize = [] (unsigned char c) {
        return (c > 255) or std::ispunct (c)
               or not(std::isalnum (c) or std::isspace (c));
      };

      // sanitize
      s.erase (std::remove_if (s.begin (), s.end (), pl_sanitize), s.end ());
      if (s.empty ())
        {
          retval = 1;
          return {};
        }

      return split (s, '\n', retval);
    }

  retval = 1;
  return {};
}

std::vector<std::string>
read_text_file (const std::string &f, int &retval)
{
  retval = 0;

  std::vector<std::string> ov;

  std::ifstream ifs_{ f, std::ios::ate };
  if (ifs_.is_open ())
    {
      auto sz_ = ifs_.tellg ();
      ifs_.seekg (0, std::ios::beg);
      /* std::cout << '\t' << sz_ << '\n'; */

      std::string s_ (sz_, '\0');
      ifs_.read (&s_[0], sz_);

      ov = read_string_lines (s_, retval);
    }
  else
    {
      std::cout << " XXX ifs_.is_open()" << f << '\n';
      retval = 1;
    }

  ifs_.close ();

  return ov;
}
