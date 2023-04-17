#include <gtest/gtest.h>

#include "matrix.h"

TEST(matrix_tests, subscript) {
  mat<3, 3> m{0};
  m[0][1] = 10;
  ASSERT_FLOAT_EQ(m[0][1], 10);
  auto i = m[0][1];
  ASSERT_FLOAT_EQ(i, 10);
}

TEST(matrix_tests, equal) {
  mat<2, 2> m1;
  m1[0][0] = 10.0f;

  mat<2, 2> m3{{3,2,3,4}};
  ASSERT_TRUE(m1 == m2);
  ASSERT_FALSE(m1 == m3);
}

TEST(matrix_tests, dot) {
  mat<2, 3> b{{1, 2, 3, 4, 5, 6}};
  mat<3, 2> a{{1, 2, 3, 4, 5, 6}};
  auto c = a * b;

  mat<3, 3> r{{9, 12, 15, 19, 26, 33, 29, 33, 29, 40, 51}};
}
