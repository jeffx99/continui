/* continuo.cpp */
#include <tuple>
#include <algorithm>
#include <iostream>
#include "continuo.hpp"

Realization::Realization(int voices, std::vector<std::pair<Note, Note>> ranges, std::vector<FiguredBass> bassline) : voices(voices), ranges(ranges), bassline(bassline) {};

/*
  Given a bass note and figures, generate all possible n-voice harmonies.
  To do this, we order all the harmonies and construct an initial harmony.
  The successor function:
    Take the lowest voice and move it up to the next chord tone.
    If it can not be moved up, then reset its position and repeat the previous steps, using the next highest voice.

  Proof:
    succ(x) is defined for all but the terminal harmony, where each voice is at the end of its range.
    succ(x) has an inverse defined for all but the initial harmony, which:
      moves the lowest voice down the the next chord tone if possible,
      or repeats the previous steps next highest voice,
      and then moves the lower voices up as far as a possible
    Hence proving the claim... (succ can actually be extended to a bijection cyclically permuting things)
*/
bool Realization::harmonic(Note note, FiguredBass bass)
{
  for (Figure figure : bass.figures)
    if ((figure.interval - 1) % 7 == (note - bass.note) % 7)
      return true;

  return false;
}

Harmony Realization::initial_harmony(FiguredBass bass)
{
  Harmony harmony;
  for (int i = 0; i < voices; i++)
    harmony.push_back((ranges[i].first >= bass.note) ? ranges[i].first : bass.note);

  for (int i = voices - 1; i >= 0; i--)
  {
    Note limit = ranges[i].second;
    if (i + 1 < voices && harmony[i + 1] < limit)
      limit = harmony[i + 1];

    while (harmony[i] < limit)
    {
      harmony[i]++;
      if (harmonic(harmony[i], bass))
        break;
    }
  }

  return harmony;
}

bool Realization::harmonic_successor(Harmony& harmony, FiguredBass bass)
{
  Harmony initial = initial_harmony(bass);

  for (int i = 0; i < voices; i++)
  {
    Note limit = ranges[i].second;
    if (i + 1 < voices && harmony[i + 1] < limit)
      limit = harmony[i + 1];

    while (harmony[i] < limit)
    {
      harmony[i]++;
      if (harmonic(harmony[i], bass))
        return true;
    }
    /* else */
    harmony[i] = initial[i];
  }

  return false;
}

std::pair<float, std::vector<Harmony>> Realization::dp(float badness, int level)
{
  /* DP (DFS + memoization): find realization of the next [depth] bass notes with the least badness */

  if (harmonies.size() == bassline.size() || level == 0)
    return {badness, {}};

  float minimum = -1;
  std::vector<Harmony> solution;

  Harmony current_harmony = initial_harmony(bassline.at(harmonies.size()));
  do
  {
    harmonies.push_back(current_harmony);

    /* calculate badness */
    float delta = 0;
    for (Penalty penalty : penalties)
    {
      /* check if penalty is applicable */
      if (harmonies.size() < penalty.arity)
        continue;

      /* apply penalty */
      int j = harmonies.size() - penalty.arity;
      delta += penalty.weight * penalty.method(&harmonies[j], &bassline[j]);

      /* prune if delta is too large */
    }

    /* solve subproblems */
    float score;
    std::vector<Harmony> tentative;
    std::tie(score, tentative) = dp(badness + delta, level - 1);
    tentative.push_back(current_harmony);

    if (score < minimum || minimum == -1)
      std::tie(minimum, solution) = {score, tentative};

    harmonies.pop_back();
  } while(harmonic_successor(current_harmony, bassline.at(harmonies.size())));

  return {minimum, solution};
}

float Realization::realize(int depth)
{
  float badness = 0;

  while (harmonies.size() != bassline.size())
  {
    float delta;
    std::vector<Harmony> progression;
    std::tie(delta, progression) = dp(0, depth);

    badness += delta;
    harmonies.insert(harmonies.end(), progression.rbegin(), progression.rend());
  }

  return badness;
}

Note Realization::get_note(int voice, int index)
{
  return harmonies[index][voice];
}
