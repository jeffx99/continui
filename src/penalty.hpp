/* penalty.hpp */
#pragma once
#include "music.hpp"

using Harmony = std::vector<Note>;
using PenaltyType = float (const Harmony*, const FiguredBass*, Mode);

struct Penalty
{
  int arity; /* number of harmonies considered */
  float weight;

  PenaltyType type;
};

namespace penalties
{
  /* ARITY 1 */

  /* omissions */
  PenaltyType third_omission_penalty;
  PenaltyType seventh_omission_penalty;
  PenaltyType dissonant_omission_penalty;

  /* doublings */
  PenaltyType third_doubling_penalty;
  PenaltyType seventh_doubling_penalty;

  /* ARITY 2 */
  PenaltyType motion_penalty;
  PenaltyType melodic_penalty;
  PenaltyType tendency_penalty;
}
