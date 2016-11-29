#include "AffineTransform.hh"
#include <iostream>
#include <cmath>

using namespace std;

AffineTransform::AffineTransform()
{
  A.MakeIdentity();
  b.SetZero();
}

AffineTransform::AffineTransform(const Float2x2 &mat, const Float2D &vec)
{
  A = mat;
  b = vec;
}

void AffineTransform::Transform(Float2D &X) const
{
  X = A * X + b;
}

AffineTransform AffineTransform::Concatenate(const AffineTransform &T1,
                                             const AffineTransform &T2)
{
  return AffineTransform(T1.A * T2.A, T1.A * T2.b + T1.b);
}

bool AffineTransform::Invert()
{
  // Set A to inv(A) and b to -inv(A) * b
  bool success = A.Invert();
  if (success) {
    b = A * -b;
  }
  return success;
}

void AffineTransform::MakeIdentity()
{
  A.MakeIdentity();
  b.SetZero();
}

void AffineTransform::MakeRotation(float angle)
{
  float c = cosf(angle), s = sinf(angle);
  A.Set(c, -s, s, c);
  b.SetZero();
}

void AffineTransform::MakeTranslation(float tx, float ty)
{
  A.MakeIdentity();
  b.Set(tx, ty);
}

void AffineTransform::MakeScaling(float sx, float sy)
{
  A.MakeDiagonal(sx, sy);
  b.SetZero();
}

void AffineTransform::MakeShearing(float sx, float sy)
{
  A.Set(1.0f, sx, sy, 1.0f);
  b.SetZero();
}
