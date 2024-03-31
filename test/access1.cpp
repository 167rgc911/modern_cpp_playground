/*
 * =====================================================================================
 *
 *       Filename:  access1.cpp
 *
 *    Description:
 *
 *        Version:  1.0
 *        Created:  03/08/24 21:31:25
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  rgc (rgc), sessyargc.jp@gmail.com
 *   Organization:
 *
 * =====================================================================================
 */

#include <iostream>

#include "aa.h"

int
main (void)
{
  auto aa = AA<std::string, std::string>{ "p0", "p1" };
  aa.print ("init aa ");

  auto s1 = aa["param0"];
  std::cout << "\n" << s1 << "\n";
  if (s1 == "p0")
    {
      aa.print ("operator[param0] ");
    }

  auto s2 = aa["param1"];
  std::cout << "\n" << s2 << "\n";
  if (s2 == "p1")
    {
      aa.print ("operator[param1] ");
    }

  return 0;
}
