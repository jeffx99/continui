/* penalty.hpp */
#pragma once
#include "music.hpp"

using Harmony = std::vector<Pitch>;

struct Penalty {
  int arity;
  float (*method) (const Chord*, Mode);
};

struct Rule
{
  const Penalty* penalty;

  float weight;
  float exponent;
};

namespace penalties
{

  extern const int foo;

  /* ARITY 1 */
  /* omissions */
  extern const Penalty third_omission_penalty;
  extern const Penalty seventh_omission_penalty;
  extern const Penalty dissonant_omission_penalty;

  /* doublings */
  extern const Penalty third_doubling_penalty;
  extern const Penalty seventh_doubling_penalty;

  /* ARITY 2 */
  extern const Penalty motion_penalty;
  extern const Penalty melodic_penalty;
  extern const Penalty tendency_penalty;
}
