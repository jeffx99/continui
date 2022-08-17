/* penalty.cpp */
#include <set>
#include <cmath>
#include <optional>
#include "penalty.hpp"


extern const Penalty penalties::melodic_penalty =
{
  .arity = 2,
  .method = [](const Chord* chords, Mode mode) -> float
  {
    float penalty = 0;
    for (int i = 0; i < chords[0].harmony.size(); i++)
    {
      penalty += std::abs(chords[1].harmony[i] - chords[0].harmony[i]);
    }

    return penalty;
  }
};


extern const Penalty penalties::third_omission_penalty =
{
  .arity = 1,
  .method = [](const Chord* chord, Mode mode) -> float
  {
    std::optional<Figure> root = get_root(chord->bass.figures);

    if (root)
    {
      Note third = (chord->bass.note + root.value()) + Figure{3};
      if (chord->bass.note.degree == third.degree)
        return 0;

      for (Note note : chord->harmony)
        if (note.degree == third.degree)
          return 0;
    }
    return 1;
  }
};

extern const Penalty penalties::seventh_omission_penalty =
{
  .arity = 1,
  .method = [](const Chord* chord, Mode mode) -> float
  {
    std::optional<Figure> root = get_root(chord->bass.figures);

    if (root)
    {
      Note seventh = (chord->bass.note + root.value()) + Figure{7};
      if (chord->bass.note.degree == seventh.degree)
        return 0;

      for (Note note : chord->harmony)
        if (note.degree == seventh.degree)
          return 0;
    }

    return 1;
  }
};

extern const Penalty penalties::dissonant_omission_penalty
{
  .arity = 1,
  .method = [](const Chord* chord, Mode mode) -> float
  {
    static std::set<int> dissonant_suspensions {4, 7, 9};
    std::set<int> missing;

    for (Figure figure : chord->bass.figures)
    {
      if (dissonant_suspensions.contains(figure.interval))
      {
        Note note = chord->bass.note + figure;
        missing.insert(note.degree);
      }
    }
    for (Note note : chord->harmony)
        missing.erase(note.degree);

    return missing.size();
  }
};

extern const Penalty penalties::third_doubling_penalty =
{
  .arity = 1,
  .method = [](const Chord* chord, Mode mode) -> float
  {
    std::optional<Figure> root = get_root(chord->bass.figures);
    int penalty = -1;

    if (root)
    {
      Note third = (chord->bass.note + root.value()) + Figure{3};
      if (chord->bass.note.degree == third.degree)
        penalty++;

      for (Note note : chord->harmony)
        if (note.degree == third.degree)
          penalty++;
    }

    return penalty >= 0 ? penalty : 0;
  }
};

extern const Penalty penalties::seventh_doubling_penalty =
{
  .arity = 1,
  .method = [](const Chord* chord, Mode mode) -> float
  {
    std::optional<Figure> root = get_root(chord->bass.figures);
    int penalty = -1;

    if (root)
    {
      Note seventh = (chord->bass.note + root.value()) + Figure{7};
      if (chord->bass.note.degree == seventh.degree)
        penalty++;

      for (Note note : chord->harmony)
        if (note.degree == seventh.degree)
          penalty++;
    }

    return penalty >= 0 ? penalty : 0;
  }
};
