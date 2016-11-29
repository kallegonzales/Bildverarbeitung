#ifndef __ColorConversion_hh__
#define __ColorConversion_hh__

#include "Image.hh"

/** @class ColorConversion
    @brief Abstract class containing static methods to convert images from
           one color model to another. Supports gray, RGB and HSV images.
    @author esquivel
 */
class ColorConversion
{
public:

  /** @brief Convert RGB image to gray image. */
  static void RGBToGray(const Image &src, Image &dst);

  /** @brief Convert gray image to RGB image. */
  static void GrayToRGB(const Image &src, Image &dst);

  /** @brief Convert RGB image to HSV image. */
  static void RGBToHSV(const Image &src, Image &dst);

  /** @brief Convert HSV image to RGB image. */
  static void HSVToRGB(const Image &src, Image &dst);

  /** @brief Convert HSV image to gray image (via RGB image). */
  static void HSVToGray(const Image &src, Image &dst);

  /** @brief Convert gray image to HSV image (via RGB image). */
  static void GrayToHSV(const Image &src, Image &dst);

private:

  /** @brief Constructor is private for pure static class. */
  ColorConversion();

};

#endif // __ColorConversion_hh__
