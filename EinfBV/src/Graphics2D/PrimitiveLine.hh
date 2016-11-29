#ifndef __PrimitiveLine_hh__
#define __PrimitiveLine_hh__

#include "PrimitiveBase.hh"

/** @class  PrimitiveLine
    @brief  Implements a 2d line primitive.
    @author esquivel
 */
class PrimitiveLine : public PrimitiveBase
{
public:

  /** @brief Initialize line primitive with given coordinates. */
  PrimitiveLine(const Color &color, const Float2D &start, const Float2D &end);

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~PrimitiveLine();

  /** @brief Draw line into given image using the Bresenham algorithm. */
  virtual void Draw(Image &image) const;

};

#endif // __PrimitiveLine_hh__
