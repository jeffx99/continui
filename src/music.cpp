/* music.cpp */
#include <set>
#include <algorithm>
#include <iostream>
#include "music.hpp"

Pitch Pitch::operator++(int)
{
  degree++;
  if (degree > 7)
  {
    degree -= 7;
    octave++;
  }

  return *this;
}

/* Defined only for pitchs with a well defined scale degree */
Pitch operator+(const Pitch pitch, const Figure figure)
{
  return {
    .degree = (pitch.degree + figure.interval + 5) % 7 + 1 ,
    .accidental = figure.accidental,
    .octave = pitch.octave + (pitch.degree + figure.interval - 2) / 7
  };
}

/* Conversion from scale degree to absolute pitch name */
Pitch relative_to_absolute(Key key, Pitch pitch)
{
  /* LETTER */
  char letter = ((key.letter - 'A') + (pitch.degree - 1)) % 7 + 'A';

  /* ACCIDENTAL */
  /* semitones from tonic in the C major scale */
  static int major_semi[7] = {0, 2, 4, 5, 7, 9, 11};
  static int minor_semi[7] = {0, 2, 3, 5, 7, 8, 10};

  int* semi;
  switch (key.mode) {
    case MAJOR:
      semi = major_semi;
      break;
    case MINOR:
      semi = minor_semi;
      break;
  }

  /*
      1. determine interval between key.letter and key.letter + pitch.degree
      2. adjust with accidentals
  */
  int i = (key.letter - 'C' + 7) % 7;
  int j = (i + (pitch.degree - 1)) % 7;

  int interval = (major_semi[j] - major_semi[i] + 12) % 12;
  interval -= key.accidental;

  int accidental = (semi[pitch.degree - 1] + pitch.accidental) - interval;

  /* OCTAVE */
  /* semitones from C_2 */
  int octave = 2 + (major_semi[i] + major_semi[pitch.degree - 1] + 12 * pitch.octave) / 12;

  return {.letter = letter, .accidental = accidental, .octave = octave};
}


/* Conversion from absolute pitch to scale degree (inverse to above) */
Pitch absolute_to_relative(Key key, Pitch pitch)
{
  /* DEGREE */
  int degree = (pitch.letter - key.letter + 7) % 7 + 1;

  /* ACCIDENTAL */
  /* semitones from tonic in the C major scale */
  static int major_semi[7] = {0, 2, 4, 5, 7, 9, 11};
  static int minor_semi[7] = {0, 2, 3, 5, 7, 8, 10};

  int* semi;
  switch (key.mode) {
    case MAJOR:
      semi = major_semi;
      break;
    case MINOR:
      semi = minor_semi;
      break;
  }

  int i = (key.letter - 'C' + 7) % 7;
  int j = (pitch.letter - 'C' + 7) % 7;
  int interval = (major_semi[j] - major_semi[i] + 12) % 12;
  interval += pitch.accidental - key.accidental;

  int accidental = interval - semi[degree - 1];

  /* OCTAVE */
  int octave = (12 * (pitch.octave - 2) - major_semi[i] + major_semi[j]) / 12;

  return {.degree = degree, .accidental = accidental, .octave = octave};
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
