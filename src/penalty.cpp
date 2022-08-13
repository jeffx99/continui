/* penalty.cpp */
#include <set>
#include <cmath>
#include "penalty.hpp"


float penalties::melodic_penalty(const Harmony harmonies[2], const FiguredBass bassline[2])
{
  float penalty = 0;
  for (int i = 0; i < harmonies[0].size(); i++)
  {
    penalty += std::abs(harmonies[1][i] - harmonies[0][i]);
  }

  return penalty;
}

float penalties::omission_penalty(const Harmony* harmony, const FiguredBass* bass)
{
  /* crude version: simply check how many figures are missing */
  /* improvement: check for "important" figures...(should be third and seventh) */

  std::set<int> intervals;
  for (Figure figure : bass->figures)
    if (figure.interval % 7 != 1)
      intervals.insert(figure.interval % 7);

  std::set<int> degrees;
  for (Note note : *harmony)
    if (note.degree != bass->note.degree)
      degrees.insert(note.degree);

  return intervals.size() - degrees.size();
}

float penalties::doubling_penalty(const Harmony* harmony, const FiguredBass* bass)
{
  /* crude version: penalize for doubling ^3 and ^7 (thirds of I and V) */
  /* improvement: avoid doubling sevenths of chords as well*/

  float weight_3 = 1;
  float weight_7 = 100;

  int count_3 = 0;
  int count_7 = 0;
  if (bass->note.degree == 3)
    count_3 += 1;
  if (bass->note.degree == 7)
    count_7 += 1;

  for (Note note : *harmony)
  {
    if (note.degree == 3)
      count_3 += 1;
    if (note.degree == 7)
      count_7 += 1;
  }

  return weight_3 * std::max(count_3 - 1, 0) + weight_7 * std::max(count_7 - 1, 0);
}
