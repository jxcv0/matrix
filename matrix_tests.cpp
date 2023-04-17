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
  mat<2, 2> m1{1, 2, 3, 4};
  mat<2, 2> m2{1, 2, 3, 4};
  ASSERT_TRUE(m1 == m2);
  m2[1][1] = -0.1f;
  ASSERT_FALSE(m1 == m2);
}

TEST(matrix_tests, dot) {
  mat<3, 2> a{1, 2, 3, 4, 5, 6};
  mat<2, 3> b{1, 2, 3, 4, 5, 6};
  auto c = a * b;
  mat<3, 3> r{9, 12, 15, 19, 26, 33, 29, 40, 51};

  ASSERT_TRUE(c == r);
}
