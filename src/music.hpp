/* music.hpp */
#pragma once
#include <vector>
#include <optional>

enum class Mode {major, minor};

struct Key
{
  char letter;
  int accidental;

  Mode mode;
};

struct Note
{
  union
  {
    int degree;
    char letter;
  };

  int accidental = 0;
  int octave = 1; // w.r.t to "lowest" tonic at octave 0


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

/* Conversion from scale degree to absolute note name */
Note contextualize(Key key, Note note);

/* Applicable only to inversions of the triad or seventh (w/ possible suspended ninth) */
std::optional<Figure> get_root(std::vector<Figure> figures);
