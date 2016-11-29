/** @file   TestAffineTransform.cpp
    @brief  Test for affine transformation of primitives (exercise 3).
    @see    AffineTransform
    @author esquivel
*/

#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <Graphics2D/AffineTransform.hh>
#include <Graphics2D/PrimitivePoint.hh>
#include <Graphics2D/PrimitiveLine.hh>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 2) {
    cout << "Usage: TestAffineTransform <output image>" << endl;
    return 0;
  }
  string outputFilename = argv[1];
  cout << "-- TestAffineTransform --" << endl;

  // Create image as drawing canvas
  Image image(300, 200, Image::CM_RGB);
  image.Clear(Color::BLACK);

  // Create primitives
  vector<PrimitiveBase*> primitives;
  primitives.push_back(new PrimitiveLine(Color::RED, Float2D(100, 175), Float2D(100, 75)));
  primitives.push_back(new PrimitiveLine(Color::GREEN, Float2D(100, 75), Float2D(200, 75)));
  primitives.push_back(new PrimitiveLine(Color::BLUE, Float2D(200, 75), Float2D(200, 175)));
  primitives.push_back(new PrimitiveLine(Color::YELLOW, Float2D(200, 175), Float2D(100, 175)));
  primitives.push_back(new PrimitiveLine(Color::MAGENTA, Float2D(100, 175), Float2D(200, 75)));
  primitives.push_back(new PrimitiveLine(Color::CYAN, Float2D(200, 75), Float2D(150, 25)));
  primitives.push_back(new PrimitiveLine(Color::MAGENTA, Float2D(150, 25), Float2D(100, 75)));
  primitives.push_back(new PrimitiveLine(Color::CYAN, Float2D(100, 75), Float2D(200, 175)));
  primitives.push_back(new PrimitiveLine(Color::WHITE, Float2D(-100, 180), Float2D(400, 180)));
  for (unsigned int i = 0; i < 30; i++) {
    primitives.push_back(new PrimitivePoint(Color::WHITE, Float2D(rand() % 300, rand() % 200)));
  }

  // Create affine transformation
  AffineTransform T, T1, T2, T3;
  T1.MakeTranslation(-150.0f, -100.0f);
  T2.MakeRotation(30.0f * (float)M_PI / 180.0f);
  T3.MakeTranslation(150.0f, 100.0f);
  T = AffineTransform::Concatenate(T3, AffineTransform::Concatenate(T2, T1));

  // Apply affine transformation
  for (unsigned int i = 0; i < primitives.size(); i++) {
    primitives[i]->ApplyTransform(T);
  }

  // Draw all primitives into image
  for (unsigned int i = 0; i < primitives.size(); i++) {
    primitives[i]->Draw(image);
  }

  // Save image to file
  if (!ImageIO::Save(outputFilename, image)) {
    cerr << "Failed to write image to file " << outputFilename << "!" << endl;
  } else {
    cout << "Wrote image to file " << outputFilename << endl;
  }

  // Clean up all dynamically allocated objects
  for (unsigned int i = 0; i < primitives.size(); i++) {
    delete primitives[i];
  }

  return 0;
}
