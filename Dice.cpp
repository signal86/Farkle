#include <iostream>
#include <cctype>
#include <algorithm>
#include <cstdlib>
#ifdef _WIN32
#include <Windows.h>
#else
#include <unistd.h>
#endif

using std::string;

class Dice {
  
  public:

    int holding;
    bool active = true;

    int roll() {
      holding = rand() % 6 + 1;
      return holding;
    }


};