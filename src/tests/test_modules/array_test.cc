/**
 * @file array_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the array class
 * @version 1.0
 * @date 2024-08-05
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <array>

#include "../../s21_containers.h"
#include "../main_test.h"

template <typename T, std::size_t N>
static bool compare_arrays(std::array<T, N> std_array,
                           s21::array<T, N> s21_array) {
  if (std_array.size() != s21_array.size()) {
    return false;
  }

  for (std::size_t i = 0; i < N; ++i) {
    if (std_array[i] != s21_array[i]) {
      return false;
    }
  }

  return true;
}

TEST(ArrayTest, DefaultConstructor) {
  s21::array<int, 15> arr_2;

  for (std::size_t i = 0; i < 15; ++i) {
    EXPECT_EQ(arr_2[i], 0);
  }
}

TEST(ArrayTest, CopyConstructor) {
  std::array<int, 5> std_original{1, 2, 3, 4, 5};
  s21::array<int, 5> s21_original{1, 2, 3, 4, 5};

  std::array<int, 5> std_copy(std_original);
  s21::array<int, 5> s21_copy(s21_original);

  EXPECT_TRUE(compare_arrays(std_copy, s21_copy));
}

TEST(ArrayTest, MoveConstructor) {
  std::array<int, 5> std_original{1, 2, 3, 4, 5};
  s21::array<int, 5> s21_original{1, 2, 3, 4, 5};

  std::array<int, 5> std_move(std::move(std_original));
  s21::array<int, 5> s21_move(std::move(s21_original));

  EXPECT_TRUE(compare_arrays(std_move, s21_move));
}

TEST(ArrayTest, MoveConstructorFail1) {
  std::array<int, 6> std_original{1, 2, 3, 4, 5, 6};
  s21::array<int, 6> s21_original{1, 2, 3, 4, 5};

  std::array<int, 6> std_move(std::move(std_original));
  s21::array<int, 6> s21_move(std::move(s21_original));

  EXPECT_FALSE(compare_arrays(std_move, s21_move));
}

TEST(ArrayTest, At1) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};

  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_EQ(arr.at(4), 5);
  EXPECT_EQ(arr.size(), 5);
}

TEST(ArrayTest, At2) {
  s21::array<int, 10> arr{-20, 10, 14, -2, 3, 0, 2, 8};

  EXPECT_EQ(arr.at(0), -20);
  EXPECT_EQ(arr.at(1), 10);
  EXPECT_EQ(arr.at(2), 14);
  EXPECT_EQ(arr.at(3), -2);
  EXPECT_EQ(arr.at(4), 3);
  EXPECT_EQ(arr.at(5), 0);
  EXPECT_EQ(arr.at(6), 2);
  EXPECT_EQ(arr.at(7), 8);
  EXPECT_EQ(arr.at(8), 0);
  EXPECT_EQ(arr.at(9), 0);
}

TEST(ArrayTest, AtFail1) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};

  EXPECT_EQ(arr.at(0), 1);
  EXPECT_EQ(arr.at(1), 2);
  EXPECT_EQ(arr.at(2), 3);
  EXPECT_EQ(arr.at(3), 4);
  EXPECT_NE(arr.at(4), 6);
}

TEST(ArrayTest, AtFail2) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};

  EXPECT_THROW(arr.at(5), std::out_of_range);
}

TEST(ArrayTest, OperatorBrackets) {
  s21::array<int, 5> arr{1, 2, 3, 4, 5};

  EXPECT_EQ(arr[0], 1);
  EXPECT_EQ(arr[1], 2);
  EXPECT_EQ(arr[2], 3);
  EXPECT_EQ(arr[3], 4);
  EXPECT_EQ(arr[4], 5);
}

TEST(ArrayTest, Front1) {
  s21::array<int, 5> arr{19, 2, 3, 4, 5};

  EXPECT_EQ(arr.front(), 19);
}

TEST(ArrayTest, Front2) {
  s21::array<int, 5> arr{19, 2, 3, 4, 5};

  EXPECT_EQ(arr.front() = 6, 6);
  EXPECT_EQ(arr[0], 6);
}

TEST(ArrayTest, Back1) {
  s21::array<int, 5> arr{19, 2, 3, 4, 5};

  EXPECT_EQ(arr.back(), 5);
}

TEST(ArrayTest, Back2) {
  s21::array<int, 5> arr{19, 2, 3, 4, 5};

  EXPECT_EQ(arr.back() = 10, 10);
  EXPECT_EQ(arr[4], 10);
}

TEST(ArrayTest, Data1) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  EXPECT_EQ(*(arr.data()), 20);
}

TEST(ArrayTest, Data2) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  EXPECT_EQ(*(arr.data()) = 3, 3);
}

TEST(ArrayTest, Begin1) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.begin();

  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ArrayTest, Begin2) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.begin();

  *it = 5;
  EXPECT_EQ(*it, 5);
  ++it;
  *it = 500;
  EXPECT_EQ(*it, 500);
  ++it;
  *it = 20;
  EXPECT_EQ(*it, 20);
  ++it;
  *it = 10;
  EXPECT_EQ(*it, 10);
}

TEST(ArrayTest, End1) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.end();
  --it;
  EXPECT_EQ(*it, 0);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, End2) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.end();
  --it;
  *it = 10;
  EXPECT_EQ(*it, 10);
  --it;
  *it = 20;
  EXPECT_EQ(*it, 20);
  --it;
  *it = 300;
  EXPECT_EQ(*it, 300);
  --it;
  *it = 100;
  EXPECT_EQ(*it, 100);
  --it;
  *it = 213;
  EXPECT_EQ(*it, 213);
}

TEST(ArrayTest, Cbegin) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.begin();

  EXPECT_EQ(*it, 20);
  ++it;
  EXPECT_EQ(*it, 1);
  ++it;
  EXPECT_EQ(*it, 2);
  ++it;
  EXPECT_EQ(*it, 3);
}

TEST(ArrayTest, Cend) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  auto it = arr.end();
  --it;
  EXPECT_EQ(*it, 0);
  --it;
  EXPECT_EQ(*it, 3);
  --it;
  EXPECT_EQ(*it, 2);
  --it;
  EXPECT_EQ(*it, 1);
  --it;
  EXPECT_EQ(*it, 20);
}

TEST(ArrayTest, Empty) {
  s21::array<int, 5> arr{20, 1, 2, 3};

  EXPECT_FALSE(arr.empty());
}

TEST(ArrayTest, MaxSize) {
  std::array<int, 5> arr_1{20, 1, 2, 3};
  s21::array<int, 5> arr_2{20, 1, 2, 3};

  EXPECT_EQ(arr_1.max_size(), arr_2.max_size());
}

TEST(ArrayTest, Swap) {
  std::array<int, 5> original_1{0, 1, 2, 3, 4};
  s21::array<int, 5> original_2{0, 1, 2, 3, 4};

  std::array<int, 5> arr_1{4, 3, 2, 1, 0};
  s21::array<int, 5> arr_2{4, 3, 2, 1, 0};

  arr_1.swap(original_1);
  arr_2.swap(original_2);

  EXPECT_EQ(arr_1[0], 0);
  EXPECT_EQ(arr_1[1], 1);
  EXPECT_EQ(arr_1[2], 2);
  EXPECT_EQ(arr_1[3], 3);
  EXPECT_EQ(arr_1[4], 4);

  EXPECT_EQ(arr_2[4], 4);
  EXPECT_EQ(arr_2[3], 3);
  EXPECT_EQ(arr_2[2], 2);
  EXPECT_EQ(arr_2[1], 1);
  EXPECT_EQ(arr_2[0], 0);
}
