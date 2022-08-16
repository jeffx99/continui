/* penalty.cpp */
#include <set>
#include <cmath>
#include <optional>
#include "penalty.hpp"


float penalties::melodic_penalty(const Harmony harmonies[2], const FiguredBass bassline[2], Mode mode)
{
  float penalty = 0;
  for (int i = 0; i < harmonies[0].size(); i++)
  {
    penalty += std::abs(harmonies[1][i] - harmonies[0][i]);
  }

  return penalty;
}


float penalties::third_omission_penalty(const Harmony* harmony, const FiguredBass* bass, Mode mode)
{
  std::optional<Figure> root = get_root(bass->figures);

  if (root)
  {
    Note third = (bass->note + root.value()) + Figure{3};
    if (bass->note.degree == third.degree)
      return 0;

    for (Note note : *harmony)
      if (note.degree == third.degree)
        return 0;
  }

  return 1;
}

float penalties::seventh_omission_penalty(const Harmony* harmony, const FiguredBass* bass, Mode mode)
{
  std::optional<Figure> root = get_root(bass->figures);

  if (root)
  {
    Note seventh = (bass->note + root.value()) + Figure{7};
    if (bass->note.degree == seventh.degree)
      return 0;

    for (Note note : *harmony)
      if (note.degree == seventh.degree)
        return 0;
  }

  return 1;
}

float penalties::dissonant_omission_penalty(const Harmony* harmony, const FiguredBass* bass, Mode mode)
{
  static std::set<int> dissonant_suspensions {4, 7, 9};
  std::set<int> missing;

  for (Figure figure : bass->figures)
  {
    if (dissonant_suspensions.contains(figure.interval))
    {
      Note note = bass->note + figure;
      missing.insert(note.degree);
    }
  }
  for (Note note : *harmony)
      missing.erase(note.degree);

  return missing.size();
}

float penalties::third_doubling_penalty(const Harmony* harmony, const FiguredBass* bass, Mode mode)
{
  std::optional<Figure> root = get_root(bass->figures);
  int penalty = -1;

  if (root)
  {
    Note third = (bass->note + root.value()) + Figure{3};
    if (bass->note.degree == third.degree)
      penalty++;

    for (Note note : *harmony)
      if (note.degree == third.degree)
        penalty++;
  }

  return penalty >= 0 ? penalty : 0;
}

float penalties::seventh_doubling_penalty(const Harmony* harmony, const FiguredBass* bass, Mode mode)
{
  std::optional<Figure> root = get_root(bass->figures);
  int penalty = -1;

  if (root)
  {
    Note seventh = (bass->note + root.value()) + Figure{7};
    if (bass->note.degree == seventh.degree)
      penalty++;

    for (Note note : *harmony)
      if (note.degree == seventh.degree)
        penalty++;
  }

  return penalty >= 0 ? penalty : 0;
}
