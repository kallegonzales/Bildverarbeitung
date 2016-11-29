#include "ImageIO.hh"
#include <fstream>
#include <iostream>
#include <cstring>

using namespace std;

ImageIO::ImageIO()
{
}

bool ImageIO::Load(const string &filename, Image &image)
{
  // Get file extension from filename
  size_t pos = filename.find_last_of('.');
  string format = (pos != string::npos) ? filename.substr(pos) : "";
  // Call LoadPPM() or LoadFreeImage() depending on the extension
  if (format.compare(".ppm") == 0 || format.compare(".pgm") == 0 ||
      format.compare(".PPM") == 0 || format.compare(".PGM") == 0) {
    return LoadPPM(filename, image);
  } else {
#ifdef BUILD_WITH_FREEIMAGE
    return LoadFreeImage(filename, image);
#else
    cerr << "ImageIO::Load() : Only Portable PixMap images are supported!" << endl;
    return false;
#endif
  }
}

bool ImageIO::Save(const string &filename, const Image &image)
{
  // Get file extension from filename
  size_t pos = filename.find_last_of('.');
  string format = (pos != string::npos) ? filename.substr(pos) : "";
  // Call SavePPM() or SaveFreeImage() depending on the extension
  if (format.compare(".ppm") == 0 || format.compare(".pgm") == 0 ||
      format.compare(".PPM") == 0 || format.compare(".PGM") == 0) {
    return SavePPM(filename, image);
  } else {
#ifdef BUILD_WITH_FREEIMAGE
    return SaveFreeImage(filename, image);
#else
    cerr << "ImageIO::Save() : Only Portable PixMap images are supported!" << endl;
    return false;
#endif
  }
}

bool ImageIO::LoadPPM(const string &filename, Image &image)
{
  // Release current image
  image.Release();
  // Open file for input (support binary output)
  ifstream file;
  file.open(filename.c_str(), ios::in | ios::binary);
  // Check if file was opened successfully
  if (!file.good()) {
    cerr << "ImageIO::LoadPPM() : Failed to open file!" << endl;
    return false;
  }
  // Create string buffer for the comment and header
  string buffer;
  // Read header and check if PPM format is supported
  getline(file, buffer);
  if (buffer[0] != 'P' ||
      (buffer[1] != '2' && buffer[1] != '3' && buffer[1] != '5' && buffer[1] != '6')) {
    cerr << "ImageIO::LoadPPM() : Unknown image format found!" << endl;
    file.close();
    return false;
  }
  // Check if gray image (P2, P5) or color image (P3, P6) is given
  bool isGray = false;
  if (buffer[1] == '2' || buffer[1] == '5') {
    isGray = true;
  }
  // Check if plain text data (P2, P3) or binary data (P5, P6) is given
  bool isBinary = false;
  if (buffer[1] == '5' || buffer[1] == '6') {
    isBinary = true;
  }
  // Set color model for image
  Image::ColorModel colorModel = isGray ? Image::CM_Gray : Image::CM_RGB;
  // Check comment lines (in case they contain a color model specification)
  while (file.peek() == '#') {
    getline(file, buffer);
    if (buffer.compare("# CM_RGB") == 0) {
      if (!isGray)
        colorModel = Image::CM_RGB; // should be set already, but anyway...
      else
        cerr << "ImageIO::LoadPPM() : Ignoring incompatible color model!" << endl;
    } else if (buffer.compare("# CM_Gray") == 0) {
      if (isGray)
        colorModel = Image::CM_Gray; // should be set already, but anyway...
      else
        cerr << "ImageIO::LoadPPM() : Ignoring incompatible color model!" << endl;
    } else if (buffer.compare("# CM_HSV") == 0) {
      if (!isGray)
        colorModel = Image::CM_HSV; // set HSV instead of RGB color model
      else
        cerr << "ImageIO::LoadPPM() : Ignoring incompatible color model!" << endl;
    }
  }
  // Read width, height and max. value (the latter is ignored because we only use
  // unsigned char images and assume that max. value = 255)
  int w, h, maxVal;
  file >> w >> h >> maxVal;
  if (w <= 0 || h <= 0) {
    cerr << "ImageIO::LoadPPM() : Invalid image size found!" << endl;
    file.close();
    return false;
  }
  // Initialize image of size w x h with 1 or 3 channels
  image.Init(w, h, colorModel);
  // Read image data
  int numBytes = image.GetNumBytes();
  unsigned char *dataPtr = image.GetData();
  if (!isBinary) {
    // Read image data in plain text format
    int val;
    for (int i = 0; i < numBytes; i++, dataPtr++) {
      // Read next integer value from file stream
      file >> val;
      // Store as unsigned char
      *dataPtr = (unsigned char)val;
    }
  } else {
    // Skip to next line where the binary data starts
    getline(file, buffer);
    // Read data bytes from file
    file.read((char*)dataPtr, numBytes);
  }
  file.close();
  return true;
}

