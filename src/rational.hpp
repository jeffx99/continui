/* rational.hpp */
#pragma once

/* Helper Struct */

struct rational
{
  int numerator;
  int denominator = 1;

  rational& operator+=(const rational&);
  rational& operator-=(const rational&);
  rational& operator*=(const rational&);
  rational& operator/=(const rational&);
};


bool operator==(const rational&, const rational&);


rational operator+(rational, const rational&);
rational operator-(rational, const rational&);
rational operator*(rational, const rational&);
rational operator/(rational, const rational&);
