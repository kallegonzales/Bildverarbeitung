#ifndef __PrimitiveRectangle_hh__
#define __PrimitiveRectangle_hh__

#include "PrimitivePolygon.hh"

/** @class  PrimitiveRectangle
    @brief  Implements a 2d rectangle primitive.
    @author esquivel
 */
class PrimitiveRectangle : public PrimitivePolygon
{
public:

  /** @brief Initialize rectangle primitive with points. */
  PrimitiveRectangle(const Color &color, const Float2D &topLeft,
                     const Float2D &bottomRight);

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~PrimitiveRectangle();

};

#endif // __PrimitiveRectangle_hh__
