/* rational.cpp */
#include <numeric>
#include "rational.hpp"

rational& rational::operator+=(const rational& other)
{
  int common = std::lcm(denominator, other.denominator);

  numerator = numerator * (common/denominator) + other.numerator * (common/other.denominator);
  denominator = common;

  return *this;
}

rational& rational::operator-=(const rational& other)
{
  int common = std::lcm(denominator, other.denominator);

  numerator = numerator * (common/denominator) - other.numerator * (common/other.denominator);
  denominator = common;

  return *this;
}

rational& rational::operator*=(const rational& other)
{
  numerator = numerator * other.numerator;
  denominator = denominator * other.denominator;

  return *this;
}

rational& rational::operator/=(const rational& other)
{
  numerator = numerator * other.denominator;
  denominator = denominator * other.numerator;

  return *this;
}

bool operator==(const rational& lhs, const rational& rhs)
{
  return (lhs.numerator * rhs.denominator == lhs.denominator * rhs.numerator);
}


rational operator+(rational lhs, const rational& rhs)
{
    lhs += rhs;
    return lhs;
}

rational operator-(rational lhs, const rational& rhs)
{
    lhs -= rhs;
    return lhs;
}

rational operator*(rational lhs, const rational& rhs)
{
    lhs *= rhs;
    return lhs;
}

rational operator/(rational lhs, const rational& rhs)
{
    lhs /= rhs;
    return lhs;
}
