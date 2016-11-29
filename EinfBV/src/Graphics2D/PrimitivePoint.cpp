#include "PrimitivePoint.hh"
#include <iostream>

using namespace std;

PrimitivePoint::PrimitivePoint(const Color &color, const Float2D &pos)
  : PrimitiveBase(color, 1)
{
  SetPoint(0, pos);
}

PrimitivePoint::~PrimitivePoint()
{
}

void PrimitivePoint::Draw(Image &image) const
{
  int x = (int)(GetPoint(0)[0] + 0.5f);
  int y = (int)(GetPoint(0)[1] + 0.5f);
  image.SetPixel(x, y, color_, true);
  image.SetPixel(x-1, y, color_, true);
  image.SetPixel(x+1, y, color_, true);
  image.SetPixel(x, y-1, color_, true);
  image.SetPixel(x, y+1, color_, true);
}
