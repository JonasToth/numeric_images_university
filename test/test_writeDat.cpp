#include <catch2/catch.hpp>
#include <algorithm>
#include <iostream>
#include <sstream>
#include "utility.h"

constexpr std::size_t Dim = 10ul;
TEST_CASE("writeVecConst", "") {
  const auto V = util::images::createConstant<Dim>(42.);
  REQUIRE(std::all_of(std::begin(V), std::end(V),
                      [](double v) { return v == 42.; }));

  std::ostringstream oss;
  util::data::writeDat(V, oss);
  REQUIRE(oss.str() == "0\t42\n"
                       "1\t42\n"
                       "2\t42\n"
                       "3\t42\n"
                       "4\t42\n"
                       "5\t42\n"
                       "6\t42\n"
                       "7\t42\n"
                       "8\t42\n"
                       "9\t42\n");
}

TEST_CASE("writeVecFuncion", "") {
  const auto V = util::images::createFunction<Dim>(
      0., 10., [](double X) { return X + 0.5; });

  std::ostringstream oss;
  util::data::writeDat(V, oss);
  REQUIRE(oss.str() == "0\t0.5\n"
                       "1\t1.5\n"
                       "2\t2.5\n"
                       "3\t3.5\n"
                       "4\t4.5\n"
                       "5\t5.5\n"
                       "6\t6.5\n"
                       "7\t7.5\n"
                       "8\t8.5\n"
                       "9\t9.5\n");
}

TEST_CASE("writeMatConst", "") {
  const auto M = util::images::createConstant<2, 2>(1.2);
  std::ostringstream oss;
  util::data::writeDat(M, oss);

  REQUIRE(oss.str() == "0\t0\t1.2\n"
                       "0\t1\t1.2\n"
                       "\n"
                       "1\t0\t1.2\n"
                       "1\t1\t1.2\n");
}