bool ImageIO::SavePPM(const string &filename, const Image &image)
{
  // Check image
  if (image.IsEmpty()) {
    cerr << "ImageIO::SavePPM() : Image is empty!" << endl;
    return false;
  }
  // Open file for output (support binary output)
  ofstream file;
  file.open(filename.c_str(), ios::out | ios::binary);
  // Check if file is ready for writing
  if (!file.good()) {
    cerr << "ImageIO::SavePPM() : Failed to write to file!" << endl;
    return false;
  }
  // Write header
  if (image.GetColorModel() == Image::CM_Gray)
    file << "P5" << endl;
  else
    file << "P6" << endl;
  switch (image.GetColorModel()) {
    case Image::CM_Gray:
      file << "# CM_Gray" << endl;
      break;
    case Image::CM_RGB:
      file << "# CM_RGB" << endl;
      break;
    case Image::CM_HSV:
      file << "# CM_HSV" << endl;
      break;
  }
  file << image.GetWidth() << " " << image.GetHeight() << endl;
  file << 255 << endl;
  // Write data bytes into file
  int numBytes = image.GetNumBytes();
  const unsigned char *dataPtr = image.GetData();
  file.write((char*)dataPtr, numBytes);
  file.close();
  return true;
}

#ifdef BUILD_WITH_FREEIMAGE

bool ImageIO::initFreeImageLib_ = false;

bool ImageIO::LoadFreeImage(const string &filename, Image &image)
{
  // Initialize FreeImage library
  if (!initFreeImageLib_) {
    FreeImage_Initialise();
    initFreeImageLib_ = true;
  }

  // Get image format from file or filename extension
  FREE_IMAGE_FORMAT tmpFormat = FreeImage_GetFileType(filename.c_str(), 0);
  if (tmpFormat == FIF_UNKNOWN)
    tmpFormat = FreeImage_GetFIFFromFilename(filename.c_str());
  if (tmpFormat == FIF_UNKNOWN) {
    cerr << "ImageIO::LoadFreeImage() : Failed to get image format using FreeImage!" << endl;
    image.Release();
    return false;
  }
  // Load image with FreeImage library
  FIBITMAP *tmpImage = NULL;
  if (FreeImage_FIFSupportsReading(tmpFormat))
    tmpImage = FreeImage_Load(tmpFormat, filename.c_str());
  if (!tmpImage) {
    cerr << "ImageIO::LoadFreeImage() : Failed to load image using FreeImage!" << endl;
    image.Release();
    return false;
  }
  CreateFromFreeImage_(tmpImage, image);
  FreeImage_Unload(tmpImage);
  if (image.IsEmpty()) {
    cerr << "ImageIO::LoadFreeImage() : Failed to convert image from FreeImage!" << endl;
    return false;
  }
  return true;
}

