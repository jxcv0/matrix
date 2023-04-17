#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <cstddef>
#include <ostream>

#define IDENTITY_MAT4 1, 0, 0, 0, \
                      0, 1, 0, 0, \
                      0, 0, 1, 0, \
                      0, 0, 0, 1  \

#define IDENTITY_MAT3 1, 0, 0, \
                      0, 1, 0, \
                      0, 0, 1  \

bool feq(float a, float b) { return fabs(a - b) < FLT_EPSILON; }

template <std::size_t N, std::size_t M>
struct mat {
 public:
  mat() = default;

  auto &operator[](const std::size_t i) {
    assert(i < N);
    return m_elem[i];
  }

  const auto &operator[](const std::size_t i) const {
    assert(i < N);
    return m_elem[i];
  }

  template <std::size_t K>
  friend mat<N, K> operator*(const mat<N, M> &m1, const mat<M, K> &m2) {
    mat<N, K> result{};
    for (std::size_t n = 0; n < N; n++) {
      for (std::size_t m = 0; m < M; m++) {
        for (std::size_t k = 0; k < K; k++) {
          result[n][k] += m1[n][m] * m2[m][k];
        }
      }
    }
    return result;
  }

  friend bool operator==(const mat<N, M> &m1, const mat<N, M> &m2) {
    for (std::size_t n = 0; n < N; n++) {
      for (std::size_t m = 0; m < M; m++) {
        if (!feq(m1[m][n], m2[m][n])) {
          return false;
        }
      }
    }
    return true;
  }

  friend bool operator!=(const mat<N, M> &m1, const mat<N, M> &m2) {
    for (std::size_t n = 0; n < N; n++) {
      for (std::size_t m = 0; m < M; m++) {
        if (!feq(m1[m][n], m2[m][n])) {
          return true;
        }
      }
    }
    return false;
  }

  friend std::ostream &operator<<(std::ostream &os, const mat<N, M> &mat) {
    os << "{ ";
    for (std::size_t n = 0; n < N; n++) {
      os << "{ ";
      for (std::size_t m = 0; m < M; m++) {
        os << mat[n][m] << " ";
      }
      os << "} ";
    }
    os << "}";
    return os;
  }

  std::array<std::array<float, M>, N> m_elem;
};

template <std::size_t N>
struct vec {
 public:
  vec() = default;

  auto &operator[](const std::size_t i) {
    assert(i < N);
    return m_elem[i];
  }

  const auto &operator[](const std::size_t i) const {
    assert(i < N);
    return m_elem[i];
  }

  friend float operator*(const vec<N> &v1, const vec<N> &v2) {
    float result = 0;
    for (std::size_t n = 0; n < N; n++) {
      result += v1[n] * v2[n];
    }
    return result;
  }

  friend bool operator==(const vec<N> &v1, const vec<N> &v2) {
    for (std::size_t n = 0; n < N; n++) {
      if (!feq(v1[n], v2[n])) {
        return false;
      }
    }
    return true;
  }

  friend bool operator!=(const vec<N> &v1, const vec<N> &v2) {
    for (std::size_t n = 0; n < N; n++) {
      if (feq(v1[n], v2[n])) {
        return false;
      }
    }
    return true;
  }

  friend std::ostream &operator<<(std::ostream &os, const vec<N> &v) {
    os << "{ ";
    for (std::size_t n = 0; n < N; n++) {
      os << v[n] << " ";
    }
    os << "}";
    return os;
  }

  std::array<float, N> m_elem;
};

#endif  // MATRIX_H_
