#include "Vectors.hh"
#include <cstdio>

using namespace std;

// Define global operators on floating point 2d vectors
Float2D operator+(const Float2D& p1, const Float2D& p2)
{
  return Float2D(p1[0] + p2[0], p1[1] + p2[1]);
}
Float2D operator-(const Float2D& p1, const Float2D& p2)
{
  return Float2D(p1[0] - p2[0], p1[1] - p2[1]);
}
Float2D operator*(float s, const Float2D& p)
{
  return Float2D(s * p[0], s * p[1]);
}
Float2D operator/(const Float2D& p, float s)
{
  return Float2D(p[0] / s, p[1] / s);
}
ostream& operator<<(ostream &os, const Float2D& p)
{
  os << "[ " << p[0] << ", " << p[1] << " ]"; return os;
}

// Define global operators on integer 2d vectors
Int2D operator+(const Int2D& p1, const Int2D& p2)
{
  return Int2D(p1[0] + p2[0], p1[1] + p2[1]);
}
Int2D operator-(const Int2D& p1, const Int2D& p2)
{
  return Int2D(p1[0] - p2[0], p1[1] - p2[1]);
}
Int2D operator*(int s, const Int2D& p)
{
  return Int2D(s * p[0], s * p[1]);
}
Int2D operator/(const Int2D& p, int s)
{
  return Int2D(p[0] / s, p[1] / s);
}
ostream& operator<<(ostream &os, const Int2D& p)
{
  os << "[ " << p[0] << ", " << p[1] << " ]"; return os;
}

