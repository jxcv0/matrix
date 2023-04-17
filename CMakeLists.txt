cmake_minimum_required(VERSION 3.16)
project(matrix)

set(CMAKE_CXX_STANDARD 17)
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ggdb -Wall -Werror -Wextra -Wpedantic")

add_library(${PROJECT_NAME} STATIC matrix.h)
target_include_directories(${PROJECT_NAME} PUBLIC .)
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG v1.13.0
)
FetchContent_MakeAvailable(googletest)

include(CTest)

add_executable(matrix_tests matrix_tests.cpp)
target_link_libraries(matrix_tests gtest_main ${PROJECT_NAME})
add_test(NAME matrix_tests COMMAND matrix_tests)

