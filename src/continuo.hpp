/* continuo.hpp */
#pragma once
#include "music.hpp"
#include "penalty.hpp"

using Harmony = std::vector<Note>;

class Realization
{
private:
  int voices;
  std::vector<std::pair<Note, Note>> ranges;

  std::vector<Harmony> harmonies;
  std::vector<FiguredBass> bassline;

  bool harmonic(Note note, FiguredBass bass);

  Harmony initial_harmony(FiguredBass bass);
  bool harmonic_successor(Harmony& harmony, FiguredBass bass);

  std::pair<float, std::vector<Harmony>> dp(float badness, int level);

public:
  std::vector<Penalty> penalties;

  Realization(int voices, std::vector<std::pair<Note, Note>> ranges, std::vector<FiguredBass> bassline);
  float realize(int depth);

  Note get_note(int voice, int index);
};
