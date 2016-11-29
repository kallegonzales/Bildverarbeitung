#include "PrimitiveRectangle.hh"
#include <iostream>

using namespace std;

PrimitiveRectangle::
PrimitiveRectangle(const Color &color, const Float2D &topLeft,
                   const Float2D &bottomRight)
  : PrimitivePolygon(color, 4)
{
  SetPoint(0, topLeft);
  SetPoint(1, Float2D(bottomRight[0], topLeft[1]));
  SetPoint(2, bottomRight);
  SetPoint(3, Float2D(topLeft[0], bottomRight[1]));
}

PrimitiveRectangle::~PrimitiveRectangle()
{
}
