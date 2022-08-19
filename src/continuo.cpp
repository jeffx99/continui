/* continuo.cpp */
#include <tuple>
#include <algorithm>
#include <iostream>
#include "continuo.hpp"

/*
  Given a bass pitch and figures, generate all possible n-voice harmonies.
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
bool make_harmonic(Pitch& pitch, FiguredBass bass)
{
  bass.figures.push_back({8, bass.pitch.accidental});
  for (Figure figure : bass.figures)
  {
    Pitch other = bass.pitch + figure;
    if (pitch.degree == other.degree)
    {
      pitch.accidental = other.accidental;
      return true;
    }
  }
  return false;
}

Harmony HarmonicRealization::initial_harmony(FiguredBass bass)
{
  Harmony harmony;
  for (int i = 0; i < voices; i++)
    harmony.push_back((ranges[i].first >= bass.pitch) ? ranges[i].first : bass.pitch);

  for (int i = voices - 1; i >= 0; i--)
  {
    Pitch limit = ranges[i].second;
    if (i + 1 < voices && harmony[i + 1] < limit)
      limit = harmony[i + 1];

    while (harmony[i] < limit)
    {
      harmony[i]++;
      if (make_harmonic(harmony[i], bass))
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
    Pitch limit = ranges[i].second;
    if (i + 1 < voices && harmony[i + 1] < limit)
      limit = harmony[i + 1];

    while (harmony[i] < limit)
    {
      harmony[i]++;
      if (make_harmonic(harmony[i], bass))
        return true;
    }
    /* else */
    harmony[i] = initial[i];
  }

  return false;
}

std::pair<float, std::vector<Harmony>> HarmonicRealization::dp(float threshold, float badness, int level)
{
  /* DP: find realization of the next [depth] bass pitchs with the least badness */

  if (progress == progression.size() || level == 0)
    return {badness, {}};

  float minimum = -1;
  std::vector<Harmony> solution;

  Harmony current_harmony = initial_harmony(progression[progress].bass);
  do
  {
    progression[progress].harmony = current_harmony;
    bool surpassed = false;

    /* calculate badness */
    float delta = 0;
    for (Rule const& rule : rules)
    {
      /* check if penalty is applicable */
      if (progress + 1 < rule.penalty->arity)
        continue;

      /* apply penalty */
      delta += rule.weight * rule.penalty->method(&progression[progress], mode);

      /* prune if delta is too large */
      if (badness + delta >= threshold && threshold >= 0)
      {
        surpassed = true;
        break;
      }
    }

    if (surpassed)
      continue;

    /* solve subproblems */
    float score;
    std::vector<Harmony> tentative;

    ++progress;
    std::tie(score, tentative) = dp(threshold, badness + delta, level - 1);
    tentative.push_back(current_harmony);

    if (score < minimum || minimum == -1)
      std::tie(minimum, solution) = {score, tentative};

    if (minimum < threshold || threshold == -1)
      threshold = minimum;

    --progress;
    progression[progress].harmony = {};
  } while(harmonic_successor(current_harmony, progression[progress].bass));

  if (minimum == -1)
    return {threshold + 1, {}};
  else
    return {minimum, solution};
}

float HarmonicRealization::realize()
{
  float badness = 0;
  do
  {
    float delta;
    std::vector<Harmony> solution;
    std::tie(delta, solution) = dp(-1, 0, depth);

    badness += delta;
    for (int i = solution.size() - 1; i >= 0; --i)
      progression[progress++].harmony = solution[i];

  } while (progress < progression.size() - 1);

  return badness;
}
