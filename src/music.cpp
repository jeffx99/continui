/* music.cpp */
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
