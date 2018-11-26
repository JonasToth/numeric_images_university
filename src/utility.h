#ifndef UTILITY_H_QD7A9SFW
#define UTILITY_H_QD7A9SFW

#include <cmath>
#include <blaze/Math.h>

using ColVectorD = blaze::DynamicVector<double, blaze::columnVector>;
using ColMatrixD = blaze::DynamicMatrix<double, blaze::columnMajor>;

namespace util {
namespace data {

/// Write the vector to a .dat file, to be plottable with the utility scripts.
template <typename OutStream> void writeDat(const ColVectorD &V, OutStream &S) {
  for (std::size_t I = 0; I < V.size(); ++I)
    S << I << "\t" << V[I] << "\n";
}

/// Write the matrix to a .dat file, to be plottable with the utility scripts.
template <typename OutStream> void writeDat(const ColMatrixD &M, OutStream &S) {
  for (std::size_t Col = 0; Col < M.columns(); ++Col) {
    for (std::size_t Row = 0; Row < M.rows(); ++Row)
      S << Col << "\t" << Row << "\t" << M.at(Row, Col) << "\n";
    Col == M.columns() - 1 ? (void)Col : (void)(S << "\n");
  }
}
} // namespace data

namespace images {

/// This function creates a Vector with constant values.
template <std::size_t Dim> ColVectorD createConstant(double Value) {
  return ColVectorD(Dim, Value);
}

/// This function creates a Matrix (image) with constant values.
template <std::size_t Rows, std::size_t Columns>
ColMatrixD createConstant(double Value) {
  return ColMatrixD(Rows, Columns, Value);
}

/// Create a vector with \tp Dim elements that are calculated with \p f in the
/// range of [X1, X2].
template <std::size_t Dim, typename Func>
ColVectorD createFunction(double X1, double X2, Func f) {
  ColVectorD Result(Dim);
  double DX = (X2 - X1) / Dim;
  double X = X1;

  for (std::size_t I = 0ul; I < Dim; ++I, X += DX)
    Result[I] = f(X);
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

ColMatrixD unvec(const ColVectorD &Vec, std::size_t Rows, std::size_t Columns) {
  if (Rows * Columns != Vec.size())
    throw std::runtime_error{"Incompatible dimensions for unvec function"};
  ColMatrixD Result(Rows, Columns);

  for (std::size_t I = 0; I < Columns; I += Rows) {
    auto S = blaze::subvector(Vec, I, Rows);
    auto C = blaze::column(Result, I);
    C = S;
  }

  return Result;
}
} // namespace math
} // namespace util

#endif /* end of include guard: UTILITY_H_QD7A9SFW */
