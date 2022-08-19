/* music_input.hpp */
#pragma once
#include <istream>
#include <ostream>
#include <vector>
#include "music.hpp"
#include "bassline.hpp"

std::istream& operator>>(std::istream&, rational&);
std::ostream& operator<<(std::ostream&, rational);

std::istream& operator>>(std::istream&, Meter&);
std::ostream& operator<<(std::ostream&, Meter);

std::istream& operator>>(std::istream&, Key&);
std::ostream& operator<<(std::ostream&, Key);

std::istream& operator>>(std::istream&, Pitch&);
std::ostream& operator<<(std::ostream&, Pitch);

std::istream& operator>>(std::istream&, Note&);
std::ostream& operator<<(std::ostream&, Note);

std::istream& operator>>(std::istream&, Figure&);
std::ostream& operator<<(std::ostream&, Figure);

std::istream& operator>>(std::istream&, std::vector<Figure>&);
std::ostream& operator<<(std::ostream&, std::vector<Figure>);



/*
  Parsing rules:

  - Notes are written with absolute pitches with duration
    - e.g. F#3:3/8
  - A semicolon ();) signifies a note with figures attached
    - e.g. Bbb:1;<5 3>
*/
