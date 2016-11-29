#include "PrimitiveBase.hh"
#include <iostream>

using namespace std;

PrimitiveBase::PrimitiveBase(const Color &color, int numPoints)
  : color_(color), points_(numPoints)
{
}

PrimitiveBase::~PrimitiveBase()
{
}

Color PrimitiveBase::GetColor() const
{
  return color_;
}

void PrimitiveBase::SetColor(const Color &color)
{
  color_ = color;
}

Float2D PrimitiveBase::GetPoint(int n) const
{
  if (n >= 0 && n < (int)points_.size()) {
    return points_[n];
  } else {
    cerr << "PrimitiveBase::GetPoint() : Invalid point index " << n << "!" << endl;
    return Float2D(0, 0);
  }
}

void PrimitiveBase::SetPoint(int n, const Float2D &p)
{
  if (n >= 0 && n < (int)points_.size()) {
    points_[n] = p;
  } else {
    cerr << "PrimitiveBase::SetPoint() : Invalid point index " << n << "!" << endl;
  }
}

int PrimitiveBase::GetNumPoints() const
{
  return points_.size();
}

void PrimitiveBase::ApplyTransform(const AffineTransform &T)
{
  for (int n = 0; n < (int)points_.size(); n++) {
    T.Transform(points_[n]);
  }
}
