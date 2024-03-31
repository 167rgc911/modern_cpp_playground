/*
 * =====================================================================================
 *
 *       Filename:  aa.h
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/08/24 21:00:08
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#pragma once
#ifndef AA_H
#define AA_H

#include <iostream>
#include <map>
#include <string>

template <typename K, typename V> class AA
{
  typedef std::map<K, V> aa;
  typedef std::pair<K, V> p_aa;

  aa aa_;
  std::string param0_;
  std::string param1_;

public:
  AA (const p_aa &p) : param0_ (p.first), param1_ (p.second)
  {
    aa_.insert ({ "param0", p.first });
    aa_.insert ({ "param1", p.second });
  }

  AA (const V &p0, const V &p1) : param0_ (p0), param1_ (p1)
  {
    aa_.insert ({ "param0", p0 });
    aa_.insert ({ "param1", p1 });
  }

  const V &
  operator[] (const K &p) const
  {
    return aa_.at (p);
    /* if (! aa_.empty()) */
    /* { */
    /*     auto s = aa_.find(p); */
    /*     if (s != aa_.end()) */
    /*     { */
    /*         return s->second; */
    /*     } */
    /* } */
    /* return {}; */
  }

  bool
  operator== (const AA &other) const
  {
    return aa_ == other.aa_;
  }

  /* getters */
  const V &
  param0 () const
  {
    return param0_;
  };
  const V &
  param1 () const
  {
    return param1_;
  };

  void
  print (const std::string comment)
  {
    std::cout << comment << "{";
    for (auto &pair : aa_)
      std::cout << "{" << pair.first << ": " << pair.second << "}";
    std::cout << "}\n";
  };
};

#endif
