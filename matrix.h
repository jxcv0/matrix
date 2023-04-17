#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>
#include <cassert>
#include <cmath>
#include <cfloat>
#include <cstddef>
#include <ostream>

bool feq(float a, float b) { return fabs(a - b) < FLT_EPSILON; }
float radians(const float degrees) { return degrees * (M_PI / 180.0f); }

template <std::size_t N, std::size_t M>
struct mat {
 public:
  mat() = default;

  static mat<N, M> identity() {
    assert(N == M);
    mat<N, N> m{};
    for (std::size_t n = 0; n < N; n++) {
      m[n][n] = 1;
    }
    return m;
  }

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
      if (!feq(v1[n], v2[n])) {
        return true;
      }
    }
    return false;
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

template <std::size_t N>
vec<N> normalize(const vec<N> &v) {
}

mat<4, 4> perspective(float fov, float aspect, float near, float far) {
  const float t = std::tan(fov / 2.0f);

  mat<4, 4> m{};
  m[0][0] = 1.0f / (aspect * t);
  m[1][1] = 1.0f / t;
  m[2][2] = -(far + near) / (far - near);
  m[2][3] = -1.0f;
  m[3][2] = -(2.0f * far * near) / (far - near);
  return m;
}

mat<4, 4> look_at(const vec<3> &eye, const vec<3> &ctr, const vec<3> &up) {

}

mat<4, 4> translate(const mat<4, 4> &m, const vec<3> &v);

mat<4, 4> rotate(const mat<4, 4> &m, const vec<3> &axis, const float angle);

#endif  // MATRIX_H_
