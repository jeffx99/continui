#include <iostream>
#include <string>
#include "assert.hpp"
#include "../src/music_input.hpp"

template <typename T>
void read_arbitrary_object(std::string name)
{
  T object;

  std::cout << "Enter " << name << ": ";
  std::cin >> object;

  std::cout << "Echoing: " << object << std::endl;
}

int main(int argc, char **argv)
{
  read_arbitrary_object<rational>("rational");
  read_arbitrary_object<Pitch>("pitch");
  read_arbitrary_object<Note>("note");
  return 0;
}
