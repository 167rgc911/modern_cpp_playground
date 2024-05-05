/*
 * =====================================================================================
 *
 *       Filename:  fuzz_map_readtextfile.cpp
 *
 *    Description:  
 *
 *        Version:  1.0
 *        Created:  05/05/24 20:22:58
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (), sessyargc.jp@gmail.com
 *   Organization:  
 *
 * SPDX-License-Identifier: MIT
 * =====================================================================================
 */

#include <algorithm>
#include <fstream>
#include <future>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "readtextfile_tomap.h"

extern "C" int
LLVMFuzzerTestOneInput (const uint8_t *Data, size_t Size)
{
  int retval = 0;
  std::string s (reinterpret_cast<const char *> (Data), Size);
  std::vector<std::string> lines_ = read_string_lines (s, retval);
  std::map<std::string, int> ll = split (lines_, ' ', retval);
  return retval; // Values other than 0 and -1 are reserved for future use.
}
