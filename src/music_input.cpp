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
    throw std::invalid_argument("invalid note delimiter: " + (char)is.peek());

  is.ignore();
  is >> note.value;
  return is;
}

std::ostream& operator<<(std::ostream& os, Note note)
{
  os << note.pitch << ':' << note.value;
  return os;
}

std::istream& operator>>(std::istream& is, Figure& figure)
{
  char ficta;
  int amount = 0;
  int multiplier;

  is >> figure.interval;
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

  figure.accidental = amount * multiplier;
  return is;
}

std::ostream& operator<<(std::ostream& os, Figure figure)
{
  char ficta = (figure.accidental > 0) ? '#' : 'b';

  os << figure.interval;
  for (int i = 0; i < abs(figure.accidental); ++i)
    os << ficta;

  return os;
}

std::istream& operator>>(std::istream& is, std::vector<Figure>& figures)
{
  is.ignore();
  while (is.peek() != '>')
  {
    Figure figure;
    is >> figure;

    figures.push_back(figure);
    is >> std::ws;
  }
  return is;
}


std::ostream& operator<<(std::ostream& os, std::vector<Figure> figures)
{
  os << '<';
  for (int i = 0; i < figures.size(); ++i)
  {
    os << figures[i];
    if (i != figures.size() - 1)
      os << ' ';
  }
  os << '>';
  return os;
}
