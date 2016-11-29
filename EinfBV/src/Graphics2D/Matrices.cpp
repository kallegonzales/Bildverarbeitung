#include "Matrices.hh"
#include <cstdio>

using namespace std;

// Define global operators on floating point 2x2 matrices
Float2x2 operator+(const Float2x2 &M1, const Float2x2 &M2)
{
  Float2x2 M(M1); M += M2; return M;
}
Float2x2 operator-(const Float2x2 &M1, const Float2x2 &M2)
{
  Float2x2 M(M1); M -= M2; return M;
}
Float2x2 operator*(float s, const Float2x2& M)
{
  Float2x2 Ms(M); Ms *= s; return Ms;
}
Float2x2 operator/(const Float2x2& M, float s)
{
  Float2x2 Ms(M); Ms /= s; return Ms;
}
Float2x2 operator*(const Float2x2 &M1, const Float2x2 &M2)
{
  Float2x2 M(M1); M.Mult(M2); return M;
}
Float2D operator*(const Float2x2 &M, const Float2D &v)
{
  return M.MultVec(v);
}
ostream& operator<<(ostream &os, const Float2x2 &M)
{
  os << "[ " << M[0][0] << ", " << M[0][1] << " ; "
     << M[1][0] << ", " << M[1][1] << " ]";
  return os;
}

