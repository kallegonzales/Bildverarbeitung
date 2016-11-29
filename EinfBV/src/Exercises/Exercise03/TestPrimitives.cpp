/** @file   TestPrimitives.cpp
    @brief  Test for drawing primitives into images (exercise 3).
    @see    PrimitiveBase
    @author esquivel
*/

#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <Graphics2D/PrimitivePoint.hh>
#include <Graphics2D/PrimitiveLine.hh>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 2) {
    cout << "Usage: TestPrimitives <output image>" << endl;
    return 0;
  }
  string outputFilename = argv[1];
  cout << "-- TestPrimitives --" << endl;

  // Create image as drawing canvas
  Image image(300, 200, Image::CM_RGB);
  image.Clear(Color::BLACK);

/*
  // Create line primitives
  vector<PrimitiveLine> lines;
  lines.push_back(PrimitiveLine(Color::RED, Float2D(100, 175), Float2D(100, 75)));
  lines.push_back(PrimitiveLine(Color::GREEN, Float2D(100, 75), Float2D(200, 75)));
  lines.push_back(PrimitiveLine(Color::BLUE, Float2D(200, 75), Float2D(200, 175)));
  lines.push_back(PrimitiveLine(Color::YELLOW, Float2D(200, 175), Float2D(100, 175)));
  lines.push_back(PrimitiveLine(Color::MAGENTA, Float2D(100, 175), Float2D(200, 75)));
  lines.push_back(PrimitiveLine(Color::CYAN, Float2D(200, 75), Float2D(150, 25)));
  lines.push_back(PrimitiveLine(Color::MAGENTA, Float2D(150, 25), Float2D(100, 75)));
  lines.push_back(PrimitiveLine(Color::CYAN, Float2D(100, 75), Float2D(200, 175)));
  lines.push_back(PrimitiveLine(Color::WHITE, Float2D(-100, 180), Float2D(400, 180)));

  // Create point primitives
  vector<PrimitivePoint> points;
  for (unsigned int i = 0; i < 30; i++) {
    points.push_back(PrimitivePoint(Color::WHITE, Float2D(rand() % 300, rand() % 200)));
  }

  // Draw line primitives into image
  for (unsigned int i = 0; i < lines.size(); i++) {
    lines[i].Draw(image);
  }

  // Draw point primitives into image
  for (unsigned int i = 0; i < points.size(); i++) {
    points[i].Draw(image);
  }
*/

  /** @note
   *  The solution above has the disadvantage that we need separate vectors
   *  for each primitive type. Since all primitive classes are derived from
   *  PrimitiveBase which provides a common interface for all primitives,
   *  let's better use a vector of PrimitiveBase pointers instead. Note that
   *  we have to use pointers when we are working with interface classes.
   */

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
