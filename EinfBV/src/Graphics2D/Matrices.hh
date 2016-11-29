#ifndef __Matrices_hh__
#define __Matrices_hh__

#include "Vectors.hh"

/** @class Float2x2
    @brief Implements data structure and operations for
           floating point 2x2 matrices.
 */
class Float2x2
{
public:
  Float2x2()
  {
    memset(data_, 0, 4 * sizeof(float));
  }
  Float2x2(const Float2x2 &M)
  {
    memcpy(data_, M.data_, 4 * sizeof(float));
  }
  Float2x2(const Float2D &col1, const Float2D &col2)
  {
    data_[0] = col1[0]; data_[1] = col2[0];
    data_[2] = col1[1]; data_[3] = col2[1];
  }
  Float2x2(float M11, float M12, float M21, float M22)
  {
    data_[0] = M11; data_[1] = M12;
    data_[2] = M21; data_[3] = M22;
  }
  Float2x2& operator=(const Float2x2 &M)
  {
    memcpy(data_, M.data_, 4 * sizeof(float));
    return *this;
  }
  Float2x2& operator+=(const Float2x2 &M)
  {
    data_[0] += M.data_[0]; data_[1] += M.data_[1];
    data_[2] += M.data_[2]; data_[3] += M.data_[3];
    return *this;
  }
  Float2x2& operator-=(const Float2x2 &M)
  {
    data_[0] -= M.data_[0]; data_[1] -= M.data_[1];
    data_[2] -= M.data_[2]; data_[3] -= M.data_[3];
    return *this;
  }
  Float2x2& operator*=(float s)
  {
    data_[0] *= s; data_[1] *= s;
    data_[2] *= s; data_[3] *= s;
    return *this;
  }
  Float2x2& operator/=(float s)
  {
    data_[0] /= s; data_[1] /= s;
    data_[2] /= s; data_[3] /= s;
    return *this;
  }
  Float2x2 operator-() const
  {
    return Float2x2(-data_[0], -data_[1], -data_[2], -data_[3]);
  }
  const float* operator[](const int i) const
  {
    return data_ + 2*i;
  }
  float* operator[](const int i)
  {
    return data_ + 2*i;
  }
  /** @brief Set this matrix as a copy of the given matrix. */
  void Set(const Float2x2 &M)
  {
    memcpy(data_, M.data_, 4 * sizeof(float));
  }
  /** @brief Set matrix elements to given values. */
  void Set(float M11, float M12, float M21, float M22)
  {
    data_[0] = M11; data_[1] = M12;
    data_[2] = M21; data_[3] = M22;
  }
  /** @brief Set all elements to zero. */
  void SetZero()
  {
    memset(data_, 0, 4 * sizeof(float));
  }
  /** @brief Make this the identity matrix. */
  void MakeIdentity()
  {
    memset(data_, 0, 4 * sizeof(float));
    data_[0] = data_[3] = 1.0f;
  }
  /** @brief Make this a diagonal matrix with given diagonal elements. */
  void MakeDiagonal(float M11, float M22) {
    memset(data_, 0, 4 * sizeof(float));
    data_[0] = M11; data_[3] = M22;
  }
  /** @brief Make this a diagonal matrix with given diagonal vector. */
  void MakeDiagonal(const Float2D &diag)
  {
    MakeDiagonal(diag[0], diag[1]);
  }
  /** @brief Make this the outer product matrix of given vectors. */
  void MakeOuterProduct(const Float2D &v, const Float2D &w)
  {
    data_[0] = v[0]*w[0]; data_[1] = v[0]*w[1];
    data_[2] = v[1]*w[0]; data_[3] = v[1]*w[1];
  }
  /** @brief Set columns of this matrix. */
  void SetColumns(const Float2D &col1, const Float2D &col2)
  {
    data_[0] = col1[0]; data_[1] = col2[0];
    data_[2] = col1[1]; data_[3] = col2[1];
  }
  /** @brief Set rows of this matrix. */
  void SetRows(const Float2D &row1, const Float2D &row2)
  {
    data_[0] = row1[0]; data_[1] = row1[1];
    data_[2] = row2[0]; data_[3] = row2[1];
  }
  /** @brief Get i-th column of this matrix. */
  Float2D GetColumn(int i) const
  {
    if (i == 0 || i == 1)
      return Float2D(data_[i], data_[i+2]);
    else
      return Float2D();
  }
  /** @brief Get i-th row of this matrix. */
  Float2D GetRow(int i) const
  {
    if (i == 0 || i == 1)
      return Float2D(data_[2*i], data_[2*i+1]);
    else
      return Float2D();
  }
  /** @brief Set i-th column of this matrix. */
  void SetColumn(int i, const Float2D &col)
  {
    if (i == 0 || i == 1) {
      data_[i] = col[0];
      data_[i+2] = col[1];
    }
  }
  /** @brief Set i-th row of this matrix. */
  void SetRow(int i, const Float2D &row)
  {
    if (i == 0 || i == 1) {
      data_[2*i] = row[0];
      data_[2*i+1] = row[1];
    }
  }
  /** @brief Copy data from given buffer of size 4. */
  void SetData(const float *data)
  {
    memcpy(data_, data, 4 * sizeof(float));
  }
  /** @brief Return read-only pointer to data. */
  const float* GetData() const
  {
    return data_;
  }
  /** @brief Multiply given matrix to right side of this matrix. */
  void Mult(const Float2x2 &M)
  {
    float Mres[4];
    const float (&M1)[4] = data_;
    const float (&M2)[4] = M.data_;
    Mres[0] = M1[0]*M2[0] + M1[1]*M2[2];
    Mres[1] = M1[0]*M2[1] + M1[1]*M2[3];
    Mres[2] = M1[2]*M2[0] + M1[3]*M2[2];
    Mres[3] = M1[2]*M2[1] + M1[3]*M2[3];
    memcpy(data_, Mres, 4 * sizeof(float));
  }
  /** @brief Multiply vector with this matrix and return result. */
  Float2D MultVec(const Float2D &v) const
  {
    return Float2D(data_[0]*v[0] + data_[1]*v[1],
                    data_[2]*v[0] + data_[3]*v[1]);
  }
  /** @brief Transpose this matrix. */
  void Transpose()
  {
    float tmp = data_[1]; data_[1] = data_[2]; data_[2] = tmp;
  }
  /** @brief Return transposed matrix. */
  Float2x2 GetTranspose() const
  {
    return Float2x2(data_[0], data_[2], data_[1], data_[3]);
  }
  /** @brief Return transposed matrix in MT. */
  void GetTranspose(Float2x2 &MT) const
  {
    MT.Set(data_[0], data_[2], data_[1], data_[3]);
  }
  /** @brief Return Frobenius norm of this matrix. */
  float GetNorm() const
  {
    return sqrtf(data_[0]*data_[0] + data_[1]*data_[1] +
                 data_[2]*data_[2] + data_[3]*data_[3]);
  }
  /** @brief Compute trace of this matrix. */
  float GetTrace() const
  {
    return data_[0] + data_[3];
  }
  /** @brief Compute determinant of this matrix. */
  float GetDeterminant() const
  {
    return data_[0]*data_[3] - data_[1]*data_[2];
  }
  /** @brief Invert this matrix.
      @return Returns if matrix inversion was successful. */
  bool Invert()
  {
    float det = data_[0]*data_[3] - data_[1]*data_[2];
    if (fabsf(det) < 1e-12f)
      return false;
    Set(data_[3] / det, -data_[1] / det, -data_[2] / det, data_[0] / det);
    return true;
  }
  /** @brief Return inverse of this matrix.
      @return Returns zero matrix if inversion failed, inverse otherwise. */
  Float2x2 GetInverse() const
  {
    Float2x2 invM(*this);
    if (!invM.Invert())
      return Float2x2();
    else
      return invM;
  }
  /** @brief Return inverse of this matrix.
      @return Returns if matrix inversion was successful. */
  bool GetInverse(Float2x2 &invM) const
  {
    invM.Set(*this);
    return invM.Invert();
  }
protected:
  /** @brief Stores matrix elements in row-wise order */
  float data_[4];
};

// Declarations of global operators for floating point 2x2 matrices
Float2x2 operator+(const Float2x2 &M1, const Float2x2 &M2);
Float2x2 operator-(const Float2x2 &M1, const Float2x2 &M2);
Float2x2 operator*(float s, const Float2x2& M);
Float2x2 operator/(const Float2x2& M, float s);
Float2x2 operator*(const Float2x2 &M1, const Float2x2 &M2);
Float2D operator*(const Float2x2 &M, const Float2D &v);
std::ostream& operator<<(std::ostream &os, const Float2x2& M);

#endif // __Matrices_hh__
