#ifndef __PrimitiveBase_hh__
#define __PrimitiveBase_hh__

#include "Color.hh"
#include "Image.hh"
#include "Vectors.hh"
#include "AffineTransform.hh"
#include <vector>

/** @class  PrimitiveBase
    @brief  Abstract base class for 2d primitives like points, lines or polygons.
    @author esquivel
 */
class PrimitiveBase
{
public:

  /** @brief Destructor. Release dynamically allocated memory. */
  virtual ~PrimitiveBase();

  /** @brief Return the coordinates of the n-th point. */
  Float2D GetPoint(int n) const;

  /** @brief Set the coordinates for the n-th point. */
  void SetPoint(int n, const Float2D &p);

  /** @brief Returns the number of points in this primitive. */
  int GetNumPoints() const;

  /** @brief Return the color of this primitive. */
  Color GetColor() const;

  /** @brief Set the color of this primitive. */
  void SetColor(const Color &color);

  /** @brief Apply affine transformation to this primitive. */
  void ApplyTransform(const AffineTransform &T);

  /** @brief Draw primitive into given image. Implement this in derived classes. */
  virtual void Draw(Image &image) const = 0;

protected:

  /** @brief Initialize primitive with given color and number of points. */
  PrimitiveBase(const Color &color, int numPoints);

  /** @brief Stores color for this primitive. */
  Color color_;

private:

  /** @brief Stores 2d points for this primitive. */
  std::vector<Float2D> points_;

};

#endif // __PrimitiveBase_hh__
