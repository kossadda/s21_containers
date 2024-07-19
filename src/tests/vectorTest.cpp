/**
 * @file vectorTest.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Vector containers method testing module
 * @version 1.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>

#include "./mainTest.h"

using s21_vector = s21::vector<int>;
using s21_iterator = s21::vector<int>::iterator;

using std_vector = std::vector<int>;
using std_iterator = std::vector<int>::iterator;

TEST(vectorIterator, pointerConstruct) {
  int arr[] = {1, 2, 3, 4, 5};
  std_vector vec{1, 2, 3, 4, 5};
  s21_iterator s21_it{arr};
  std_iterator std_it{vec.begin()};

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(s21_it + i) == *(std_it + i));
  }
}

TEST(vectorIterator, referenceConstruct) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};
  s21_iterator it_ref{it};

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_ref + i));
  }
}

TEST(vectorIterator, pointerAssignment) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it;
  it = arr;

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(arr + i));
  }
}

TEST(vectorIterator, iteratorAssignment) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};
  s21_iterator it_assign = it;

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_assign + i));
  }
}

TEST(vectorIterator, dereferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};

  int new_value = 11;
  *it = new_value;

  EXPECT_TRUE(*it == new_value);
}

TEST(vectorIterator, exceptDereferenceIterator) {
  s21_iterator it;

  EXPECT_THROW(*it = 5, std::invalid_argument);
}

TEST(vectorIterator, constDereferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};

  EXPECT_TRUE(*it == *arr);
}

TEST(vectorIterator, exceptConstDereferenceIterator) {
  s21_iterator it;

  EXPECT_THROW(*it, std::invalid_argument);
}

TEST(vectorIterator, prefixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};
  int check = *(++it);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(vectorIterator, postfixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};
  int check = *(it++);

  EXPECT_TRUE(check == *arr);
}

TEST(vectorIterator, prefixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};
  int check = *(--it);

  EXPECT_TRUE(check == *arr);
}

TEST(vectorIterator, postfixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};
  int check = *(it--);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(vectorIterator, sumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};

  EXPECT_TRUE(*(it + 1) == *(arr + 1));
}

TEST(vectorIterator, shortSumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr};

  it += 1;

  EXPECT_TRUE(*it == *(arr + 1));
}

TEST(vectorIterator, subShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};

  EXPECT_TRUE(*(it - 1) == *arr);
}

TEST(vectorIterator, shortSubShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};

  it -= 1;

  EXPECT_TRUE(*it == *arr);
}

TEST(vectorIterator, subDifferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator begin{arr};
  s21_iterator end{arr + 5};

  EXPECT_TRUE(end - begin == 5);
  EXPECT_TRUE(begin - end == 5);
}

TEST(vectorIterator, iteratorEqual) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};
  s21_iterator copy{it};

  EXPECT_TRUE(it == copy);
}

TEST(vectorIterator, iteratorNotEqual) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_iterator it{arr + 1};
  s21_iterator copy{it};

  EXPECT_FALSE(it != copy);
}

TEST(vector, numForAllocateConstruct) {
  s21_vector::size_type size{5};
  s21_vector s21_v(size);
  std_vector std_v(size);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, initListConstruct) {
  s21_vector::size_type size{5}, count{};
  s21_vector s21_v({11, 22, 33, 44, 55});
  std_vector std_v({11, 22, 33, 44, 55});

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (; count < size; count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, referenceConstruct) {
  s21_vector::size_type size{5}, count{};
  s21_vector v({11, 22, 33, 44, 55});
  s21_vector copy{v};

  EXPECT_TRUE(v.size() == copy.size());
  EXPECT_TRUE(v.capacity() == copy.capacity());

  for (; count < size; count++) {
    EXPECT_TRUE(v.at(count) == copy.at(count));
  }
}

TEST(vector, moveConstruct) {
  s21_vector::size_type size{5}, count{};
  int arr[]{11, 22, 33, 44, 55};
  s21_vector v({11, 22, 33, 44, 55});
  s21_vector moved = std::move(v);

  EXPECT_TRUE(moved.size() == size);
  EXPECT_TRUE(moved.capacity() == size);
  EXPECT_TRUE(!v.size());
  EXPECT_TRUE(!v.capacity());

  for (; count < size; count++) {
    EXPECT_TRUE(moved[count] == arr[count]);
  }
}

TEST(vector, iteratorAccess) {
  s21_vector v({11, 22, 33, 44, 55});

  EXPECT_TRUE(*v.begin() == 11);
  EXPECT_TRUE(*(v.end() - 1) == 55);
}

TEST(vector, emptyCheck) {
  s21_vector v;

  EXPECT_TRUE(v.empty());
  //////////////////////////////////////////////////////////
}

TEST(vector, maxSizeCheck) {
  s21_vector s21_v;
  std_vector std_v;

  EXPECT_TRUE(s21_v.max_size() == std_v.max_size());
}

TEST(vector, reserveMemory_1) {
  s21_vector s21_v;
  std_vector std_v;

  s21_v.reserve(5);
  std_v.reserve(5);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, reserveMemory_2) {
  s21_vector s21_v{1, 2, 3, 4, 5};
  std_vector std_v{1, 2, 3, 4, 5};

  s21_v.reserve(3);
  std_v.reserve(3);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, shrinkToFit) {
  s21_vector s21_v{1, 2, 3};
  std_vector std_v{1, 2, 3};

  s21_v.reserve(5);
  std_v.reserve(5);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, elementFrontBack) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  EXPECT_TRUE(s21_v.front() == std_v.front());
  EXPECT_TRUE(s21_v.back() == std_v.back());
}
