#ifndef __AffineTransform_hh__
#define __AffineTransform_hh__

#include "Vectors.hh"
#include "Matrices.hh"

/** @class  AffineTransform
    @brief  Base class for 2d affine transformations like rotation,
            translation, skew or scaling. Affine transformations are
            described by a 2x2 matrix A and 2d vector b, defining the
            homogeneous matrix T = [ A b ; 0 0 1]. A 2d vector X is
            transformed to A*X + b (in homogeneous form T * [X; 1]).
    @author esquivel
 */
class AffineTransform
{
public:

  /** @brief Create an affine transformation representing identity. */
  AffineTransform();

  /** @brief Create an affine transformation with the given linear part A
             and translational part b. */
  AffineTransform(const Float2x2 &mat, const Float2D &vec);

  /** @brief Transform the given 2d point. */
  void Transform(Float2D &X) const;

  /** @brief Concatenate the given affine transformations T1 and T2 and
             returns the result T. In terms of matrices, T = T1 * T2. */
  static AffineTransform Concatenate(const AffineTransform &T1,
                                     const AffineTransform &T2);

  /** @brief Invert this affine transformation.
      @return Returns if inversion was successful. */
  bool Invert();

  /** @brief Make this the identity transformation. */
  void MakeIdentity();

  /** @brief Make this a rotation with given rotation angle. */
  void MakeRotation(float angle);

  /** @brief Make this a translation with given translation vector. */
  void MakeTranslation(float tx, float ty);

  /** @brief Make this a scaling transformation with given scaling factors. */
  void MakeScaling(float sx, float sy);

  /** @brief Make this a shearing transformation with given shearing values. */
  void MakeShearing(float sx, float sy);

  /** @brief Stores linear part of affine transformation. */
  Float2x2 A;

  /** @brief Stores translational part of affine transformation. */
  Float2D b;

};
#endif // __AffineTransform_hh__
