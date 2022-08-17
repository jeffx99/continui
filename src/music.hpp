/* music.hpp */
#pragma once
#include <vector>
#include <optional>

struct Note;
using Harmony = std::vector<Note>;

enum Mode { MAJOR, MINOR };
enum Accidental { DOUBLE_FLAT = -2, FLAT, NATURAL, SHARP, DOUBLE_SHARP};

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

struct Chord
{
  Harmony harmony;
  FiguredBass bass;
};

/* Defined only for notes with a well defined scale degree */
Note operator+(const Note note, const Figure figure);

/* Conversion from scale degree to absolute note name */
Note contextualize(Key key, Note note);

/* Applicable only to inversions of the triad or seventh (w/ possible suspended ninth) */
std::optional<Figure> get_root(std::vector<Figure> figures);
