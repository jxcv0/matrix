#ifndef MATRIX_H_
#define MATRIX_H_

#include <array>
#include <cassert>
#include <cfloat>
#include <cmath>
#include <cstddef>
#include <ostream>

bool feq(float a, float b) { return fabs(a - b) < FLT_EPSILON; }
float radians(const float degrees) { return degrees * (M_PI / 180.0f); }

template <std::size_t N, std::size_t M>
struct mat {
 public:
  mat() = default;
  mat(const mat<N, M> &) = default;

  static mat<N, M> identity() {
    static_assert(N == M);
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
  vec(const vec<N> &) = default;

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

  friend vec<3> operator*(const vec<N> &v1, const float f) {
    vec<3> result = v1;
    for (std::size_t n = 0; n < N; n++) {
      result[n] *= f;
    }
    return result;
  }

  friend vec<N> operator+(const vec<N> &v1, const vec<N> &v2) {
    vec<N> result;
    for (std::size_t n = 0; n < N; n++) {
      result[n] = v1[n] + v2[n];
    }
    return result;
  }

  friend vec<N> operator-(const vec<N> &v1, const vec<N> &v2) {
    vec<N> result;
    for (std::size_t n = 0; n < N; n++) {
      result[n] = v1[n] - v2[n];
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

vec<3> cross(const vec<3> &v1, const vec<3> &v2) {
  return {(v1[1] * v2[2]) - (v1[2] * v2[1]), (v1[2] * v2[0]) - (v1[0] * v2[2]),
          (v1[0] * v2[1]) - (v1[1] * v2[0])};
}

template <std::size_t N>
vec<N> normalize(const vec<N> &v) {
  float l = 0;
  for (std::size_t n = 0; n < N; n++) {
    l += (v[n] * v[n]);
  }
  l = std::sqrt(l);

  vec<N> w = v;
  w[0] /= l;
  w[1] /= l;
  w[2] /= l;
  return w;
}

mat<4, 4> perspective(const float fov, const float aspect, const float near,
                      const float far) {
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
  vec<3> f{ctr[0] - eye[0], ctr[1] - eye[1], ctr[2] - eye[2]};
  f = normalize(f);

  auto s = normalize(cross(f, up));
  auto u = cross(s, f);

  auto m = mat<4, 4>::identity();

  m[0][0] = s[0];
  m[1][0] = s[1];
  m[2][0] = s[2];

  m[0][1] = u[0];
  m[1][1] = u[1];
  m[2][1] = u[2];

  m[0][2] = -f[0];
  m[1][2] = -f[1];
  m[2][2] = -f[2];

  m[3][0] = -(s * eye);
  m[3][1] = -(u * eye);
  m[3][2] = f * eye;
  return m;
}

mat<4, 4> translate(const mat<4, 4> &m, const vec<3> &v) {
  mat<4, 4> res = m;
  res[3][0] += v[0];
  res[3][1] += v[1];
  res[3][2] += v[2];
  return res;
}

mat<4, 4> rotate(const mat<4, 4> &m, const vec<3> &axis, const float angle) {
  const float c = std::cos(angle);
  const float s = std::sin(angle);

  auto a = normalize(axis);

  mat<4, 4> rot{};
  rot[0][0] = c + (1.0f - c) * a[0] * a[0];
  rot[0][1] = (1.0f - c) * a[0] * a[1] + s * a[2];
  rot[0][2] = (1.0f - c) * a[0] * a[2] - s * a[1];
  rot[0][3] = 0.0f;

  rot[1][0] = (1.0f - c) * a[1] * a[0] - s * a[2];
  rot[1][1] = c + (1.0f - c) * a[1] * a[1];
  rot[1][2] = (1.0f - c) * a[1] * a[2] + s * a[0];
  rot[1][3] = 0.0f;

  rot[2][0] = (1.0f - c) * a[2] * a[0] + s * a[1];
  rot[2][1] = (1.0f - c) * a[2] * a[1] - s * a[0];
  rot[2][2] = c + (1.0f - c) * a[2] * a[2];
  rot[2][3] = 0.0f;

  rot[3][0] = 0.0f;
  rot[3][1] = 0.0f;
  rot[3][2] = 0.0f;
  rot[3][3] = 1.0f;

  return m * rot;
}

#endif  // MATRIX_H_
