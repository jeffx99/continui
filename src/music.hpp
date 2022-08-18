/* music.hpp */
#pragma once
#include <vector>
#include <optional>

struct Pitch;
using Harmony = std::vector<Pitch>;

enum Mode { MAJOR, MINOR };
enum Accidental { DOUBLE_FLAT = -2, FLAT, NATURAL, SHARP, DOUBLE_SHARP};

struct Key
{
  char letter;
  int accidental;

  Mode mode;
};

struct Pitch
{
  union
  {
    int degree;
    char letter;
  };

  int accidental = 0;
  int octave = 1; // w.r.t to "lowest" tonic at octave 0


  operator int() const { return degree + 7 * octave; };
  Pitch operator ++(int);
};

struct Figure
{
  int interval;
  int accidental = 0;
};

struct FiguredBass
{
  Pitch pitch;
  std::vector<Figure> figures;
};

struct Chord
{
  Harmony harmony;
  FiguredBass bass;
};

/* Defined only for pitchs with a well defined scale degree */
Pitch operator+(const Pitch pitch, const Figure figure);

/* Conversion from scale degree to absolute pitch name */
Pitch relative_to_absolute(Key key, Pitch pitch);
Pitch absolute_to_relative(Key key, Pitch pitch);

/* Applicable only to inversions of the triad or seventh (w/ possible suspended ninth) */
std::optional<Figure> get_root(std::vector<Figure> figures);
