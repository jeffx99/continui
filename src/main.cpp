/* main.cpp */
#include <vector>
#include <iostream>
#include "continuo.hpp"
#include "penalty.hpp"

int main(int argc, char** argv)
{
  std::vector<FiguredBass> bassline =
  {
    {{1, 2}, {{8}, {5}, {3}}},
    {{7, 1}, {{6}, {3}}},
    {{6, 1}, {{6}, {4}, {3}}},
    {{5, 1}, {{7}, {5}, {3}}},
    {{1, 1}, {{8}, {5}, {3}}}
  };

  /* tenor, alto, soprano */
  std::vector<std::pair<Note, Note>> ranges =
  {
    {{1, 1}, {5, 2}},
    {{5, 1}, {1, 3}},
    {{1, 2}, {5, 3}}
  };

  Realization continuo(3, ranges, bassline);
  continuo.penalties.push_back({2, 0.5, penalties::melodic_penalty});
  continuo.penalties.push_back({1, 3, penalties::omission_penalty});
  continuo.penalties.push_back({1, 2, penalties::doubling_penalty});

  std::cout << "badness: " << continuo.realize(3) << std::endl;

  std::cout << "realization:" << std::endl;
  for (int i = 2; i >= 0; i--)
  {
    for (int j = 0; j < bassline.size(); j++)
      std::cout << continuo.get_note(i, j).degree << "." << continuo.get_note(i, j).octave << " ";

    std:: cout << std::endl;
  }
}
