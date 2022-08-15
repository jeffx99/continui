/* music.cpp */
#include <set>
#include <algorithm>
#include <iostream>
#include "music.hpp"

Note Note::operator++(int)
{
  degree++;
  if (degree > 7)
  {
    degree -= 7;
    octave++;
  }

  return *this;
}

/* Conversion from scale degree to absolute note name */
Note contextualize(Key key, Note note)
{
  /* LETTER */
  char letter = ((key.letter - 'A') + (note.degree - 1)) % 7 + 'A';

  /* ACCIDENTAL */
  /* semitones from tonic in the C major scale */
  static int major_semi[7] = {0, 2, 4, 5, 7, 9, 11};
  static int minor_semi[7] = {0, 2, 3, 5, 7, 8, 10};

  int* semi;
  switch (key.mode) {
    case Mode::major:
      semi = major_semi;
      break;
    case Mode::minor:
      semi = minor_semi;
      break;
  }

  /*
    Sharpening:
      1. determine interval between key.letter and key.letter + note.degree
      2. adjust with accidentals 
  */
  int i = (key.letter - 'C' + 7) % 7;
  int j = (i + (note.degree - 1)) % 7;

  int interval = (major_semi[j] - major_semi[i] + 12) % 12;
  interval -= key.accidental;

  int accidental = (semi[note.degree - 1] + note.accidental) - interval;

  /* OCTAVE */
  /* semitones from C_2 */
  int octave = (major_semi[i] + major_semi[note.degree - 1] + 12 * note.octave) / 12;

  return {.letter = letter, .accidental = accidental, .octave = octave + 2};
}

/* Applicable only to inversions of the triad or seventh (w/ possible suspended ninth) */
std::optional<Figure> get_root(std::vector<Figure> figures)
{
  std::set<int> desired = {1, 3, 5, 7, 2 /* 9 */};

  figures.push_back({1});
  for (Figure figure : figures)
  {
    std::set<int> intervals;
    int j = figure.interval - 1;

    for (Figure figure : figures)
      intervals.insert((figure.interval - j + 6) % 7 + 1);

    bool rooted = true;
    for (int interval : intervals)
      rooted &= desired.contains(interval);

    if (rooted && intervals.contains(3)) /* must contain the third to be considered the root */
        return figure;
  }

  return std::nullopt;
}
