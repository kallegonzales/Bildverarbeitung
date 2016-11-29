/** @file   TestLineIntersection.cpp
    @brief  Test for 2d line intersection (exercise 2).
    @see    FloatLine2D
    @author esquivel
*/

#include <Graphics2D/Lines.hh>
#include <Graphics2D/Vectors.hh>
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 9) {
    cout << "Usage: TestLineIntersection x1 y1 x2 y2 x3 y3 x4 y4" << endl;
    return 0;
  }
  cout << "-- TestLineIntersection --" << endl;

  // Read points
  Float2D X[4];
  for (int i = 0; i < 4; i++) {
    X[i].Set((float)atof(argv[2*i+1]), (float)atof(argv[2*i+2]));
  }

  // Create lines
  FloatLine2D L[2];
  for (int i = 0; i < 2; i++) {
    L[i].Set(X[2*i], X[2*i+1]);
    cout << endl << "Line " << i << ": " << L[i].GetStart() << " -> "
         << L[i].GetEnd() << endl;
    Float2D n;
    float d;
    if (L[i].GetHesseNormalForm(n, d)) {
      cout << "Hesse normal form is n = " << n << ", d = " << d << endl;
    } else {
      cerr << "Failed to compute Hesse normal form, line is degenerate!" << endl;
    }
    float m, b;
    if (L[i].GetSlopeIntersectForm(m, b)) {
      cout << "Slope is m = " << m << ", intersect is b = " << b << endl;
    } else {
      cerr << "Failed to compute slope-intersect form, line is vertical or degenerate!" << endl;
    }
  }

  // Compute intersection point
  Float2D S;
  if (L[0].GetIntersection(L[1], S)) {
    cout << endl << "Intersection at " << S << endl;
  } else {
    cout << endl << "No intersection!" << endl;
  }

  return 0;
}
