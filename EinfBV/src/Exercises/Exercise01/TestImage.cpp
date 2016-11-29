/** @file   TestImage.cpp
    @brief  Test for basic image functions (exercise 1).
    @see    Image
    @author esquivel
*/

#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <iostream>
#include <string>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 2) {
    cout << "Usage: TestImage <output image> <width> <height>" << endl;
    return 0;
  }
  string outputFilename = argv[1];
  int width = (argc > 2) ? atoi(argv[2]) : 320;
  int height = (argc > 3) ? atoi(argv[3]) : 240;
  cout << "-- TestImage --" << endl;

  // Create image
  Image image(width, height, Image::CM_RGB);

  // Draw into image
  Color color(0, 0, 0);
  for (int y = 0; y < height; y++) {
    color.red = (256 * y) / height;
    for (int x = 0; x < width; x++) {
      color.green = (256 * x) / width;
      image.SetPixel(x, y, color);
    }
  }

  // Save image to file
  if (!ImageIO::Save(outputFilename, image)) {
    cerr << "Failed to write image to file " << outputFilename << "!" << endl;
  } else {
    cout << "Wrote image to file " << outputFilename << endl;
  }

  return 0;
}
