#ifndef __ImageIO_hh__
#define __ImageIO_hh__

#ifdef BUILD_WITH_FREEIMAGE
#  include <FreeImage.h>
#endif

#include "Image.hh"
#include <string>

/** @class ImageIO
    @brief Abstract class containing static methods to load and save images
           using the Portable PixMap format. Other image formats can be used
           with the FreeImage library optionally.

    @note This software uses the FreeImage open source image library.
          See http://freeimage.sourceforge.net for details.
          FreeImage is used under the FreeImage Public License, version 1.0.

    @author esquivel
 */
class ImageIO
{
public:

  /** @brief Load image from file.
      @return Returns true in case of success. */
  static bool Load(const std::string &filename, Image &image);

  /** @brief Save image to file.
      @return Returns true in case of success. */
  static bool Save(const std::string &filename, const Image &image);

  /** @brief Load image from Portable PixMap or Portable GrayMap file.
      @return Returns true in case of success. */
  static bool LoadPPM(const std::string &filename, Image &image);

  /** @brief Save image to Portable PixMap or Portable GrayMap file.
      @return Returns true in case of success. */
  static bool SavePPM(const std::string &filename, const Image &image);

#ifdef BUILD_WITH_FREEIMAGE

  /** @brief Load image from file using the FreeImage library.
      @return Returns true in case of success. */
  static bool LoadFreeImage(const std::string &filename, Image &image);

  /** @brief Save image to file using the FreeImage library.
      @return Returns true in case of success. */
  static bool SaveFreeImage(const std::string &filename, const Image &image);

#endif

private:

#ifdef BUILD_WITH_FREEIMAGE

  /** @brief Stores if FreeImage library has been initialized */
  static bool initFreeImageLib_;

  /** @brief Create FreeImage image from given image.
      @attention If pointer dst is not NULL, it is released first!
   */
  static void ConvertToFreeImage_(const Image &src, FIBITMAP* &dst);

  /** @brief Convert given FreeImage image to image.
      @attention If pointer src is NULL, an empty image dst is returned!
   */
  static void CreateFromFreeImage_(FIBITMAP* src, Image &dst);

#endif

  /** @brief Constructor is private for pure static class. */
  ImageIO();

};

#endif // __ImageIO_hh__
