#include "assert.hpp"
#include "../src/rational.hpp"

void rational_addition_with_same_denominator()
{
  rational r = {1, 3};
  rational s = {2, 3};

  rational sum = {1};

  VERIFY (r + s == sum);
}

void rational_addition_with_different_denominator()
{
  rational r = {30, 50};
  rational s = {4, 3};

  rational sum = {29, 15};

  VERIFY(r + s == sum);
}

void rational_subtraction_with_different_denominator()
{
  rational r = {36, 20};
  rational s = {1, 3};

  rational difference = {22, 15};

  VERIFY(r - s == difference);
}

void rational_mutliplication()
{
  rational r = {4, 35};
  rational s = {7, 5};

  rational product = {4, 25};

  VERIFY(r * s == product);
}

int main(int argc, char **argv)
{
  rational_addition_with_same_denominator();
  rational_addition_with_different_denominator();
  rational_subtraction_with_different_denominator();
  rational_mutliplication();
}
