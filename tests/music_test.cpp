#include <iostream>
#include <vector>
#include <optional>

#include "assert.hpp"
#include "../src/music.hpp"


void note_conversion_with_natural_key_and_degree()
{
  Key key = {.letter = 'D', .accidental = 0, .mode = Mode::major};
  Note note = {.degree = 4, .accidental = 0, .octave = 3};

  Note result = contextualize(key, note);

  EXPECT('G', result.letter);
  EXPECT(0, result.accidental);
  EXPECT(5, result.octave);
}

void note_conversion_with_flat_key_sharp_degree()
{
  Key key = {.letter = 'E', .accidental = -1, .mode = Mode::minor};
  Note note = {.degree = 7, .accidental = 1, .octave = 2};

  Note result = contextualize(key, note);

  EXPECT('D', result.letter);
  EXPECT(0, result.accidental);
  EXPECT(5, result.octave);
}

void note_conversion_with_sharp_key_sharp_degree()
{
  Key key = {.letter = 'F', .accidental = 1, .mode = Mode::minor};
  Note note = {.degree = 3, .accidental = 1, .octave = 3};

  Note result = contextualize(key, note);

  EXPECT('A', result.letter);
  EXPECT(1, result.accidental);
  EXPECT(5, result.octave)
}

void figured_bass_root_with_triad()
{
  std::vector<Figure> figures = {{6}, {4}};

  std::optional<Figure> root = get_root(figures);

  EXPECT(true, root.has_value());
  EXPECT(4, root->interval);
}

void figured_bass_root_with_seventh()
{
  std::vector<Figure> figures = {{6}, {5}, {3}};

  std::optional<Figure> root = get_root(figures);

  EXPECT(true, root.has_value());
  EXPECT(6, root->interval);
}

void figured_bass_root_with_suspension()
{
  std::vector<Figure> figures = {{7}, {6}, {3}};

  std::optional<Figure> root = get_root(figures);

  EXPECT(true, root.has_value());
  EXPECT(6, root->interval);
}

void figured_bass_root_with_non_harmonic_bass()
{
  std::vector<Figure> figures = {{7}, {5}, {2}};

  std::optional<Figure> root = get_root(figures);

  EXPECT(false, root.has_value());
}

int main(int argc, char **argv)
{
  note_conversion_with_natural_key_and_degree();
  note_conversion_with_flat_key_sharp_degree();
  note_conversion_with_sharp_key_sharp_degree();
  figured_bass_root_with_triad();
  figured_bass_root_with_seventh();
  figured_bass_root_with_suspension();
  figured_bass_root_with_non_harmonic_bass();

  return 0;
}
