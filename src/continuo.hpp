/* continuo.hpp */
#pragma once
#include <map>
#include "music.hpp"
#include "penalty.hpp"

class HarmonicRealization
{
private:
  Harmony initial_harmony(FiguredBass bass);
  bool harmonic_successor(Harmony& harmony, FiguredBass bass);

  std::pair<float, std::vector<Harmony>> dp(float badness, int level);

public:
  int depth;
  int progress = 0;

  int voices;
  Mode mode;

  std::vector<std::pair<Note, Note>> ranges; /* from lowest to highest */
  std::map<std::string, Rule> rules;

  std::vector<Chord> progression;

  float realize();
};
