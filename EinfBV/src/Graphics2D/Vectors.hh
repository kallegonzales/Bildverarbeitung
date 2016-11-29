#ifndef __Vectors_hh__
#define __Vectors_hh__

#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <iostream>

/** @class Float2D
    @brief Implements data structure and operations for
           floating point 2d vectors.
 */
class Float2D
{
public:
  Float2D()
  {
    data_[0] = data_[1] = 0.0f;
  }
  Float2D(float x, float y)
  {
    data_[0] = x; data_[1] = y;
  }
  Float2D(int x, int y)
  {
    data_[0] = (float)x; data_[1] = (float)y;
  }
  Float2D(const Float2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
  }
  Float2D& operator=(const Float2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
    return *this;
  }
  Float2D& operator+=(const Float2D &p)
  {
    data_[0] += p.data_[0]; data_[1] += p.data_[1];
    return *this;
  }
  Float2D& operator-=(const Float2D &p)
  {
    data_[0] -= p.data_[0]; data_[1] -= p.data_[1];
    return *this;
  }
  Float2D& operator*=(float s)
  {
    data_[0] *= s; data_[1] *= s;
    return *this;
  }
  Float2D& operator/=(float s)
  {
    data_[0] /= s; data_[1] /= s;
    return *this;
  }
  Float2D operator-() const
  {
    return Float2D(-data_[0], -data_[1]);
  }
  float operator[](const int i) const
  {
    return data_[i];
  }
  float& operator[](const int i)
  {
    return data_[i];
  }
  bool operator==(const Float2D &p) const
  {
    return ((data_[0] == p.data_[0]) && (data_[1] == p.data_[1]));
  }
  bool operator!=(const Float2D &p) const
  {
    return ! operator==(p);
  }
  /** @brief Copy data from given buffer. */
  void SetData(const float *data)
  {
    data_[0] = data[0]; data_[1] = data[1];
  }
  /** @brief Return read-only pointer to data. */
  const float* GetData() const
  {
    return data_;
  }
  /** @brief Set elements to given values. */
  void Set(float x, float y)
  {
    data_[0] = x; data_[1] = y;
  }
  /** @brief Set this vector as a copy of the given vector. */
  void Set(const Float2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
  }
  /** @brief Set all elements to zero. */
  void SetZero()
  {
    data_[0] = data_[1] = 0.0f;
  }
  /** @brief Compute L2 norm of this vector. */
  float GetNorm() const
  {
    return sqrtf(data_[0]*data_[0] + data_[1]*data_[1]);
  }
  /** @brief Compute distance to given vector. */
  float GetDistance(const Float2D &p) const
  {
    return Float2D(data_[0] - p.data_[0], data_[1] - p.data_[1]).GetNorm();
  }
  /** @brief Compute dot product between two vectors. */
  float DotProduct(const Float2D &p) const
  {
    return data_[0]*p.data_[0] + data_[1]*p.data_[1];
  }
protected:
  /** @brief Stores vector elements */
  float data_[2];
};

// Declarations of global operators for floating point 2d vectors
Float2D operator+(const Float2D& p1, const Float2D& p2);
Float2D operator-(const Float2D& p1, const Float2D& p2);
Float2D operator*(float s, const Float2D& p);
Float2D operator/(const Float2D& p, float s);
std::ostream& operator<<(std::ostream &os, const Float2D& p);


/** @class Int2D
    @brief Implements data structure and operations for
           integer 2d vectors.
 */
class Int2D
{
public:
  Int2D()
  {
    data_[0] = data_[1] = 0;
  }
  Int2D(int x, int y)
  {
    data_[0] = x; data_[1] = y;
  }
  Int2D(const Int2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
  }
  Int2D& operator=(const Int2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
    return *this;
  }
  Int2D& operator+=(const Int2D &p)
  {
    data_[0] += p.data_[0]; data_[1] += p.data_[1];
    return *this;
  }
  Int2D& operator-=(const Int2D &p)
  {
    data_[0] -= p.data_[0]; data_[1] -= p.data_[1];
    return *this;
  }
  Int2D& operator*=(int s)
  {
    data_[0] *= s; data_[1] *= s;
    return *this;
  }
  Int2D& operator/=(int s)
  {
    data_[0] /= s; data_[1] /= s;
    return *this;
  }
  Int2D operator-() const
  {
    return Int2D(-data_[0], -data_[1]);
  }
  int operator[](const int i) const
  {
    return data_[i];
  }
  int& operator[](const int i)
  {
    return data_[i];
  }
  bool operator==(const Int2D &p) const
  {
    return (data_[0] == p.data_[0]) && (data_[1] == p.data_[1]);
  }
  bool operator!=(const Int2D &p) const
  {
    return ! operator==(p);
  }
  /** @brief Copy data from given buffer. */
  void SetData(const int *data)
  {
    data_[0] = data[0]; data_[1] = data[1];
  }
  /** @brief Return read-only pointer to data. */
  const int* GetData() const
  {
    return data_;
  }
  /** @brief Set elements to given values. */
  void Set(int x, int y)
  {
    data_[0] = x; data_[1] = y;
  }
  /** @brief Set this vector as a copy of the given vector. */
  void Set(const Int2D &p)
  {
    data_[0] = p.data_[0]; data_[1] = p.data_[1];
  }
  /** @brief Set all elements to zero. */
  void SetZero()
  {
    data_[0] = data_[1] = 0;
  }
  /** @brief Compute dot product between two vectors. */
  int DotProduct(const Int2D &p) const
  {
    return data_[0]*p.data_[0] + data_[1]*p.data_[1];
  }
protected:
  /** @brief Stores vector elements */
  int data_[2];
};

// Declarations of global operators for integer 2d vectors
Int2D operator+(const Int2D& p1, const Int2D& p2);
Int2D operator-(const Int2D& p1, const Int2D& p2);
Int2D operator*(int s, const Int2D& p);
Int2D operator/(const Int2D& p, int s);
std::ostream& operator<<(std::ostream &os, const Int2D& p);

#endif // __Vectors_hh__
