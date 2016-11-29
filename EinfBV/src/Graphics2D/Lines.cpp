#include "Lines.hh"
#include "Matrices.hh"

using namespace std;

bool FloatLine2D::GetSlopeIntersectForm(float &m, float &b) const
{
  // Compute slope m = (B_y - A_y) / (B_x - A_x)
  Float2D dir = GetDirection(); // = B - A
  if (fabsf(dir[0]) < 1e-8) {
    return false;
  } else {
    m = dir[1] / dir[0];
    // Compute intersect b = A_y - m*A_x
    b = start_[1] - m*start_[0];
    return true;
  }
}

bool FloatLine2D::GetHesseNormalForm(Float2D &n, float &d) const
{
  // Compute vector orthogonal to direction
  Float2D dir = GetDirection();
  n.Set(-dir[1], dir[0]);
  // Scale length of vector to 1
  float len = n.GetNorm();
  if (len < 1e-8) {
    return false;
  } else {
    n /= len;
    // Compute distance d = n^T * A
    d = n.DotProduct(start_);
    if (d < 0) {
      // Correct sign of normal and distance
      n = -n;
      d = -d;
    }
    return true;
  }
}

bool FloatLine2D::GetIntersection(const FloatLine2D &L, Float2D &X) const
{
  // Compute intersection point from equation system
  // A1 + t1*(B1 - A1) = A2 + t2*(B2 - A2)
  Float2D dir1 = GetDirection();
  Float2D dir2 = L.GetDirection();
  Float2x2 mat;
  mat.SetColumn(0, dir1);
  mat.SetColumn(1, dir2);
  if (mat.Invert()) {
    Float2D t = mat * (L.start_ - start_);
    X = start_ + t[0] * dir1;
    return true;
  } else {
    return false;
  }
}
