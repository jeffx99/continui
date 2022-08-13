/* penalty.hpp */
#pragma once
#include "music.hpp"

using Harmony = std::vector<Note>;

struct Penalty
{
  int arity; /* number of harmonies considered */
  float weight;

  float (*method)(const Harmony harmonies[], const FiguredBass bassline[]);
};

namespace penalties
{
  /* arity 1 */
  float spacing_penalty(const Harmony* harmony, const FiguredBass* bass);
  float doubling_penalty(const Harmony* harmony, const FiguredBass* bass);
  float omission_penalty(const Harmony* harmony, const FiguredBass* bass);

  /* arity 2 */
  float motion_penalty(const Harmony harmonies[2], const FiguredBass bassline[2]);
  float melodic_penalty(const Harmony harmonies[2], const FiguredBass bassline[2]);
  float tendency_penalty(const Harmony harmonies[2], const FiguredBass bassline[2]);
}
