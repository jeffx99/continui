/* continuo.hpp */
#pragma once
#include "music.hpp"
#include "penalty.hpp"

class HarmonicRealization
{
private:
  Harmony initial_harmony(FiguredBass bass);
  bool harmonic_successor(Harmony& harmony, FiguredBass bass);

  std::pair<float, std::vector<Harmony>> dp(float threshold, float badness, int level);

public:
  int depth;
  int progress = 0;

  int voices;
  Mode mode;

  std::vector<std::pair<Pitch, Pitch>> ranges; /* from lowest to highest */
  std::vector<Rule> rules;

  std::vector<Chord> progression;

  float realize();
};
