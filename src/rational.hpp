/* rational.hpp */
#pragma once

/* Helper Struct */

struct rational
{
  int numerator;
  int denominator;

  rational& operator+=(const rational&);
  rational& operator-=(const rational&);
  rational& operator*=(const rational&);
  rational& operator/=(const rational&);
}


bool operator==(const rational&, const rational&);


rational operator+(const rational&, const rational&);
rational operator-(const rational&, const rational&);
rational operator*(const rational&, const rational&);
rational operator/(const rational&, const rational&);
