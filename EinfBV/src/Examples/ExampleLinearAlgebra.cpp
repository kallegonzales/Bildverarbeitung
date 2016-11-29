/** @file   ExampleLinearAlgebra.cpp
    @brief  Example for use of linear algebra classes.
    @see    ImageIO
    @author esquivel
*/

#include <Graphics2D/Matrices.hh>
#include <Graphics2D/Vectors.hh>
#include <iostream>
#include <string>

using namespace std;

int main()
{
  // Define 2d points
  Float2D p0(2.0f, 5.0f);
  Float2D p1(3.0f, -1.0f);

  // Compute their difference vector
  Float2D dp = p1 - p0;
  cout << "p0 is " << p0 << ", p1 is " << p1 << endl;
  cout << "Difference vector is " << dp << endl;

  // Rotate the vector by 30 degree
  float phi = 30.0f * (float)M_PI / 180.0f;
  Float2x2 R(cosf(phi), -sinf(phi), sinf(phi), cosf(phi));
  dp = R * dp;
  cout << "Rotated difference vector is " << dp << endl;

  // Rotate it back using the inverse matrix
  Float2x2 R_inv = R;
  R_inv.Invert();
  dp = R_inv * dp;
  cout << "Back-rotated difference vector is " << dp << endl;

  return 0;
}
