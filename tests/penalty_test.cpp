#include "assert.hpp"
#include "../src/penalty.hpp"

void omission_penalty_with_ambiguous_quality()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 5},
    .figures =
    {
      {7},
      {5},
      {3}
    }
  };

  Harmony harmony =
  {
    {.degree = 4, .octave = 3},
    {.degree = 2, .octave = 3}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::third_omission_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}

void omission_penalty_with_seventh_chord()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 4},
    .figures =
    {
      {6},
      {5},
      {3}
    }
  };

  Harmony harmony =
  {
    {.degree = 2, .octave = 3},
    {.degree = 6, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::seventh_omission_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}

void omission_penalty_with_ninth()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 4},
    .figures =
    {
      {9},
      {7}
    }
  };

  Harmony harmony =
  {
    {.degree = 3, .octave = 3},
    {.degree = 4, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::dissonant_omission_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}


void omission_penalty_with_fourth()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 1},
    .figures =
    {
      {5},
      {4}
    }
  };

  Harmony harmony =
  {
    {.degree = 5, .octave = 2},
    {.degree = 5, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::dissonant_omission_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}

void doubling_penalty_with_doubled_third()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 7},
    .figures =
    {
      {6},
      {5},
      {3}
    }
  };

  Harmony harmony =
  {
    {.degree = 7, .octave = 3},
    {.degree = 7, .octave = 2},
    {.degree = 5, .octave = 2},
    {.degree = 4, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::third_doubling_penalty.method(&chord, MAJOR);
  EXPECT(2, penalty);
}

void doubling_penalty_with_doubled_seventh()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 2},
    .figures =
    {
      {6},
      {4},
      {3}
    }
  };

  Harmony harmony =
  {
    {.degree = 7, .octave = 3},
    {.degree = 4, .octave = 3},
    {.degree = 5, .octave = 2},
    {.degree = 4, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::seventh_doubling_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}

void doubling_penalty_with_doubled_seventh_in_bass()
{
  FiguredBass bass =
  {
    .pitch = {.degree = 1},
    .figures =
    {
      {6},
      {4},
      {2}
    }
  };

  Harmony harmony =
  {
    {.degree = 4, .octave = 3},
    {.degree = 6, .octave = 2},
    {.degree = 2, .octave = 2},
    {.degree = 1, .octave = 2}
  };

  Chord chord = {harmony, bass};
  float penalty = penalties::seventh_doubling_penalty.method(&chord, MAJOR);
  EXPECT(1, penalty);
}

void motion_penalty_with_parallel_fifths()
{

}

void motion_penalty_with_parallel_octaves()
{

}

void motion_penalty_with_contrary_motion()
{

}

void melodic_penalty_with_perfect_cadence()
{

}

void melodic_penalty_with_change_of_position()
{

}

void tendency_penalty_with_perfect_cadence()
{

}

void tendency_penalty_with_dropped_leading_tone()
{

}

void tendency_penalty_with_suspension()
{

}

void tendency_penalty_with_fourth()
{

}

int main(int argc, char **argv)
{
  omission_penalty_with_ambiguous_quality();
  omission_penalty_with_seventh_chord();
  omission_penalty_with_ninth();
  omission_penalty_with_fourth();

  doubling_penalty_with_doubled_third();
  doubling_penalty_with_doubled_seventh();
  doubling_penalty_with_doubled_seventh_in_bass();

  motion_penalty_with_parallel_fifths();
  motion_penalty_with_parallel_octaves();
  motion_penalty_with_contrary_motion();

  melodic_penalty_with_perfect_cadence();
  melodic_penalty_with_change_of_position();

  tendency_penalty_with_perfect_cadence();
  tendency_penalty_with_dropped_leading_tone();
  tendency_penalty_with_suspension();
  tendency_penalty_with_fourth();
}
