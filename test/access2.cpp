/*
 * =====================================================================================
 *
 *       Filename:  access2.cpp
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
  aa.print ("init ");

  auto s2 = aa.param1 ();
  std::cout << "\n" << s2 << "\n";
  aa.print ("member param1 ");

  auto s3 = aa.param0 ();
  std::cout << "\n" << s3 << "\n";
  ;
  aa.print ("member param0 ");

  return 0;
}
