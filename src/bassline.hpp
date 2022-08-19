/* bassline.hpp */
#pragma once
#include "music.hpp"
#include "rational.hpp"

/*
  VoiceLine:

    - A given meter (for now this is just 4/4)?
    - A series of notes with durations attached (either relative or absolute pitches)
*/
struct Note;
using VoiceLine = std::vector<Note>;

struct Meter
{
  int multiple;
  rational beat;
};

struct Note
{
  Pitch pitch;
  rational value;
};

struct Segment
{
  Key key;
  Meter meter;

  std::vector<VoiceLine> lines = {{}};

  std::vector<std::pair<FiguredBass, rational>> essential_basses;
};
