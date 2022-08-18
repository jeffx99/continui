#include <vector>
#include <optional>
#include "assert.hpp"
#include "../src/music.hpp"

void pitch_addition_with_natural_figure()
{
  Pitch pitch = {.degree = 3, .accidental = 1, .octave = 2};
  Figure figure = {5};

  Pitch result = pitch + figure;

  EXPECT(7, result.degree);
  EXPECT(0, result.accidental);
  EXPECT(2, result.octave);
}

void pitch_addition_with_sharp_figure()
{
  Pitch pitch = {.degree = 1, .accidental = 0, .octave = 3};
  Figure figure = {4, SHARP};

  Pitch result = pitch + figure;

  EXPECT(4, result.degree);
  EXPECT(1, result.accidental);
  EXPECT(3, result.octave);
}

void pitch_addition_with_increasing_octave()
{
  Pitch pitch = {.degree = 5, .accidental = 0, .octave = 2};
  Figure figure = {5};

  Pitch result = pitch + figure;

  EXPECT(2, result.degree);
  EXPECT(0, result.accidental);
  EXPECT(3, result.octave);
}

void pitch_conversion_with_natural_key_and_degree()
{
  Key key = {.letter = 'D', .accidental = 0, .mode = MAJOR};
  Pitch pitch = {.degree = 4, .accidental = 0, .octave = 3};

  Pitch result = relative_to_absolute(key, pitch);
  Pitch original = absolute_to_relative(key, result);

  EXPECT('G', result.letter);
  EXPECT(0, result.accidental);
  EXPECT(5, result.octave);

  EXPECT(4, original.degree);
  EXPECT(0, original.accidental);
  EXPECT(3, original.octave);
}

void pitch_conversion_with_flat_key_sharp_degree()
{
  Key key = {.letter = 'E', .accidental = -1, .mode = MINOR};
  Pitch pitch = {.degree = 7, .accidental = 1, .octave = 2};

  Pitch result = relative_to_absolute(key, pitch);
  Pitch original = absolute_to_relative(key, result);

  EXPECT('D', result.letter);
  EXPECT(0, result.accidental);
  EXPECT(5, result.octave);


  EXPECT(7, original.degree);
  EXPECT(1, original.accidental);
  EXPECT(2, original.octave);
}

void pitch_conversion_with_sharp_key_sharp_degree()
{
  Key key = {.letter = 'F', .accidental = 1, .mode = MINOR};
  Pitch pitch = {.degree = 3, .accidental = 1, .octave = 3};

  Pitch result = relative_to_absolute(key, pitch);
  Pitch original = absolute_to_relative(key, result);

  EXPECT('A', result.letter);
  EXPECT(1, result.accidental);
  EXPECT(5, result.octave)

  EXPECT(3, original.degree);
  EXPECT(1, original.accidental);
  EXPECT(3, original.octave);
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
  pitch_addition_with_natural_figure();
  pitch_addition_with_sharp_figure();
  pitch_addition_with_increasing_octave();

  pitch_conversion_with_natural_key_and_degree();
  pitch_conversion_with_flat_key_sharp_degree();
  pitch_conversion_with_sharp_key_sharp_degree();

  figured_bass_root_with_triad();
  figured_bass_root_with_seventh();
  figured_bass_root_with_suspension();
  figured_bass_root_with_non_harmonic_bass();

  return 0;
}
