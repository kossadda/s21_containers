/**
 * @file vectorTest.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief vector containers method testing module
 * @version 1.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./mainTest.h"

using iter = container::vector<int>::iterator;

TEST(iterator, pointerConstruct) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(arr + i));
  }
}

TEST(iterator, iteratorRefConstruct) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};
  iter it_ref{it};

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_ref + i));
  }
}

TEST(iterator, pointerAssignment) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it;
  it = arr;

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(arr + i));
  }
}

TEST(iterator, iteratorAssignment) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};
  iter it_assign = it;

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_assign + i));
  }
}

TEST(iterator, dereferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};

  int new_value = 11;
  *it = new_value;

  EXPECT_TRUE(*it == new_value);
}

TEST(iterator, exceptDereferenceIterator) {
  iter it;

  EXPECT_THROW(*it = 5, std::invalid_argument);
}

TEST(iterator, constDereferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};

  EXPECT_TRUE(*it == *arr);
}

TEST(iterator, exceptConstDereferenceIterator) {
  iter it;

  EXPECT_THROW(*it, std::invalid_argument);
}

TEST(iterator, prefixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};
  int check = *(++it);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(iterator, postfixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};
  int check = *(it++);

  EXPECT_TRUE(check == *arr);
}

TEST(iterator, prefixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};
  int check = *(--it);

  EXPECT_TRUE(check == *arr);
}

TEST(iterator, postfixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};
  int check = *(it--);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(iterator, sumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};

  EXPECT_TRUE(*(it + 1) == *(arr + 1));
}

TEST(iterator, shortSumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr};

  it += 1;

  EXPECT_TRUE(*it == *(arr + 1));
}

TEST(iterator, subShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};

  EXPECT_TRUE(*(it - 1) == *arr);
}

TEST(iterator, shortSubShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};

  it -= 1;

  EXPECT_TRUE(*it == *arr);
}

TEST(iterator, subDifferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  iter begin{arr};
  iter end{arr + 5};

  EXPECT_TRUE(end - begin == 5);
  EXPECT_TRUE(begin - end == 5);
}

TEST(iterator, iteratorEqual) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};
  iter copy{it};

  EXPECT_TRUE(it == copy);
}

TEST(iterator, iteratorNotEqual) {
  int arr[] = {1, 2, 3, 4, 5};
  iter it{arr + 1};
  iter copy{it};

  EXPECT_FALSE(it != copy);
}