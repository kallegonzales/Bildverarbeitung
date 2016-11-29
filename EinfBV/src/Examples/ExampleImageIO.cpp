/** @file   ExampleImageIO.cpp
    @brief  Example for reading/writing images.
    @see    ImageIO
    @author esquivel
*/

#include <Graphics2D/Image.hh>
#include <Graphics2D/ImageIO.hh>
#include <iostream>
#include <string>

using namespace std;

int main(int argc, char *argv[])
{
  // Read parameters
  if (argc < 2) {
    cout << "Usage: ExampleImageIO <input image> [<output image>]" << endl;
    return 0;
  }
  string inputFilename = argv[1];
  string outputFilename = (argc > 2) ? argv[2] : "";
  cout << "-- ExampleImageIO --" << endl;

  // Load image from file
  Image image;
  if (!ImageIO::Load(inputFilename, image)) {
    cerr << "Failed to read image from file " << inputFilename << "!" << endl;
    return -1;
  } else {
    cout << "Read image from file " << inputFilename << endl;
  }

  // Show image information
  int width = image.GetWidth(), height = image.GetHeight();
  int channels = image.GetChannels();
  cout << "Image has size " << width << " x " << height << " pixels and "
       << channels << " channels" << endl;
  cout << "Size of image instance is " << sizeof(image) << " B + "
       << 1e-3*image.GetNumBytes() << " kB image data" << endl;
  cout << "Color model is ";
  switch (image.GetColorModel()) {
    case Image::CM_Gray:
      cout << "CM_Gray" << endl; break;
    case Image::CM_RGB:
      cout << "CM_RGB" << endl; break;
    case Image::CM_HSV:
      cout << "CM_HSV" << endl; break;
    case Image::CM_None:
      cout << "CM_None" << endl; break;
    default:
      cout << "unknown" << endl; break;
  }

  // Save image to file
  if (!outputFilename.empty()) {
    if (!ImageIO::Save(outputFilename, image)) {
      cerr << "Failed to write image to file " << outputFilename << "!" << endl;
    } else {
      cout << "Wrote image to file " << outputFilename << endl;
    }
  }

  return 0;
}
