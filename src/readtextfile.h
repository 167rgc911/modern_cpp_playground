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

std::map<std::string, int>
split (std::vector<std::string> &s, const char delim, int &retval)
{
  retval = 0;

  std::map<std::string, int> ov{};

  for (std::string l : s)
    {
      std::istringstream ss_ (l);
      for (std::string w; std::getline (ss_, w, delim);)
        {
          ov.emplace (std::make_pair (w, 0));
        }
    }
  /* std::cout << ov.size() << '\n'; */

  return ov;
}

std::vector<std::string>
split (std::string &s, const char delim, int &retval)
{
  retval = 0;

  std::vector<std::string> ov{};

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
        return std::ispunct (c) or not(std::isalnum (c) or std::isspace (c));
      };

      // sanitize
      auto [srf, srl] = std::ranges::remove_if (s, pl_sanitize);
      s.erase (srf, srl);
      if (s.empty ())
        {
          retval = 1;
          return {};
        }

      // normalize to all ASCII lowercase
      std::transform (s.begin (), s.end (), s.begin (),
                      [] (unsigned char c) { return std::tolower (c); });

      return split (s, '\n', retval);
    }

  retval = 1;
  return {};
}

std::vector<std::string>
read_text_file (const std::string &f, int &retval)
{
  retval = 0;

  std::vector<std::string> ov{};

  // possible issue with LARGE files
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
