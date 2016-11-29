#ifndef __PrimitivePoint_hh__
#define __PrimitivePoint_hh__

#include "PrimitiveBase.hh"

/** @class  PrimitivePoint
    @brief  Implements a 2d point primitive.
    @author esquivel
 */
class PrimitivePoint : public PrimitiveBase
{
public:

  /** @brief Initialize point primitive with given coordinates. */
  PrimitivePoint(const Color &color, const Float2D &pos);

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~PrimitivePoint();

  /** @brief Draw point into given image. */
  virtual void Draw(Image &image) const;

};

#endif // __PrimitivePoint_hh__
