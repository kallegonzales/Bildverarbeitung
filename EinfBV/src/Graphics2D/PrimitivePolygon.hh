#ifndef __PrimitivePolygon_hh__
#define __PrimitivePolygon_hh__

#include "PrimitiveBase.hh"

/** @class  PrimitivePolygon
    @brief  Implements a 2d polygon primitive.
    @author esquivel
 */
class PrimitivePolygon : public PrimitiveBase
{
public:

  /** @brief Initialize polygon primitive with given number of points. */
  PrimitivePolygon(const Color &color, int numPoints);

  /** @brief Initialize polygon primitive with given points. */
  PrimitivePolygon(const Color &color, const std::vector<Float2D> &points);

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~PrimitivePolygon();

  /** @brief Draw polygon into given image. */
  virtual void Draw(Image &image) const;

};

#endif // __PrimitivePolygon_hh__
