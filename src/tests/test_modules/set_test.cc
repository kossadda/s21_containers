/**
 * @file set_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Set methods testing module
 * @version 1.0
 * @date 2024-07-30
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <set>

#include "./../main_test.h"

using s21_set = s21::set<int>;
using std_set = std::set<int>;

void compare(s21_set s1, std_set s2) {
  auto s21_it = s1.begin();
  auto std_it = s2.begin();

  if (s1.size()) {
    for (; s21_it != s1.end(); s21_it++, std_it++) {
      EXPECT_EQ(*s21_it, *std_it);
    }
  }

  EXPECT_EQ(s1.size(), s2.size());
  EXPECT_EQ(s1.empty(), s2.empty());
}

TEST(set, defaultConstructor) {
  s21_set s21_s;
  std_set std_s;

  compare(s21_s, std_s);
}

TEST(set, initializerListConstructor) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  compare(s21_s, std_s);
}

TEST(set, copyConstructor) {
  s21_set s21_s1 = {1, 2, 3, 4, 5};
  s21_set s21_s2 = s21_s1;
  std_set std_s1 = {1, 2, 3, 4, 5};
  std_set std_s2 = std_s1;

  compare(s21_s2, std_s2);
}

TEST(set, moveConstructor) {
  s21_set s21_s1 = {1, 2, 3, 4, 5};
  s21_set s21_s2 = std::move(s21_s1);
  std_set std_s1 = {1, 2, 3, 4, 5};
  std_set std_s2 = std::move(std_s1);

  compare(s21_s2, std_s2);

  EXPECT_TRUE(s21_s1.empty());
  EXPECT_TRUE(std_s1.empty());
}

TEST(set, copyAssignmentOperator) {
  s21_set s21_s1 = {1, 2, 3, 4, 5};
  s21_set s21_s2;
  s21_s2 = s21_s1;
  std_set std_s1 = {1, 2, 3, 4, 5};
  std_set std_s2;
  std_s2 = std_s1;

  EXPECT_EQ(s21_s2.empty(), std_s2.empty());
  EXPECT_EQ(s21_s2.size(), std_s2.size());

  compare(s21_s2, std_s2);
}

TEST(set, moveAssignmentOperator) {
  s21_set s21_s1 = {1, 2, 3, 4, 5};
  s21_set s21_s2;
  s21_s2 = std::move(s21_s1);
  std_set std_s1 = {1, 2, 3, 4, 5};
  std_set std_s2;
  std_s2 = std::move(std_s1);

  compare(s21_s2, std_s2);

  EXPECT_EQ(s21_s1.empty(), std_s1.empty());
}

TEST(set, insert) {
  s21_set s21_s;
  std_set std_s;

  auto s21_result = s21_s.insert(1);
  auto std_result = std_s.insert(1);
  compare(s21_s, std_s);

  s21_result = s21_s.insert(2);
  std_result = std_s.insert(2);
  compare(s21_s, std_s);

  s21_result = s21_s.insert(1);
  std_result = std_s.insert(1);
  compare(s21_s, std_s);
}

TEST(set, emplace) {
  s21_set s21_m;
  std_set std_m;

  auto s21_result = s21_m.emplace(1);
  auto std_result = std_m.emplace(1);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(1);
  std_result = std_m.emplace(1);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(2);
  std_result = std_m.emplace(2);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(3);
  std_result = std_m.emplace(3);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(4);
  std_result = std_m.emplace(4);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(5);
  std_result = std_m.emplace(5);
  EXPECT_EQ(*s21_result.first, *std_result.first);
  EXPECT_EQ(s21_result.second, std_result.second);
  EXPECT_EQ(s21_m.size(), std_m.size());
}

TEST(set, erase) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  auto s21_it = s21_s.begin();
  auto std_it = std_s.begin();

  s21_s.erase(s21_it);
  std_s.erase(std_it);

  compare(s21_s, std_s);

  s21_it = s21_s.begin();
  ++s21_it;
  std_it = std_s.begin();
  ++std_it;

  auto s21_check = s21_s.erase(s21_it);
  auto std_check = std_s.erase(std_it);

  EXPECT_EQ(*s21_check, *std_check);

  compare(s21_s, std_s);
}

TEST(set, eraseAll) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  while (s21_s.size()) {
    s21_s.erase(s21_s.begin());
    std_s.erase(std_s.begin());
  }

  EXPECT_EQ(s21_s.size(), std_s.size());
}

TEST(set, eraseRange_1) {
  s21_set s21_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};
  std_set std_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};

  auto s21_it_begin = s21_s.begin();
  ++s21_it_begin;
  ++s21_it_begin;
  auto s21_it_end = s21_it_begin;
  ++s21_it_end;
  ++s21_it_end;

  auto std_it_begin = std_s.begin();
  ++std_it_begin;
  ++std_it_begin;
  auto std_it_end = std_it_begin;
  ++std_it_end;
  ++std_it_end;

  auto s21_it = s21_s.erase(s21_it_begin, s21_it_end);
  auto std_it = std_s.erase(std_it_begin, std_it_end);

  EXPECT_EQ(*s21_it, *std_it);

  compare(s21_s, std_s);
}

TEST(set, eraseRange_2) {
  s21_set s21_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};
  std_set std_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};

  auto s21_it_begin = s21_s.begin();
  auto s21_it_end = s21_it_begin;
  ++s21_it_end;

  auto std_it_begin = std_s.begin();
  auto std_it_end = std_it_begin;
  ++std_it_end;

  auto s21_it = s21_s.erase(s21_it_begin, s21_it_end);
  auto std_it = std_s.erase(std_it_begin, std_it_end);

  EXPECT_EQ(*s21_it, *std_it);

  compare(s21_s, std_s);
}

TEST(set, eraseRange_3) {
  s21_set s21_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};
  std_set std_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};

  auto s21_it_begin = s21_s.end();
  --s21_it_begin;
  auto s21_it_end = s21_s.end();

  auto std_it_begin = std_s.end();
  --std_it_begin;
  auto std_it_end = std_s.end();

  s21_s.erase(s21_it_begin, s21_it_end);
  std_s.erase(std_it_begin, std_it_end);

  compare(s21_s, std_s);
}

TEST(set, eraseRange_4) {
  s21_set s21_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};
  std_set std_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};

  auto s21_it_begin = s21_s.begin();
  auto s21_it_end = s21_s.end();

  auto std_it_begin = std_s.begin();
  auto std_it_end = std_s.end();

  s21_s.erase(s21_it_begin, s21_it_end);
  std_s.erase(std_it_begin, std_it_end);

  compare(s21_s, std_s);
}

TEST(set, eraseRange_5) {
  s21_set s21_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};
  std_set std_s = {11, 256, 31, 44, 15, 1, 7, 111, 22, 222};

  auto s21_it_begin = s21_s.begin();

  auto std_it_begin = std_s.begin();

  s21_s.erase(s21_it_begin, s21_it_begin);
  std_s.erase(std_it_begin, std_it_begin);

  compare(s21_s, std_s);
}

TEST(set, clear) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  s21_s.clear();
  std_s.clear();
  compare(s21_s, std_s);
}

TEST(set, find) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  compare(s21_s, std_s);
  EXPECT_EQ(s21_s.find(6), s21_s.end());
  EXPECT_EQ(std_s.find(6), std_s.end());
}

TEST(set, contains) {
  s21_set s21_s = {1, 2, 3, 4, 5};
  std_set std_s = {1, 2, 3, 4, 5};

  compare(s21_s, std_s);
  EXPECT_FALSE(s21_s.conatains(6));
}

TEST(set, swap) {
  s21_set s21_s1 = {1, 2, 3};
  s21_set s21_s2 = {4, 5, 6};
  std_set std_s1 = {1, 2, 3};
  std_set std_s2 = {4, 5, 6};

  s21_s1.swap(s21_s2);
  std_s1.swap(std_s2);
  compare(s21_s1, std_s1);
  compare(s21_s2, std_s2);
}

TEST(set, merge_1) {
  s21_set s21_s1 = {1, 2, 3};
  s21_set s21_s2 = {4, 5, 6};
  std_set std_s1 = {1, 2, 3};
  std_set std_s2 = {4, 5, 6};

  s21_s1.merge(s21_s2);
  std_s1.merge(std_s2);

  compare(s21_s1, std_s1);
  compare(s21_s2, std_s2);
}

TEST(set, merge_2) {
  s21_set s21_s1 = {1, 2, 3, 10, 20, 30, 40, 50};
  s21_set s21_s2 = {4, 5, 6, 10, 20, 30, 60, 70};
  std_set std_s1 = {1, 2, 3, 10, 20, 30, 40, 50};
  std_set std_s2 = {4, 5, 6, 10, 20, 30, 60, 70};

  s21_s1.merge(s21_s2);
  std_s1.merge(std_s2);

  compare(s21_s1, std_s1);
  compare(s21_s2, std_s2);
}

TEST(setIterator, easyIterate) {
  s21_set s{1, 2, 3, 4, 5};
  int res[] = {1, 2, 3, 4, 5};

  int count = 0;
  for (auto i : s) {
    EXPECT_EQ(i, res[count++]);
  }
}

TEST(setIterator, checkConstructors) {
  s21_set s{1, 2, 3, 4, 5};

  s21_set::iterator it1{s.begin() + 1};
  s21_set::iterator it2{s.begin()++};
  s21_set::iterator it3{s.begin()--};
  s21_set::iterator it4{++s.begin()};
  s21_set::iterator it5{--it1};

  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*(it1 + 1), *it4);
  EXPECT_EQ(*it1, *it5);
}

TEST(setIterator, checkConstructorsToIterator_1) {
  s21_set s{1, 2, 3, 4, 5};

  s21_set::const_iterator it1{s.begin() + 1};
  s21_set::const_iterator it2{s.begin()++};
  s21_set::const_iterator it3{s.begin()--};
  s21_set::const_iterator it4{++s.begin()};
  s21_set::const_iterator it5{--it1};

  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*(it1 + 1), *it4);
  EXPECT_EQ(*it1, *it5);
}

TEST(setIterator, checkConstructorsToIterator_2) {
  s21_set s{1, 2, 3, 4, 5};

  s21_set::const_iterator it1{s.cbegin() + 1};
  s21_set::const_iterator it2{s.cbegin()++};
  s21_set::const_iterator it3{s.cbegin()--};
  s21_set::const_iterator it4{++s.cbegin()};
  s21_set::const_iterator it5{--it1};

  EXPECT_EQ(*it1, *it2);
  EXPECT_EQ(*it1, *it3);
  EXPECT_EQ(*(it1 + 1), *it4);
  EXPECT_EQ(*it1, *it5);
}

TEST(setIterator, checkOperators) {
  s21_set s{1, 2, 3, 4, 5};
  std_set ss{1, 2, 3, 4, 5};

  EXPECT_EQ(*s.begin(), *(s.end() - 5));
  EXPECT_EQ(*(s.begin() + 5), *s.end());
  EXPECT_EQ(*s.cbegin(), *(s.cend() - 5));
  EXPECT_EQ(*(s.cbegin() + 5), *s.cend());
}
