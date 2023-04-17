#ifndef MATRIX_H_
#define MATRIX_H_

#include <cstddef>
#include <array>
#include <cmath>

bool feq(float a, float b) {
  return fabs(a - b) < FLT_EPSILON;
}

template <std::size_t N, std::size_t M>
class mat {
 public:
  mat() = default;

  auto operator[](const int i) {
    return m_elem[i];
  }

  const auto operator[](const int i) const {
    return m_elem[i];
  }

  template <std::size_t K>
  friend mat<N, K> operator*(const mat<N, M> &m1, const mat<M, K> &m2) {
    mat<N, K> result;
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

 private:
  float m_elem[N][M];
};

template <std::size_t M>
using vec = mat<1, M>;

#endif  // MATRIX_H_
