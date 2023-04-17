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
  ASSERT_FALSE(m1 != m2);
  m2[1][1] = -0.1f;
  ASSERT_FALSE(m1 == m2);
  ASSERT_TRUE(m1 != m2);
}

TEST(matrix_tests, product) {
  mat<3, 2> a{1, 2, 3, 4, 5, 6};
  mat<2, 3> b{1, 2, 3, 4, 5, 6};
  auto c = a * b;
  mat<3, 3> r{9, 12, 15, 19, 26, 33, 29, 40, 51};
  ASSERT_TRUE(c == r);
}

TEST(matrix_tests, identity) {
  mat<3, 3> i{IDENTITY_MAT3};
  mat<3, 2> a{1, 2, 3, 4, 5, 6};
  auto b = i * a;
  ASSERT_TRUE(b == a);
}

TEST(vector_tests, product) {
  vec<3> a{1, 2, 3};
  vec<3> b{3, 2, 1};
  auto c = a * b;
  ASSERT_FLOAT_EQ(c, 10);
}
