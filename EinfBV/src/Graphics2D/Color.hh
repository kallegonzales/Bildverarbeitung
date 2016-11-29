#ifndef __Color_hh__
#define __Color_hh__

/** @class  Color
    @brief  Implements a data structure for RGB colors.
    @author esquivel
 */
class Color
{
public:

  /** @brief Define common colors as static constants. */
  static const Color RED, GREEN, BLUE, CYAN, MAGENTA, YELLOW, BLACK, GRAY, WHITE;

  /** @brief Create black as default color. */
  Color()
  {
    red = green = blue = 0;
  }

  /** @brief Create a color with the given RGB values. */
  Color(unsigned char r, unsigned char g, unsigned char b)
  {
    red = r;
    green = g;
    blue = b;
  }

  /** @brief Set RGB values. */
  void Set(unsigned char r, unsigned char g, unsigned char b)
  {
    red = r;
    green = g;
    blue = b;
  }

  /** @brief RGB values stored in this color for public access */
  unsigned char red, green, blue;

};

#endif // __Color_hh__
