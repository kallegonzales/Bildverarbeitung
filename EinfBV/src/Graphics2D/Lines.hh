#ifndef __Lines_hh__
#define __Lines_hh__

#include "Vectors.hh"

/** @class FloatLine2D
    @brief Implements data structure and operations for 2d lines
           through points A, B with floating point coordinates.
 */
class FloatLine2D
{
public:
  FloatLine2D()
  {
  }
  FloatLine2D(const Float2D &X1, const Float2D &X2)
  {
    start_ = X1;
    end_ = X2;
  }
  FloatLine2D(const FloatLine2D &L)
  {
    start_ = L.start_;
    end_ = L.end_;
  }
  FloatLine2D& operator=(const FloatLine2D &L)
  {
    start_ = L.start_;
    end_ = L.end_;
    return *this;
  }
  /** @brief Set this line as a copy of the given line. */
  void Set(const FloatLine2D &L)
  {
    start_ = L.start_;
    end_ = L.end_;
  }
  /** @brief Set start and end point. */
  void Set(const Float2D &X1, const Float2D &X2)
  {
    start_ = X1;
    end_ = X2;
  }
  /** @brief Set start point. */
  void SetStart(const Float2D &X)
  {
    start_ = X;
  }
  /** @brief Set end point. */
  void SetEnd(const Float2D &X)
  {
    end_ = X;
  }
  /** @brief Get start point. */
  Float2D GetStart() const
  {
    return start_;
  }
  /** @brief Get end point. */
  Float2D GetEnd() const
  {
    return end_;
  }
  /** @brief Compute distance between start and end point. */
  float GetLength() const
  {
    return end_.GetDistance(start_);
  }
  /** @brief Return direction vector. */
  Float2D GetDirection() const
  {
    return end_ - start_;
  }

  /** @brief Compute slope-intersect form y = m*x + b for this line.
      @return Returns true if slope-intersect form was computed successfully. */
  bool GetSlopeIntersectForm(float &m, float &b) const;

  /** @brief Compute Hesse normal form n^T X = d for this line.
      @return Returns true if Hesse normal form was computed successfully. */
  bool GetHesseNormalForm(Float2D &n, float &d) const;

  /** @brief Compute intersection with given line L in point X.
      @return Returns true if intersection was computed successfully. */
  bool GetIntersection(const FloatLine2D &L, Float2D &X) const;

protected:
  /** @brief Store start point and end point */
  Float2D start_, end_;
};

#endif // __Lines_hh__
