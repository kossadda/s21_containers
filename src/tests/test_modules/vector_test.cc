/**
 * @file vector_test.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Vector containers method testing module
 * @version 1.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <vector>

#include "./../main_test.h"

using s21_vector = s21::vector<int>;
using s21_iterator = s21::vector<int>::const_iterator;

using std_vector = std::vector<int>;
using std_iterator = std::vector<int>::const_iterator;

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

  EXPECT_TRUE(*v.cbegin() == 11);
  EXPECT_TRUE(*(v.cend() - 1) == 55);
}

TEST(vector, atThrows) {
  s21_vector v({11, 22, 33, 44, 55});

  EXPECT_THROW(v.at(7), std::out_of_range);
}

TEST(vector, emptyCheck) {
  s21_vector v;

  EXPECT_TRUE(v.empty());

  v.insert(v.cbegin(), 1);

  EXPECT_FALSE(v.empty());
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

TEST(vector, reserveThrows) {
  s21_vector s21_v{1, 2, 3, 4, 5};

  EXPECT_THROW(s21_v.reserve(s21_v.max_size() + 1), std::length_error);
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

TEST(vector, clearElements) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.clear();
  std_v.clear();

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, insertOneElement) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.insert(s21_v.cbegin() + 2, 100);
  std_v.insert(std_v.cbegin() + 2, 100);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, insertMoreElements) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.insert(s21_v.cbegin() + 2, 111, 12);
  std_v.insert(std_v.cbegin() + 2, 12, 111);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, emplace) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  EXPECT_EQ(*s21_v.emplace(s21_v.cbegin() + 2, 12),
            *std_v.emplace(std_v.cbegin() + 2, 12));
  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, emplaceEmpty) {
  s21_vector s21_v;
  std_vector std_v;

  EXPECT_EQ(*s21_v.emplace(s21_v.cbegin(), 12),
            *std_v.emplace(std_v.cbegin(), 12));
  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, emplaceEnd) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  EXPECT_EQ(*s21_v.emplace(s21_v.cend(), 12), *std_v.emplace(std_v.cend(), 12));
  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, emplaceBack) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  EXPECT_EQ(s21_v.emplace_back(100), std_v.emplace_back(100));
  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, emplaceBackEmpty) {
  s21_vector s21_v;
  std_vector std_v;

  EXPECT_EQ(s21_v.emplace_back(100), std_v.emplace_back(100));
  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, insertThrows) {
  s21_vector s21_v{11, 22, 33, 44, 55};

  EXPECT_THROW(s21_v.insert(s21_v.cbegin() - 1, 5), std::out_of_range);
  EXPECT_THROW(s21_v.insert(s21_v.cbegin() + s21_v.size() + 1, 5),
               std::out_of_range);
}

TEST(vector, eraseMoreElement) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.erase(s21_v.cbegin() + 2, s21_v.cbegin() + 4);
  std_v.erase(std_v.cbegin() + 2, std_v.cbegin() + 4);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, eraseOneElement) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.erase(s21_v.cbegin() + 2);
  std_v.erase(std_v.cbegin() + 2);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, eraseMoreElements) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.erase(s21_v.cbegin() + 2, s21_v.cbegin() + 4);
  std_v.erase(std_v.cbegin() + 2, std_v.cbegin() + 4);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, eraseThrows) {
  s21_vector s21_v{11, 22, 33, 44, 55};

  EXPECT_THROW(s21_v.erase(s21_v.cbegin() - 1), std::range_error);
  EXPECT_THROW(s21_v.erase(s21_v.cbegin() - s21_v.size() + 1),
               std::range_error);
  EXPECT_THROW(s21_v.erase(s21_v.cbegin(), s21_v.cend() + 1), std::range_error);
  EXPECT_THROW(s21_v.erase(s21_v.cbegin(), s21_v.cend() - s21_v.size() - 1),
               std::range_error);
  EXPECT_THROW(s21_v.erase(s21_v.cend(), s21_v.cbegin()), std::range_error);
}

TEST(vector, pushBackElement_1) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.push_back(123);
  std_v.push_back(123);

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, pushBackElement_2) {
  s21_vector s21_v;
  std_vector std_v;

  for (s21_vector::size_type i = 0; i < 100; i++) {
    s21_v.push_back(i);
    std_v.push_back(i);
  }

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, pushBackElement_3) {
  s21_vector s21_v;
  std_vector std_v;

  s21_v.reserve(25);
  std_v.reserve(25);

  for (s21_vector::size_type i = 0; i < 26; i++) {
    s21_v.push_back(i);
    std_v.push_back(i);
  }

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, popBackElement) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  s21_v.pop_back();
  std_v.pop_back();

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());

  for (s21_vector::size_type count{}; count < s21_v.size(); count++) {
    EXPECT_TRUE(s21_v[count] == std_v[count]);
  }
}

TEST(vector, popBackUntilEmpty) {
  s21_vector s21_v{11, 22, 33, 44, 55};
  std_vector std_v{11, 22, 33, 44, 55};

  while (!s21_v.empty()) {
    s21_v.pop_back();
    std_v.pop_back();
  }

  EXPECT_TRUE(s21_v.size() == std_v.size());
  EXPECT_TRUE(s21_v.capacity() == std_v.capacity());
}

TEST(vector, swapElements) {
  s21_vector s21_v1{11, 22, 33, 44, 55};
  s21_vector s21_v2{66, 77, 88, 99};
  std_vector std_v1{11, 22, 33, 44, 55};
  std_vector std_v2{66, 77, 88, 99};

  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);

  EXPECT_TRUE(s21_v1.size() == std_v1.size());
  EXPECT_TRUE(s21_v2.size() == std_v2.size());
  EXPECT_TRUE(s21_v1.capacity() == std_v1.capacity());
  EXPECT_TRUE(s21_v2.capacity() == std_v2.capacity());

  for (s21_vector::size_type count{}; count < s21_v1.size(); count++) {
    EXPECT_TRUE(s21_v1[count] == std_v1[count]);
  }

  for (s21_vector::size_type count{}; count < s21_v2.size(); count++) {
    EXPECT_TRUE(s21_v2[count] == std_v2[count]);
  }
}

TEST(vector, swapEmptyWithNonEmpty) {
  s21_vector s21_v1{11, 22, 33, 44, 55};
  s21_vector s21_v2;
  std_vector std_v1{11, 22, 33, 44, 55};
  std_vector std_v2;

  s21_v1.swap(s21_v2);
  std_v1.swap(std_v2);

  EXPECT_TRUE(s21_v1.size() == std_v1.size());
  EXPECT_TRUE(s21_v2.size() == std_v2.size());
  EXPECT_TRUE(s21_v1.capacity() == std_v1.capacity());
  EXPECT_TRUE(s21_v2.capacity() == std_v2.capacity());

  for (s21_vector::size_type count{}; count < s21_v1.size(); count++) {
    EXPECT_TRUE(s21_v1[count] == std_v1[count]);
  }

  for (s21_vector::size_type count{}; count < s21_v2.size(); count++) {
    EXPECT_TRUE(s21_v2[count] == std_v2[count]);
  }
}

TEST(vector, assignVectors) {
  s21_vector s21_v1{11, 22, 33, 44, 55};
  s21_vector s21_v2 = s21_v1;

  EXPECT_TRUE(s21_v1.size() == s21_v2.size());
  EXPECT_TRUE(s21_v1.capacity() == s21_v2.capacity());

  for (s21_vector::size_type count{}; count < s21_v2.size(); count++) {
    EXPECT_TRUE(s21_v1[count] == s21_v2[count]);
  }
}

TEST(vectorIterator, referenceConstruct) {
  s21_vector s21_v1{1, 2, 3, 4, 5};
  s21_iterator it{s21_v1.begin()};
  s21_iterator it_ref{it};

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_ref + i));
  }
}

TEST(vectorIterator, iteratorAssignment) {
  s21_vector s21_v1{1, 2, 3, 4, 5};
  s21_iterator it{s21_v1.begin()};
  s21_iterator it_assign = it;

  for (int i = 0; i < 5; i++) {
    EXPECT_TRUE(*(it + i) == *(it_assign + i));
  }
}

TEST(vectorIterator, dereferenceIterator) {
  s21_vector v{1, 2, 3, 4, 5};
  s21_vector::iterator it{v.begin()};

  int new_value = 11;
  *it = new_value;

  EXPECT_TRUE(*it == new_value);
}

TEST(vectorIterator, exceptDereferenceIterator) {
  s21_vector::iterator it;

  EXPECT_THROW(*it = 5, std::invalid_argument);
}

TEST(vectorIterator, constDereferenceIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin()};

  EXPECT_TRUE(*it == *arr);
}

TEST(vectorIterator, exceptConstDereferenceIterator) {
  s21_iterator it;

  EXPECT_THROW(*it, std::invalid_argument);
}

TEST(vectorIterator, prefixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin()};
  int check = *(++it);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(vectorIterator, postfixIncrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin()};
  int check = *(it++);

  EXPECT_TRUE(check == *arr);
}

TEST(vectorIterator, prefixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};
  int check = *(--it);

  EXPECT_TRUE(check == *arr);
}

TEST(vectorIterator, postfixDecrement) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};
  int check = *(it--);

  EXPECT_TRUE(check == *(arr + 1));
}

TEST(vectorIterator, sumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin()};

  EXPECT_TRUE(*(it + 1) == *(arr + 1));
}

TEST(vectorIterator, shortSumShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin()};

  it += 1;

  EXPECT_TRUE(*it == *(arr + 1));
}

TEST(vectorIterator, subShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};

  EXPECT_TRUE(*(it - 1) == *arr);
}

TEST(vectorIterator, shortSubShiftIterator) {
  int arr[] = {1, 2, 3, 4, 5};
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};

  it -= 1;

  EXPECT_TRUE(*it == *arr);
}

TEST(vectorIterator, subDifferenceIterator) {
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator begin{v.begin()};
  s21_iterator end{v.begin() + 5};

  EXPECT_TRUE(end - begin == 5);
  EXPECT_TRUE(begin - end == 5);
}

TEST(vectorIterator, iteratorEqual) {
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};
  s21_iterator copy{it};

  EXPECT_TRUE(it == copy);
}

TEST(vectorIterator, iteratorNotEqual) {
  s21_vector v{1, 2, 3, 4, 5};
  s21_iterator it{v.begin() + 1};
  s21_iterator copy{it};

  EXPECT_FALSE(it != copy);
}
