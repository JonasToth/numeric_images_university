#include <iostream>
#include <blaze/Math.h>

#include "utility.h"

int main(int argc, char *argv[]) {
  constexpr std::size_t Dim = 10ul;
  auto ExampleVec = util::images::createSin<Dim>(0., M_PI);

  for (auto El : ExampleVec)
    std::cout << El << ", ";
  std::cout << "\n\n";

  auto ConstImage = ColMatrixD(Dim, Dim);
  for (std::size_t I = 0; I < Dim; ++I)
    blaze::column(ConstImage, I) = ExampleVec;

  const auto VecImage = util::math::vec(ConstImage);
  for (auto El : VecImage)
    std::cout << El << ", ";
  std::cout << "\n";

  return 0;
}
