#include "Image.hh"
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <cstring>

#define RINT(x)      (int)(x + 0.5f)
#define CLAMP(x,a,b) (((x) < (a)) ? (a) : (((x) > (b)) ? (b) : (x)))

using namespace std;

Image::Image()
  : width_(0), height_(0), channels_(0), data_(NULL), colorModel_(CM_None)
{
}

Image::Image(int w, int h, ColorModel cm)
  : width_(0), height_(0), channels_(0), data_(NULL), colorModel_(CM_None)
{
  Init(w, h, cm);
}

Image::Image(const Image &img)
  : width_(0), height_(0), channels_(0), data_(NULL), colorModel_(CM_None)
{
  *this = img;
}

Image::~Image()
{
  Release();
}

void Image::Init(int w, int h, ColorModel cm)
{
  // Check if size is valid
  if (w <= 0 || h <= 0 || cm == CM_None) {
    cerr << "Image::Init() : Invalid image size or color model!" << endl;
    Release();
    return;
  }
  // Allocate memory (release already allocated memory if needed)
  int channels = (cm == CM_Gray) ? 1 : 3;
  int numBytes = w * h * channels;
  if (data_ == NULL) {
    data_ = new unsigned char[numBytes];
  } else if (GetNumBytes() != numBytes) {
    delete[] data_;
    data_ = new unsigned char[numBytes];
  }
  width_ = w;
  height_ = h;
  channels_ = channels;
  colorModel_ = cm;
  memset(data_, 0, numBytes);
}

void Image::Clear(unsigned char value)
{
  if (data_ != NULL)
    memset(data_, value, GetNumBytes());
}

void Image::Clear(const Color &color)
{
  if (colorModel_ == CM_Gray) {
    Clear(color.red);
  } else if (data_ != NULL) {
    unsigned char *d = data_;
    for (int i = 0; i < width_*height_; i++, d += 3) {
      d[0] = color.red;
      d[1] = color.green;
      d[2] = color.blue;
    }
  }
}

void Image::Release()
{
  // Release allocated memory
  if (data_ != NULL)
    delete[] data_;
  // Reset image parameters
  width_ = 0;
  height_ = 0;
  channels_ = 0;
  data_ = NULL;
  colorModel_ = CM_None;
}

bool Image::IsEmpty() const
{
  return data_ == NULL;
}

int Image::GetWidth() const
{
  return width_;
}

int Image::GetHeight() const
{
  return height_;
}

void Image::GetDimensions(int &width, int &height) const
{
  width = width_;
  height = height_;
}

int Image::GetNumPixels() const
{
  return width_ * height_;
}

int Image::GetChannels() const
{
  return channels_;
}

int Image::GetNumBytes() const
{
  return width_ * height_ * channels_;
}

const unsigned char *Image::GetData() const
{
  return data_;
}

unsigned char *Image::GetData()
{
  return data_;
}

Image::ColorModel Image::GetColorModel() const
{
  return colorModel_;
}

Image& Image::operator=(const Image &src)
{
  if (src.data_ != NULL) {
    int numBytes = src.GetNumBytes();
    if (data_ == NULL) {
      data_ = new unsigned char[numBytes];
    } else if (GetNumBytes() != numBytes) {
      delete[] data_;
      data_ = new unsigned char[numBytes];
    }
    width_ = src.width_;
    height_ = src.height_;
    channels_ = src.channels_;
    colorModel_ = src.colorModel_;
    memcpy(data_, src.data_, numBytes);
  } else {
    Release();
  }
  return *this;
}

unsigned char Image::GetPixel(int x, int y, int ch, bool check) const
{
  if (check) {
    if (data_ == NULL) return 0;
    if (x < 0) x = 0; else if (x >= width_) x = width_-1;
    if (y < 0) y = 0; else if (y >= height_) y = height_-1;
  }
  return data_[(y*width_ + x)*channels_ + ch];
}

void Image::GetPixel(int x, int y, Color &color, bool check) const
{
  if (check) {
    if (data_ == NULL) return;
    if (x < 0) x = 0; else if (x >= width_) x = width_-1;
    if (y < 0) y = 0; else if (y >= height_) y = height_-1;
  }
  unsigned char *d = &data_[(y*width_ + x)*channels_];
  if (colorModel_ == CM_Gray)
    color.Set(*d, *d, *d);
  else
    color.Set(d[0], d[1], d[2]);
}

void Image::SetPixel(int x, int y, int ch, unsigned char value, bool check)
{
  if (check) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
  }
  data_[(y*width_ + x)*channels_ + ch] = value;
}

void Image::SetPixel(int x, int y, const Color &color, bool check)
{
  if (check) {
    if (x < 0 || x >= width_ || y < 0 || y >= height_) return;
  }
  unsigned char *d = &data_[(y*width_ + x)*channels_];
  if (colorModel_ == CM_Gray)
    *d = color.red; // set only 1-st channel for gray images
  else {
    d[0] = color.red;
    d[1] = color.green;
    d[2] = color.blue;
  }
}

