/**
 * @file multiset_test.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Multiset methods testing module
 * @version 1.0
 * @date 2024-08-02
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <set>

#include "./../main_test.h"

using s21_multiset = s21::multiset<int>;
using std_multiset = std::multiset<int>;

void compare(s21_multiset ms1, std_multiset ms2) {
  auto ms21_it = ms1.begin();
  auto ms_std_it = ms2.begin();

  if (ms1.size()) {
    for (; ms21_it != ms1.end(); ms21_it++, ms_std_it++) {
      EXPECT_EQ(*ms21_it, *ms_std_it);
    }
  }

  EXPECT_EQ(ms1.size(), ms2.size());
  EXPECT_EQ(ms1.empty(), ms2.empty());
}

TEST(multiset, defaultConstructor) {
  s21_multiset ms1;
  std_multiset ms2;

  compare(ms1, ms2);
}

TEST(multiset, initializerListConstructor) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms2 = {1, 2, 3, 4, 5, 1, 2, 3};

  compare(ms1, ms2);
}

TEST(multiset, copyConstructor) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  s21_multiset ms2 = ms1;
  std_multiset ms_std1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std2 = ms_std1;

  compare(ms2, ms_std2);
}

TEST(multiset, moveConstructor) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  s21_multiset ms2 = std::move(ms1);
  std_multiset ms_std1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std2 = std::move(ms_std1);

  compare(ms2, ms_std2);

  EXPECT_TRUE(ms1.empty());
  EXPECT_TRUE(ms_std1.empty());
}

TEST(multiset, copyAssignmentOperator) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  s21_multiset ms2;
  ms2 = ms1;
  std_multiset ms_std1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std2;
  ms_std2 = ms_std1;

  EXPECT_EQ(ms2.empty(), ms_std2.empty());
  EXPECT_EQ(ms2.size(), ms_std2.size());

  compare(ms2, ms_std2);
}

TEST(multiset, moveAssignmentOperator) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  s21_multiset ms2;
  ms2 = std::move(ms1);
  std_multiset ms_std1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std2;
  ms_std2 = std::move(ms_std1);

  compare(ms2, ms_std2);

  EXPECT_EQ(ms1.empty(), ms_std1.empty());
}

TEST(multiset, insert) {
  s21_multiset ms1;
  std_multiset ms_std;

  auto ms1_result = ms1.insert(1);
  auto ms_std_result = ms_std.insert(1);
  compare(ms1, ms_std);

  ms1_result = ms1.insert(2);
  ms_std_result = ms_std.insert(2);
  compare(ms1, ms_std);

  ms1_result = ms1.insert(1);
  ms_std_result = ms_std.insert(1);
  compare(ms1, ms_std);
}

TEST(multiset, emplace) {
  s21_multiset s21_m;
  std_multiset std_m;

  auto s21_result = s21_m.emplace(1);
  auto std_result = std_m.emplace(1);
  EXPECT_EQ(*s21_result, *std_result);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(1);
  std_result = std_m.emplace(1);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(2);
  std_result = std_m.emplace(2);
  EXPECT_EQ(*s21_result, *std_result);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(2);
  std_result = std_m.emplace(2);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(4);
  std_result = std_m.emplace(4);
  EXPECT_EQ(*s21_result, *std_result);
  EXPECT_EQ(s21_m.size(), std_m.size());

  s21_result = s21_m.emplace(4);
  std_result = std_m.emplace(4);
  EXPECT_EQ(s21_m.size(), std_m.size());
}

TEST(multiset, erase) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  auto ms1_it = ms1.begin();
  auto ms_std_it = ms_std.begin();

  ms1.erase(ms1_it);
  ms_std.erase(ms_std_it);

  compare(ms1, ms_std);

  ms1_it = ms1.begin();
  ++ms1_it;
  ms_std_it = ms_std.begin();
  ++ms_std_it;

  auto ms1_check = ms1.erase(ms1_it);
  auto ms_std_check = ms_std.erase(ms_std_it);

  EXPECT_EQ(*ms1_check, *ms_std_check);

  compare(ms1, ms_std);
}

TEST(multiset, eraseAll) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  while (ms1.size()) {
    ms1.erase(ms1.begin());
    ms_std.erase(ms_std.begin());
  }

  EXPECT_EQ(ms1.size(), ms_std.size());
}

TEST(multiset, clear) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  ms1.clear();
  ms_std.clear();
  compare(ms1, ms_std);
}

TEST(multiset, find) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  compare(ms1, ms_std);
  EXPECT_EQ(ms1.find(6), ms1.end());
  EXPECT_EQ(ms_std.find(6), ms_std.end());
}

TEST(multiset, contains) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  compare(ms1, ms_std);
  EXPECT_FALSE(ms1.conatains(6));
}

TEST(multiset, swap) {
  s21_multiset ms1 = {1, 2, 3, 1, 2, 3};
  s21_multiset ms2 = {4, 5, 6, 4, 5, 6};
  std_multiset ms_std1 = {1, 2, 3, 1, 2, 3};
  std_multiset ms_std2 = {4, 5, 6, 4, 5, 6};

  ms1.swap(ms2);
  ms_std1.swap(ms_std2);
  compare(ms1, ms_std1);
  compare(ms2, ms_std2);
}

TEST(multiset, merge_1) {
  s21_multiset ms1 = {1, 2, 3, 1, 2, 3};
  s21_multiset ms2 = {4, 5, 6, 4, 5, 6};
  std_multiset ms_std1 = {1, 2, 3, 1, 2, 3};
  std_multiset ms_std2 = {4, 5, 6, 4, 5, 6};

  ms1.merge(ms2);
  ms_std1.merge(ms_std2);

  compare(ms1, ms_std1);
  compare(ms2, ms_std2);
}

TEST(multiset, merge_2) {
  s21_multiset ms1 = {1, 2, 3, 10, 20, 30, 40, 50, 1, 2, 3};
  s21_multiset ms2 = {4, 5, 6, 10, 20, 30, 60, 70, 4, 5, 6};
  std_multiset ms_std1 = {1, 2, 3, 10, 20, 30, 40, 50, 1, 2, 3};
  std_multiset ms_std2 = {4, 5, 6, 10, 20, 30, 60, 70, 4, 5, 6};

  ms1.merge(ms2);
  ms_std1.merge(ms_std2);

  compare(ms1, ms_std1);
  compare(ms2, ms_std2);
}

TEST(multiset, count) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  EXPECT_EQ(ms1.count(1), ms_std.count(1));
  EXPECT_EQ(ms1.count(2), ms_std.count(2));
  EXPECT_EQ(ms1.count(3), ms_std.count(3));
  EXPECT_EQ(ms1.count(4), ms_std.count(4));
  EXPECT_EQ(ms1.count(5), ms_std.count(5));
  EXPECT_EQ(ms1.count(6), ms_std.count(6));
}

TEST(multiset, equal_range) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  auto ms1_range = ms1.equal_range(1);
  auto ms_std_range = ms_std.equal_range(1);

  EXPECT_EQ(*ms1_range.first, *ms_std_range.first);
  EXPECT_EQ(*ms1_range.second, *ms_std_range.second);

  ms1_range = ms1.equal_range(6);
  ms_std_range = ms_std.equal_range(6);

  EXPECT_EQ(ms1_range.first, ms1_range.second);
  EXPECT_EQ(ms_std_range.first, ms_std_range.second);
}

TEST(multiset, lower_bound) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  EXPECT_EQ(*ms1.lower_bound(1), *ms_std.lower_bound(1));
  EXPECT_EQ(*ms1.lower_bound(2), *ms_std.lower_bound(2));
  EXPECT_EQ(*ms1.lower_bound(3), *ms_std.lower_bound(3));
  EXPECT_EQ(*ms1.lower_bound(4), *ms_std.lower_bound(4));
  EXPECT_EQ(*ms1.lower_bound(5), *ms_std.lower_bound(5));
  EXPECT_EQ(*ms1.lower_bound(-1), *ms_std.lower_bound(-1));
  EXPECT_EQ(*ms1.lower_bound(6), 0);
}

TEST(multiset, upper_bound) {
  s21_multiset ms1 = {1, 2, 3, 4, 5, 1, 2, 3};
  std_multiset ms_std = {1, 2, 3, 4, 5, 1, 2, 3};

  EXPECT_EQ(*ms1.upper_bound(1), *ms_std.upper_bound(1));
  EXPECT_EQ(*ms1.upper_bound(2), *ms_std.upper_bound(2));
  EXPECT_EQ(*ms1.upper_bound(3), *ms_std.upper_bound(3));
  EXPECT_EQ(*ms1.upper_bound(4), *ms_std.upper_bound(4));
  EXPECT_EQ(*ms1.lower_bound(-1), *ms_std.lower_bound(-1));
  EXPECT_EQ(*ms1.upper_bound(5), 0);
  EXPECT_EQ(*ms1.upper_bound(6), 0);
}
