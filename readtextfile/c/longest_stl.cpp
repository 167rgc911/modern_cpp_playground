// =====================================================================================
//
//       Filename:  longest.cpp
//
//    Description:
//
//        Version:  1.0
//        Created:  05/14/24 04:45:58
//       Revision:  none
//       Compiler:  g++
//
//         Author:  rgc (), sessyargc.jp@gmail.com
//   Organization:
//
// =====================================================================================

#include <array>
#include <fstream>
#include <iostream>
#include <string>

const int NUM_WORDS = 10;

int
main (int argc, char *argv[])
{
  if (argc < 2)
    {
      std::cerr << "Usage: " << argv[0] << " wordlist.txt\n";
      return EXIT_FAILURE;
    }

  std::ifstream ifs_ { argv[1] };
  if (ifs_.is_open ())
    {
      std::array<std::string, NUM_WORDS> longest_words;

      while (!ifs_.eof())
        {
          std::string buf;
          ifs_ >> buf;
          for (auto & word : longest_words) 
            {
              if (word.length() < buf.length())
                {
                  word = buf;
                  break;
                }
            }
        }

      for (auto word : longest_words)
        {
          std::cout << word << '\n';
        }

      ifs_.close ();
    }
  else
    {
      std::cout << " XXX ifs_.is_open() " << argv[1] << '\n';
    }

  return EXIT_SUCCESS;
}
