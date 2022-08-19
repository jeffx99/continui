/* main.cpp */
#include <vector>
#include <iostream>
#include "continuo.hpp"
#include "penalty.hpp"
#include "bassline.hpp"
#include "music_input.hpp"

int main(int argc, char** argv)
{
  /* Realization */
  HarmonicRealization realization;

  realization.depth = 4;
  realization.ranges =
  {
    {{.degree = 1, .octave = 1}, {.degree = 5, .octave = 2}},
    {{.degree = 5, .octave = 1}, {.degree = 1, .octave = 3}},
    {{.degree = 5, .octave = 2}, {.degree = 5, .octave = 3}}
  };

  realization.rules =
  {
    {.penalty = &penalties::third_omission_penalty,     .weight = 3, .exponent = 1},
    {.penalty = &penalties::seventh_omission_penalty,   .weight = 2, .exponent = 1},
    {.penalty = &penalties::dissonant_omission_penalty, .weight = 2, .exponent = 1},

    {.penalty = &penalties::third_doubling_penalty,     .weight = 1, .exponent = 1},
    {.penalty = &penalties::seventh_doubling_penalty,   .weight = 2, .exponent = 1},

    {.penalty = &penalties::melodic_penalty,            .weight = 0.5, .exponent = 2}
  };

  /*
    Take user input (interactive mode):
      - get meter + voices
      -  get bassline
        - sections preceded by local key. e.g. "c#:"
        - a series of notes with optional figures attached (separated by whitespace)
        - sections terminated by period "|" (final section terminated by "||")
      - while taking input
        - keep track of current position and position of last essential bass note
        - use this to construct an essential bassline
          - add bass notes to harmonic realization
          - keep a separate vector of durations
  */
  Meter meter;

  std::cout << "meter: ";
  std::cin >> meter;

  std::cout << "voices: ";
  std::cin >> realization.voices;

  std::cout << "bassline: " << std::endl;
  std::cout << std::endl;

  std::vector<Segment> segments;
  do /*for (int i = 0; i < 1; ++i)*/ {
    segments.push_back(Segment());

    Segment& segment = segments.back();
    segment.meter = meter;
    segment.lines.resize(realization.voices);
    std::cin >> segment.key;

    if (std::cin.peek() != ':')
      std::cout << "invalid key delimiter: "/* + (char)std::cin.peek()*/ << std::endl;
    std::cin.ignore();

    rational prev = {0};
    rational next = {0};
    while (std::cin.peek() != '|')
    {
      Note note;
      std::cin >> note;

      segment.lines[0].push_back(note);
      next += note.value;

      /* check if bass note is essential */
      if (std::cin.peek() == ';')
      {
        std::cin.ignore();

        FiguredBass figured_bass = {.pitch = absolute_to_relative(segment.key, note.pitch)};
        std::cin >> figured_bass.figures;

        segment.essential_basses.push_back({figured_bass, next - prev});
        prev = next;
      }

      std::cin >> std::ws;
    }
    std::cin.ignore();
  } while (std::cin.peek() != '|');

  /*
    Perform realizations:
      - for each segment run a harmonic realization
        - take the last chord of each segment and use it as the first for the next
  */
  for (int i = 0; i < segments.size(); ++i)
  {
    realization.progress = 0;
    realization.progression.clear();
    realization.mode = segments[i].key.mode;
    for (auto pair : segments[i].essential_basses)
      realization.progression.push_back({.harmony = {}, .bass = pair.first});

    realization.realize();
    for (int j = 0; j < realization.voices; ++j)
    {
      segments[i].lines.push_back({});
      for (int k = 0; k < realization.progression.size(); ++k)
      {
        Chord chord = realization.progression[k];
        auto pair = segments[i].essential_basses[k];

        segments[i].lines[j+1].push_back({.pitch = relative_to_absolute(segments[i].key, chord.harmony[j]), .value = pair.second});
      }
    }
  }

  /*
    Print result
  */

  for (int i = realization.voices - 1; i >= 0; --i)
  {
    for (Segment& segment : segments)
    {
        for (Note note : segment.lines[i+1])
          std::cout << note << " ";

        std::cout << std::endl;
    }
  }
}
