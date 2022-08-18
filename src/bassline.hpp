/* bassline.hpp */
#pragma once
#include "music.hpp"
#include "rational.hpp"

/*
  VoiceLine:

    - A given meter (for now this is just 4/4)?
    - A series of notes with durations attached (either relative or absolute pitches)
*/
using duration = rational;

struct Note
{
  Pitch pitch;
  duration value;
};

struct Meter
{
  int multiple;
  duration beat;
};

struct VoiceLine
{
  Meter meter;
  std::vector<Note> notes;
};
