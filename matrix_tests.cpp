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
  auto i = mat<3, 3>::identity();
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

TEST(vector_tests, cross) {
  vec<3> v1{1.0f, 2.0f, 3.0f};
  vec<3> v2{1.0f, 5.0f, 7.0f};
  auto v = cross(v1, v2);
  ASSERT_FLOAT_EQ(v[0], -1.0f);
  ASSERT_FLOAT_EQ(v[1], -4.0f);
  ASSERT_FLOAT_EQ(v[2], 3.0f);
}

TEST(vector_tests, normalize) {
  vec<4> v{5, 2, -3};
  v = normalize(v);

  ASSERT_FLOAT_EQ(v[0], 0.8111071056538127f);
  ASSERT_FLOAT_EQ(v[1], 0.3244428422615251f);
  ASSERT_FLOAT_EQ(v[2], -0.4866642633922876f);
}

TEST(matrix_tests, perspective) {
  auto m = perspective(radians(45.0f), (800.0f / 600.0f), 0.1f, 100.0f);

  ASSERT_FLOAT_EQ(m[0][0], 1.81066f);
  ASSERT_FLOAT_EQ(m[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m[0][2], 0.0f);
  ASSERT_FLOAT_EQ(m[0][3], 0.0f);

  ASSERT_FLOAT_EQ(m[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m[1][1], 2.4142134f);
  ASSERT_FLOAT_EQ(m[1][2], 0.0f);
  ASSERT_FLOAT_EQ(m[1][3], 0.0f);

  ASSERT_FLOAT_EQ(m[2][0], 0.0f);
  ASSERT_FLOAT_EQ(m[2][1], 0.0f);
  ASSERT_FLOAT_EQ(m[2][2], -1.002002f);
  ASSERT_FLOAT_EQ(m[2][3], -1.0f);

  ASSERT_FLOAT_EQ(m[3][0], 0.0f);
  ASSERT_FLOAT_EQ(m[3][1], 0.0f);
  ASSERT_FLOAT_EQ(m[3][2], -0.2002002f);
  ASSERT_FLOAT_EQ(m[3][3], 0.0f);
}

TEST(matrix_tests, look_at) {
  vec<3> eye{3.0f, 3.0f, 3.0f};
  vec<3> ctr{1.0f, 0.0f, 1.0f};
  vec<3> c{eye[0] + ctr[0], eye[1] + ctr[1], eye[2] + ctr[2]};
  vec<3> up{0.0f, 1.0f, 0.0f};

  auto m = look_at(eye, c, up);
  ASSERT_FLOAT_EQ(m[0][0], -0.707107f);
  ASSERT_FLOAT_EQ(m[0][1], 0.0f);
  ASSERT_FLOAT_EQ(m[0][2], -0.707107f);
  ASSERT_FLOAT_EQ(m[0][3], 0.0f);
  ASSERT_FLOAT_EQ(m[1][0], 0.0f);
  ASSERT_FLOAT_EQ(m[1][1], 1.0f);
  ASSERT_FLOAT_EQ(m[1][2], -0.0f);
  ASSERT_FLOAT_EQ(m[1][3], 0.0f);
  ASSERT_FLOAT_EQ(m[2][0], 0.707107f);
  ASSERT_FLOAT_EQ(m[2][1], -0.0f);
  ASSERT_FLOAT_EQ(m[2][2], -0.707107f);
  ASSERT_FLOAT_EQ(m[2][3], 0.0f);
  ASSERT_FLOAT_EQ(m[3][0], -0.0f);
  ASSERT_FLOAT_EQ(m[3][1], -3.0f);
  ASSERT_FLOAT_EQ(m[3][2], 4.24264f);
  ASSERT_FLOAT_EQ(m[3][3], 1.0f);
}

TEST(matrix_tests, translate) {
  auto m = mat<4, 4>::identity();
  vec<3> v{0.1f, 0.1f, 0.1f};
  m = translate(m, v);
  ASSERT_FLOAT_EQ(m[3][0], 0.1f);
  ASSERT_FLOAT_EQ(m[3][1], 0.1f);
  ASSERT_FLOAT_EQ(m[3][2], 0.1f);
}

TEST(matrix_tests, rotate) {
  auto m = mat<4, 4>::identity();
  vec<3> v{0.0f, 1.0f, 0.0f};
  auto r = rotate(m, v, radians(30.0f));

  ASSERT_FLOAT_EQ(r[0][0], 0.86602539f);
  ASSERT_FLOAT_EQ(r[0][1], 0.0f);
  ASSERT_FLOAT_EQ(r[0][2], -0.5f);
  ASSERT_FLOAT_EQ(r[0][3], 0.0f);

  ASSERT_FLOAT_EQ(r[1][0], 0.0f);
  ASSERT_FLOAT_EQ(r[1][1], 1.0f);
  ASSERT_FLOAT_EQ(r[1][2], 0.0f);
  ASSERT_FLOAT_EQ(r[1][3], 0.0f);

  ASSERT_FLOAT_EQ(r[2][0], 0.5f);
  ASSERT_FLOAT_EQ(r[2][1], 0.0f);
  ASSERT_FLOAT_EQ(r[2][2], 0.86602539f);
  ASSERT_FLOAT_EQ(r[2][3], 0.0f);

  ASSERT_FLOAT_EQ(r[3][0], 0.0f);
  ASSERT_FLOAT_EQ(r[3][1], 0.0f);
  ASSERT_FLOAT_EQ(r[3][2], 0.0f);
  ASSERT_FLOAT_EQ(r[3][3], 1.0f);
}


