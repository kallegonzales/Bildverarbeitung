#include "PrimitivePolygon.hh"
#include "PrimitiveLine.hh"
#include <algorithm>
#include <iostream>

using namespace std;

PrimitivePolygon::PrimitivePolygon(const Color &color, int numPoints)
  : PrimitiveBase(color, numPoints)
{
}

PrimitivePolygon::PrimitivePolygon(const Color &color,
                                   const std::vector<Float2D> &points)
  : PrimitiveBase(color, points.size())
{
  for (int n = 0; n < (int)points.size(); n++) {
    SetPoint(n, points[n]);
  }
}

PrimitivePolygon::~PrimitivePolygon()
{
}

void PrimitivePolygon::Draw(Image &image) const
{
  int numPoints = GetNumPoints();

  // Draw lines between subsequent 2d points
  for (int n = 0; n < numPoints; n++) {
    PrimitiveLine line(color_, GetPoint(n), GetPoint((n+1) % numPoints));
    line.Draw(image);
  }
}