bool ImageIO::SaveFreeImage(const string &filename, const Image &image)
{
  // Check if image is empty
  if (image.IsEmpty()) {
   cerr << "ImageIO::SaveFreeImage() : Image is empty!" << endl;
   return false;
  }

  // Initialize FreeImage library
  if (!initFreeImageLib_) {
    FreeImage_Initialise();
    initFreeImageLib_ = true;
  }

  // Get image format from file or filename extension
  FREE_IMAGE_FORMAT tmpFormat = FreeImage_GetFileType(filename.c_str(), 0);
  if (tmpFormat == FIF_UNKNOWN)
    tmpFormat = FreeImage_GetFIFFromFilename(filename.c_str());
  if (tmpFormat == FIF_UNKNOWN) {
    cerr << "ImageIO::SaveFreeImage() : Failed to get image format using FreeImage!" << endl;
    return false;
  }
  // Save image with FreeImage library
  FIBITMAP *tmpImage = NULL;
  ConvertToFreeImage_(image, tmpImage);
  if (!tmpImage) {
    cerr << "ImageIO::SaveFreeImage() : Failed to convert image to FreeImage!" << endl;
    return false;
  }
  BOOL success = FreeImage_Save(tmpFormat, tmpImage, filename.c_str());
  FreeImage_Unload(tmpImage);
  if (!success) {
    cerr << "ImageIO::SaveFreeImage() : Failed to save image using FreeImage!" << endl;
    return false;
  }
  return true;
}

void ImageIO::ConvertToFreeImage_(const Image &src, FIBITMAP* &dst)
{
  // Check if image is empty
  if (dst != NULL) {
    FreeImage_Unload(dst);
    dst = NULL;
  }
  if (src.IsEmpty())
    return;

  // Create target image instance
  int w = src.GetWidth(), h = src.GetHeight(), ch = src.GetChannels();
  dst = FreeImage_Allocate(w, h, 8 * ch);
  if (!dst) return;

  // Copy target image data from source image
  BYTE *bits = NULL;
  const unsigned char *s = src.GetData();
  if (ch == 3) {
    for (int row = 0; row < h; row++) {
      bits = FreeImage_GetScanLine(dst, h-row-1);
      for (int col = 0; col < w; col++, bits += ch) {
        bits[FI_RGBA_RED] = *(s++);
        bits[FI_RGBA_GREEN] = *(s++);
        bits[FI_RGBA_BLUE] = *(s++);
      }
    }
  } else {
    for (int row = 0; row < h; row++) {
      bits = FreeImage_GetScanLine(dst, h-row-1);
      memcpy(bits, s, w * ch);
      s += w * ch;
    }
  }
}

void ImageIO::CreateFromFreeImage_(FIBITMAP* src, Image &dst)
{
  // Check if image is empty
  if (src == NULL) {
    dst.Release();
    return;
  }

  // Retrieve source image data
  BYTE *bits = FreeImage_GetBits(src);
  int w = FreeImage_GetWidth(src);
  int h = FreeImage_GetHeight(src);
  int ch = FreeImage_GetBPP(src) / 8;
  if (ch < 0) ch = 0; else if (ch > 4) ch = 4;
  FREE_IMAGE_COLOR_TYPE colorType = FreeImage_GetColorType(src);
  if (bits == NULL || w == 0 || h == 0 || ch == 0) {
    dst.Release();
    return;
  }
  if (colorType == FIC_PALETTE)
    ch = 3;

  // Copy source image data to target image
  Image::ColorModel cm = (ch < 3) ? Image::CM_Gray : Image::CM_RGB;
  dst.Init(w, h, cm);
  unsigned char *d = dst.GetData();
  if (colorType == FIC_PALETTE) {
    RGBQUAD *pal = FreeImage_GetPalette(src);
    for (int row = 0; row < h; row++) {
      bits = FreeImage_GetScanLine(src, h-row-1);
      for (int col = 0; col < w; col++, bits++) {
        *(d++) = pal[*bits].rgbRed;
        *(d++) = pal[*bits].rgbGreen;
        *(d++) = pal[*bits].rgbBlue;
      }
    }
  } else if (ch == 3 || ch == 4) {
    for (int row = 0; row < h; row++) {
      bits = FreeImage_GetScanLine(src, h-row-1);
      for (int col = 0; col < w; col++, bits += ch) {
        *(d++) = bits[FI_RGBA_RED];
        *(d++) = bits[FI_RGBA_GREEN];
        *(d++) = bits[FI_RGBA_BLUE];
      }
    }
  } else {
    for (int row = 0; row < h; row++) {
      bits = FreeImage_GetScanLine(src, h-row-1);
      for (int col = 0; col < w; col++, bits += ch)
        *(d++) = *bits;
    }
  }
}

#endif // BUILD_WITH_FREEIMAGE
