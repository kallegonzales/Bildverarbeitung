#include "PrimitiveLine.hh"
#include <iostream>

using namespace std;

PrimitiveLine::PrimitiveLine(const Color &color, const Float2D &start, const Float2D &end)
  : PrimitiveBase(color, 2)
{
  SetPoint(0, start);
  SetPoint(1, end);
}

PrimitiveLine::~PrimitiveLine()
{
}

void PrimitiveLine::Draw(Image &image) const
{
  // Compute integer coordinates of endpoints
  int x1 = (int)(GetPoint(0)[0] + 0.5f);
  int y1 = (int)(GetPoint(0)[1] + 0.5f);
  int x2 = (int)(GetPoint(1)[0] + 0.5f);
  int y2 = (int)(GetPoint(1)[1] + 0.5f);
  // Compute absolute distance along x- and y-direction
  int dx = abs(x2 - x1), dy = abs(y2 - y1);
  // Compute direction of steps in x- and y-direction
  int sx = x1 < x2 ? 1 : -1, sy = y1 < y2 ? 1 : -1;
  if (dx > dy) {
    // Draw line along x-direction (slope <= 45 degree)
    int E = 2*dy - dx;
    for (int i = 0; i <= dx; i++) {
      image.SetPixel(x1, y1, color_, true);
      // Update coordinates and decision variable
      if (E <= 0) {
        x1 += sx;
        E += 2*dy;
      } else {
        x1 += sx;
        y1 += sy;
        E += 2*(dy - dx);
      }
    }
  } else {
    // Draw line along y-direction (flip roles of x and y)
    int E = 2*dx - dy;
    for (int i = 0; i <= dy; i++) {
      image.SetPixel(x1, y1, color_, true);
      // Update coordinates and decision variable
      if (E <= 0) {
        y1 += sy;
        E += 2*dx;
      } else {
        y1 += sy;
        x1 += sx;
        E += 2*(dx - dy);
      }
    }
  }
}
