#ifndef UTILITY_H_QD7A9SFW
#define UTILITY_H_QD7A9SFW

#include <cmath>
#include <blaze/Math.h>

using ColVectorD = blaze::DynamicVector<double, blaze::columnVector>;
using ColMatrixD = blaze::DynamicMatrix<double, blaze::columnMajor>;

namespace util {
namespace images {

/// This function creates a Vector with constant values.
template <std::size_t Dim> ColVectorD createConstant(double Value) {
  return ColVectorD(Dim, Value);
}

/// Create a vector with \tp Dim elements that are calculated with \p f in the
/// range of [X1, X2].
template <std::size_t Dim, typename Func>
ColVectorD createFunction(double X1, double X2, Func f) {
  ColVectorD Result(Dim);
  double DX = (X2 - X1) / Dim;
  double X = X1;

  for (std::size_t I = 0ul; I < (Dim - 1); ++I) {
    Result[I] = f(X);
    X += DX;
  }
  Result[Dim - 1] = f(X2);

  return Result;
}

/// This function creates a Vector with \tp Dim elements that contains the
/// values for `y(x) = A * sin(B*x + C) + D` from \p X1 to \p X2.
/// \sa createFunction
template <std::size_t Dim>
ColVectorD createSin(double X1, double X2, double A = 1., double B = 1.,
                     double C = 0., double D = 0.) {
  auto Func = [&](double X) { return A * std::sin(B * X + C) + D; };
  return createFunction<Dim>(X1, X2, Func);
}
} // namespace images

namespace math {
ColVectorD vec(const ColMatrixD &Mat) {
  ColVectorD Result(Mat.rows() * Mat.columns());

  for (std::size_t Col = 0, I = 0; Col < Mat.columns(); ++Col) {
    auto C = blaze::column(Mat, Col);
    auto S = blaze::subvector(Result, I, Mat.rows());
    S = C;
    I += Mat.rows();
  }
  return Result;
}
} // namespace math
} // namespace util

#endif /* end of include guard: UTILITY_H_QD7A9SFW */
