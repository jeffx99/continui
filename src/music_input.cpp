/* music_input.cpp */
#include <ctype.h>
#include <stdlib.h>
#include <iostream>
#include "music_input.hpp"

std::istream& operator>>(std::istream& is, rational& r)
{
  is >> r.numerator;
  if (is.peek() == '/')
  {
    is.ignore();
    is >> r.denominator;
  }
  return is;
}

std::ostream& operator<<(std::ostream& os, rational r)
{
  os << r.numerator;
  if (r.denominator != 1)
  {
    os << '/' << r.denominator;
  }
  return os;
}


std::istream& operator>>(std::istream& is, Pitch& pitch)
{
  char ficta;
  int amount = 0;
  int multiplier;

  is >> pitch.letter;
  if (is.peek() == '#' || is.peek() == 'b')
  {
    ficta = is.peek();
    while (is.peek() == ficta)
    {
      is.ignore();
      ++amount;
    }
  }

  if (ficta == '#')
    multiplier = +1;
  if (ficta == 'b')
    multiplier = -1;

  pitch.accidental = amount * multiplier;
  is >> pitch.octave;
  return is;
}

std::ostream& operator<<(std::ostream& os, Pitch pitch)
{
  char ficta = (pitch.accidental > 0) ? '#' : 'b';

  os << pitch.letter;
  for (int i = 0; i < abs(pitch.accidental); ++i)
    os << ficta;

  os << pitch.octave;
  return os;
}

std::istream& operator>>(std::istream& is, Note& note)
{
  is >> note.pitch;

  if (is.peek() != ':')
    throw std::invalid_argument("invalid delimiter");

  is.ignore();
  is >> note.value;
  return is;
}

std::ostream& operator<<(std::ostream& os, Note note)
{
  os << note.pitch << ':' << note.value;
  return os;
}
