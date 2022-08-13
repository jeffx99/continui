/* music.hpp */
#pragma once
#include <vector>

struct Note
{
  int degree;
  int octave = 1; // w.r.t to "lowest" tonic at octave 0
  int accidental = 0;

  operator int() const { return degree + 7 * octave; };
  Note operator ++(int);
};

struct Figure
{
  int interval;
  int accidental = 0;
};

struct FiguredBass
{
  Note note;
  std::vector<Figure> figures;
};
