/*
 * =====================================================================================
 *
 *       Filename:  fuzz_readtextfile.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  05/01/24 06:05:37
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (),
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

#include "readtextfile.h"

extern "C" int
LLVMFuzzerTestOneInput (const uint8_t *Data, size_t Size)
{
  int retval = 0;
  std::string s (reinterpret_cast<const char *> (Data), Size);
  std::vector<std::string> discarded = read_string_lines (s, retval);
  return retval; // Values other than 0 and -1 are reserved for future use.
}
