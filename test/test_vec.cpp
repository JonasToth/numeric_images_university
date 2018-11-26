#define CATCH_CONFIG_MAIN

#include <catch2/catch.hpp>
#include "utility.h"

constexpr std::size_t Dim = 10ul;

TEST_CASE("VecTrivial", "") {
  ColMatrixD M(Dim, Dim, 0.);
  const auto VecM = util::math::vec(M);

  REQUIRE(VecM.size() == Dim * Dim);
  REQUIRE(std::all_of(std::begin(VecM), std::end(VecM),
                      [](double x) { return x == 0.; }));
}

TEST_CASE("VecReal", "") {
  auto V = util::images::createSin<Dim>(0., M_PI);
  REQUIRE(std::any_of(std::begin(V), std::end(V),
                      [](double x) { return x != 0.; }));

  auto ConstImage = ColMatrixD(Dim, Dim);
  for (std::size_t I = 0; I < Dim; ++I)
    blaze::column(ConstImage, I) = V;

  const auto VecImage = util::math::vec(ConstImage);
  REQUIRE(std::any_of(std::begin(VecImage), std::end(VecImage),
                      [](double x) { return x != 0.; }));
  REQUIRE(VecImage.size() == Dim * Dim);

  const auto UnVec = util::math::unvec(VecImage, Dim, Dim);
  REQUIRE(UnVec.rows() == Dim);
  REQUIRE(UnVec.columns() == Dim);
  REQUIRE(blaze::column(UnVec, 0) == V);
}
