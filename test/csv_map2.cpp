/*
 * =====================================================================================
 *
 *       Filename:  csv_map2.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/17/24 06:02:44
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
#include <memory>
#include <string>
#include <vector>

#include "csv.h"

int
main (void)
{
  int retval = 0;

  std::vector<std::pair<std::map<std::string, std::string>,
                        std::map<std::string, std::string>>>
      vpm_;

  const auto ndx = std::vector<unsigned long int>{ 0, 1 };

  const auto csv_text_ = read_csv_file ("files/colrowhdr.csv", retval);
  const auto k_ = split (csv_text_.front (), ',', retval);
  const auto ik_ = construct_index (k_, ndx, retval);

  for (unsigned long int i = 1; i < csv_text_.size (); ++i)
    {
      const auto v_ = split (csv_text_.at (i), ',', retval);
      const auto iv_ = construct_index (v_, ndx, retval);

      const auto i_ = construct_map (ik_, iv_, retval);
      const auto m_ = construct_map (k_, v_, retval);

      /* std::for_each(i_.begin(), i_.end(), */
      /*         [](const std::pair<std::string, std::string>& p_) */
      /*             { std::cout << "index \t" << p_.first << '\t' << p_.second
       * << '\n'; }); */
      /* std::for_each(m_.begin(), m_.end(), */
      /*         [](const std::pair<std::string, std::string>& p_) */
      /*             { std::cout << "row \t" << p_.first << '\t' << p_.second
       * << '\n'; }); */

      vpm_.emplace_back (std::make_pair (i_, m_));
    }

  std::for_each (vpm_.begin (), vpm_.end (),
                 [] (const std::pair<std::map<std::string, std::string>,
                                     std::map<std::string, std::string>> &p_) {
                   auto f_ = p_.first;
                   auto s_ = p_.second;
                   std::cout << "index \t";
                   /* std::for_each(f_.begin(), f_.end(), */
                   /*         [](const std::pair<std::string, std::string>&
                    * pf_) */
                   /*             { std::cout << " " << pf_.first << ": " <<
                    * pf_.second; }); */
                   print_pair<std::map<std::string, std::string>,
                              std::pair<std::string, std::string>> (f_);
                   std::cout << " row \t";
                   /* std::for_each(s_.begin(), s_.end(), */
                   /*         [](const std::pair<std::string, std::string>&
                    * ps_) */
                   /*             { std::cout << " " << ps_.first << ": " <<
                    * ps_.second; }); */
                   print_pair<std::map<std::string, std::string>,
                              std::pair<std::string, std::string>> (s_);
                   std::cout << '\n';
                 });

  return retval;
}
