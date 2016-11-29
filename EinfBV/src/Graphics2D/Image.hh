#ifndef __Image_hh__
#define __Image_hh__

#include "Color.hh"
#include <string>

/** @class Image
    @brief Simple multi-channel image implementation. Provides some basic
           methods to modify images, e.g. cropping, resizing and rescaling.
           In order to draw into images, access pixels with the SetPixel
           methods, or create primitives (see PrimitiveBase) for drawing.

    Image data is always stored as 1 byte per channel. The number of channels
    is either 1 for gray images, 3 for color images (RGB or HSV color model),
    and 0 for empty images. Image data is stored row-wise in chunks of 1 or 3
    bytes.

    @author esquivel
 */
class Image
{
public:

  /** @brief Specifies different color models for images. CM_Gray is always
             used for 1-channels images, CM_RGB and CM_HSV for 3-channel
             images. CM_None is set for uninitialized images. */
  enum ColorModel {
    CM_None, ///< Color model for uninitialized images
    CM_Gray, ///< Color model for 1-channel gray images
    CM_RGB,  ///< Color model for 3-channel RGB color images
    CM_HSV   ///< Color model for 3-channel HSV color images
  };

  /** @brief Create an empty image that must be initialized later. */
  Image();

  /** @brief Create an image with given size and color model. */
  Image(int w, int h, ColorModel cm);

  /** @brief Create an image as copy of another image. */
  Image(const Image &img);

  /** @brief Release memory used by image instance. */
  ~Image();

  /** @brief Initialize image to given size and color model and set all data
             values to zero. */
  void Init(int w, int h, ColorModel cm);

  /** @brief Set all image values to zero or the given value. */
  void Clear(unsigned char value = 0);

  /** @brief Set all image values to the given color. Assumes that the
             image is an RGB color image. */
  void Clear(const Color &color);

  /** @brief Release internal data and sets size to zero. */
  void Release();

  /** @brief Returns if image has empty data. */
  bool IsEmpty() const;

  /** @brief Returns image width in pixels. */
  int GetWidth() const;

  /** @brief Returns image height in pixels. */
  int GetHeight() const;

  /** @brief Returns image dimensions in pixels. */
  void GetDimensions(int &width, int &height) const;

  /** @brief Returns number of pixels in image. */
  int GetNumPixels() const;

  /** @brief Returns number of channels (3 for color images, 1 for gray
             images, and 0 for uninitialized images). */
  int GetChannels() const;

  /** @brief Returns image data size in bytes. */
  int GetNumBytes() const;

  /** @brief Returns read-only pointer to image data of size num_bytes. */
  const unsigned char *GetData() const;

  /** @brief Returns pointer to image data of size num_bytes. */
  unsigned char *GetData();

  /** @brief Return color model for this image (CM_RGB or CM_HSV for 3 channels
             CM_Gray for 1 channel, and CM_None for uninitialized images). */
  ColorModel GetColorModel() const;

  /** @brief Assignment creates a deep copy of the given image. */
  Image& operator=(const Image &src);

  /** @brief Get image value from channel ch at pixel (x, y).
             If check is set, the coordinates are checked for validity. */
  unsigned char GetPixel(int x, int y, int ch, bool check = false) const;

  /** @brief Get image values from all channels at pixel (x, y).
             If check is set, the coordinates are checked for validity.
             Assumes that the image is an RGB color image.  */
  void GetPixel(int x, int y, Color &color, bool check = false) const;

  /** @brief Set image value in channel ch at pixel (x, y).
             If check is set, the coordinates are checked for validity. */
  void SetPixel(int x, int y, int ch, unsigned char value, bool check = false);

  /** @brief Set image values in all channels at pixel (x, y).
             If check is set, the coordinates are checked for validity.
             Assumes that the image is an RGB color image. */
  void SetPixel(int x, int y, const Color &color, bool check = false);

private:

  int width_, height_, channels_;
  unsigned char *data_;
  ColorModel colorModel_;

};

#endif // __Image_hh__
