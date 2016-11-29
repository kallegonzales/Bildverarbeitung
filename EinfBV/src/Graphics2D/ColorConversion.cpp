#include "ColorConversion.hh"
#include <iostream>
#include <cmath>

using namespace std;

ColorConversion::ColorConversion()
{
}

void ColorConversion::RGBToGray(const Image &src, Image &dst)
{
  // TODO : Implement this method in exercise 5
}

void ColorConversion::GrayToRGB(const Image &src, Image &dst)
{
  // TODO : Implement this method in exercise 5
}

void ColorConversion::RGBToHSV(const Image &src, Image &dst)
{
  // TODO : Implement this method in exercise 5
}

void ColorConversion::HSVToRGB(const Image &src, Image &dst)
{
  // TODO : Implement this method in exercise 5
}

void ColorConversion::HSVToGray(const Image &src, Image &dst)
{
  Image tmp;
  HSVToRGB(src, tmp);
  RGBToGray(tmp, dst);
}

void ColorConversion::GrayToHSV(const Image &src, Image &dst)
{
  Image tmp;
  GrayToRGB(src, tmp);
  RGBToHSV(tmp, dst);
}

