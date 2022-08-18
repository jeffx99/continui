/* continuo.cpp */
#include <tuple>
#include <algorithm>
#include <iostream>
#include "continuo.hpp"

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
bool harmonic(Note& note, FiguredBass bass)
{
  for (Figure figure : bass.figures)
  {
    Note other = bass.note + figure;
    if (note.degree == other.degree)
    {
      note.accidental = other.accidental;
      return true;
    }
  }
  return false;
}

Harmony HarmonicRealization::initial_harmony(FiguredBass bass)
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

bool HarmonicRealization::harmonic_successor(Harmony& harmony, FiguredBass bass)
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

std::pair<float, std::vector<Harmony>> HarmonicRealization::dp(float badness, int level)
{
  /* DP: find realization of the next [depth] bass notes with the least badness */

  if (progress == progression.size() || level == 0)
    return {badness, {}};

  float minimum = -1;
  std::vector<Harmony> solution;

  Harmony current_harmony = initial_harmony(progression[progress].bass);
  do
  {
    progression[progress++].harmony = current_harmony;

    /* calculate badness */
    float delta = 0;
    for (auto const& [key, rule] : rules)
    {
      /* check if penalty is applicable */
      if (progress < rule.penalty->arity)
        continue;

      /* apply penalty */
      int j = progress - rule.penalty->arity;
      delta += rule.weight * rule.penalty->method(&progression[progress], mode);

      /* prune if delta is too large */
    }

    /* solve subproblems */
    float score;
    std::vector<Harmony> tentative;
    std::tie(score, tentative) = dp(badness + delta, level - 1);
    tentative.push_back(current_harmony);

    if (score < minimum || minimum == -1)
      std::tie(minimum, solution) = {score, tentative};

    progression[--progress].harmony = {};
  } while(harmonic_successor(current_harmony, progression[progress].bass));

  return {minimum, solution};
}

float HarmonicRealization::realize()
{
  float badness = 0;

  while (progress < progression.size())
  {
    float delta;
    std::vector<Harmony> solution;
    std::tie(delta, solution) = dp(0, depth);

    badness += delta;
    for (int i = 0; i < solution.size(); ++i)
      progression[progress++].harmony = solution[i];
  }

  return badness;
}
