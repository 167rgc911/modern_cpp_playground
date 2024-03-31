/*
 * =====================================================================================
 *
 *       Filename:  csv_map.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/16/24 10:00:19
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
#include <map>
#include <string>
#include <vector>

#include "csv.h"

int
main (void)
{
  int retval = 0;

  const auto csv_text_ = read_csv_file ("files/colrowhdr.csv", retval);
  const auto k_ = split (csv_text_.front (), ',', retval);
  const auto v_ = split (csv_text_.back (), ',', retval);

#if 0
    std::vector<std::pair<std::string, std::string>> vp_;
    vp_.reserve(k_.size());
    std::transform(k_.begin(), k_.end(), v_.begin(), std::back_inserter(vp_),
            [](std::string k, std::string v)
                { return std::make_pair(k, v); });

    std::map<std::string, std::string> m_;
    for (auto& p_ : vp_)
    {
        /* m_[p_.first] = p_.second; */
        m_.insert(p_);
    }

    /* for (const auto& p_ : m_) */
    /* { */
    /*     std::cout << '\t' << p_.first << '\t' << p_.second << '\n'; */
    /* } */
#else
  const auto m_ = construct_map (k_, v_, retval);
#endif

  std::for_each (m_.begin (), m_.end (),
                 [] (const std::pair<std::string, std::string> &p_) {
                   std::cout << '\t' << p_.first << '\t' << p_.second << '\n';
                 });

  return retval;
}
