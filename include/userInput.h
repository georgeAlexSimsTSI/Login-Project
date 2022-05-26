#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <limits>
using std::cin;
using std::cout;
using std::endl;
using std::string;
using std::vector;

/**
 * @brief useful methods for command line inputs
 */
namespace userInput
{
  template <typename T> // this is in the header file as according to stack overflow it must be visible to a translation unit
  T &validateInput(T &val, const string &prompt)
  {
    while (true)
    {
      cout << prompt;
      if (cin >> val)
        break;
      else
      {
        cout << "Enter a valid input" << endl;
        cin.clear();
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
      }
    }
    cin.clear();
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    return val;
  }
};

#endif