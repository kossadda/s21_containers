/**
 * @file list_test.cc
 * @author emmonbea (moskaleviluak@icloud.com)
 * @brief Unit tests for the list class
 * @version 1.0
 * @date 2024-06-14
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <list>

#include "../../s21_containers.h"
#include "../main_test.h"

template <typename T>
static void print_original(const std::list<T> &l) {
  for (auto it = l.cbegin(); it != l.cend(); ++it) {
    std::cout << *it << " ";
  }
  std::cout << std::endl;
}

template <typename T>
static void print_lists(const std::list<T> &std_list,
                        const s21::list<T> &s21_list) {
  std::cout << "std_list(size = " << std_list.size() << "):" << std::endl;

  print_original(std_list);

  std::cout << "s21_list(size = " << s21_list.size() << "):" << std::endl;

  s21_list.print();
}

template <typename T>
static bool compare_lists(const std::list<T> &std_list,
                          const s21::list<T> &s21_list, bool expect) {
  bool res = true;
  auto std_it = std_list.cbegin();
  auto s21_it = s21_list.cbegin();

  if (std_list.size() != s21_list.size()) {
    res = false;
  }

  for (; std_it != std_list.cend() && s21_it != s21_list.cend();
       ++std_it, ++s21_it) {
    if (*std_it != *s21_it) {
      res = false;
    }
  }

  if (res != expect) {
    print_lists(std_list, s21_list);
  }
  return res;
}

TEST(ListTest, DefaultConstructor) {
  s21::list<int> l;

  EXPECT_EQ(l.size(), 0);
  EXPECT_EQ(l.cbegin(), l.cend());
  EXPECT_TRUE(l.empty());
}

TEST(ListTest, ConstructorWithSize) {
  size_t n = 5;
  s21::list<int> l(n);
  auto it = l.cbegin();

  EXPECT_EQ(l.size(), n);
  for (size_t i = 0; i < n; ++i) {
    EXPECT_EQ(*it, 0);
  }

  EXPECT_FALSE(l.empty());
}

TEST(ListTest, CopyConstructor) {
  s21::list<int> original{1, 2, 3, 4, 5};
  s21::list<int> copy{original};

  EXPECT_TRUE(copy == original);
}

TEST(ListTest, MoveConstructor) {
  s21::list<int> original{1, 2, 3, 4, 5};
  s21::list<int> tmp{1, 2, 3, 4, 5};
  s21::list<int> move{std::move(original)};

  EXPECT_TRUE(original.empty());
  EXPECT_TRUE(move == tmp);
}

TEST(ListTest, Front) {
  s21::list<int> l{1, 2, 3, 4, 5};
  EXPECT_EQ(l.front(), 1);
}

TEST(ListTest, Back) {
  s21::list<int> l{1, 2, 3, 4, 5};
  EXPECT_EQ(l.back(), 5);
}

TEST(ListTest, MaxSize) {
  s21::list<int> l;
  EXPECT_EQ(l.max_size(),
            std::numeric_limits<s21::list<int>::size_type>::max());
}

TEST(ListTest, Insert1) {
  s21::list<int> l;
  auto it = l.insert(l.begin(), 10);

  EXPECT_EQ(*it, 10);
}

TEST(ListTest, Insert2) {
  s21::list<int> l{10};
  auto it = l.insert(l.begin(), 20);

  EXPECT_EQ(*it, 20);
}

TEST(ListTest, Insert3) {
  s21::list<int> l{10, 20, 30};
  s21::list<int> expected{10, 15, 20, 30};

  auto it_1 = l.begin();
  ++it_1;
  auto it_2 = l.insert(it_1, 15);

  EXPECT_TRUE(l == expected);
  EXPECT_EQ(*it_2, 15);
}

TEST(ListTest, EraseNormal1) {
  s21::list<int> s21_list{1};
  s21::list<int> s21_expected;
  auto it = s21_list.begin();

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal2) {
  s21::list<int> s21_list{1, 2};
  s21::list<int> s21_expected{2};
  auto it = s21_list.begin();

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal3) {
  s21::list<int> s21_list{1, 2};
  s21::list<int> s21_expected{1};
  auto it = s21_list.begin();
  ++it;

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, EraseNormal4) {
  s21::list<int> s21_list{1, 2, 4, 3, 4, 5, 6};
  s21::list<int> s21_expected{1, 2, 3, 4, 5, 6};
  auto it = s21_list.begin();
  ++it;
  ++it;

  s21_list.erase(it);

  EXPECT_TRUE(s21_list == s21_expected);
}

TEST(ListTest, PushBack) {
  s21::list<int> l{1};
  s21::list<int> expected{1, 2};

  l.push_back(2);

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, PushFront) {
  s21::list<int> l{1, 2};
  s21::list<int> expected{0, 1, 2};

  l.push_front(0);

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, PopFrontNormal1) {
  std::list<int> std_list{1, 2};
  s21::list<int> s21_list{1, 2};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontNormal2) {
  std::list<int> std_list{1, 2, 3};
  s21::list<int> s21_list{1, 2, 3};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontNormal3) {
  std::list<int> std_list{1};
  s21::list<int> s21_list{1};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_TRUE(compare_lists(std_list, s21_list, true));
}

TEST(ListTest, PopFrontFail1) {
  std::list<int> std_list{1, 2, 3};
  s21::list<int> s21_list{1, 2};

  std_list.pop_front();
  s21_list.pop_front();

  EXPECT_FALSE(compare_lists(std_list, s21_list, false));
}

TEST(ListTest, SwapNormal1) {
  std::list<int> std_list_1{1, 2, 3};
  s21::list<int> s21_list_1{1, 2, 3};

  std::list<int> std_list_2{3, 2, 1};
  s21::list<int> s21_list_2{3, 2, 1};

  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);

  std::list<int> expected_std_1{3, 2, 1};
  std::list<int> expected_std_2{1, 2, 3};
  s21::list<int> expected_s21_1{3, 2, 1};
  s21::list<int> expected_s21_2{1, 2, 3};

  EXPECT_EQ(std_list_1, expected_std_1);
  EXPECT_EQ(std_list_2, expected_std_2);

  EXPECT_EQ(s21_list_1, expected_s21_1);
  EXPECT_EQ(s21_list_2, expected_s21_2);

  EXPECT_TRUE(compare_lists(std_list_1, s21_list_1, true));
  EXPECT_TRUE(compare_lists(std_list_2, s21_list_2, true));
}

TEST(ListTest, SwapNormal2) {
  std::list<int> std_list_1{1, 2, 3, 5, 6};
  s21::list<int> s21_list_1{1, 2, 3, 5, 6};

  std::list<int> std_list_2{3, 2, 1};
  s21::list<int> s21_list_2{3, 2, 1};

  std_list_1.swap(std_list_2);
  s21_list_1.swap(s21_list_2);

  std::list<int> expected_std_1{3, 2, 1};
  std::list<int> expected_std_2{1, 2, 3, 5, 6};
  s21::list<int> expected_s21_1{3, 2, 1};
  s21::list<int> expected_s21_2{1, 2, 3, 5, 6};

  EXPECT_EQ(std_list_1, expected_std_1);
  EXPECT_EQ(std_list_2, expected_std_2);

  EXPECT_EQ(s21_list_1, expected_s21_1);
  EXPECT_EQ(s21_list_2, expected_s21_2);

  EXPECT_TRUE(compare_lists(std_list_1, s21_list_1, true));
  EXPECT_TRUE(compare_lists(std_list_2, s21_list_2, true));
}

TEST(ListTest, MergeNormal1) {
  s21::list<int> l_1{1, 3, 5, 7};
  s21::list<int> l_2{4, 6, 9, 10};
  s21::list<int> expected_1{1, 3, 4, 5, 6, 7, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeEmpty1) {
  s21::list<int> l_1;
  s21::list<int> l_2{4, 6, 9, 10};
  s21::list<int> expected_1{4, 6, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeEmpty2) {
  s21::list<int> l_1{4, 6, 9, 10};
  s21::list<int> l_2;
  s21::list<int> expected_1{4, 6, 9, 10};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, MergeNonSorted) {
  s21::list<int> l_1{2, 1, 3, 5, 2, 9, 7};
  s21::list<int> l_2{1, 4, 5, 3, 4};
  s21::list<int> expected_1{1, 2, 1, 3, 4, 5, 2, 5, 3, 4, 9, 7};

  l_1.merge(l_2);

  EXPECT_TRUE(l_1 == expected_1);
  EXPECT_TRUE(l_2.empty());
}

TEST(ListTest, SpliceNormal1) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2{6, 7, 8, 9};

  s21::list<int> s21_expected{1, 6, 7, 8, 9, 2, 3, 4, 5};

  auto it = s21_list_1.cbegin();
  ++it;

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceNormal2) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2{6};

  s21::list<int> s21_expected{6, 1, 2, 3, 4, 5};

  auto it = s21_list_1.cbegin();

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceNormal3) {
  s21::list<int> s21_list_1;
  s21::list<int> s21_list_2{6};

  s21::list<int> s21_expected{6};

  s21::list<int>::const_iterator it = s21_list_1.cbegin();

  s21_list_1.splice(it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, SpliceEmpty) {
  s21::list<int> s21_list_1{1, 2, 3, 4, 5};
  s21::list<int> s21_list_2;

  s21::list<int> s21_expected{1, 2, 3, 4, 5};
  std::list<int> std_expected{1, 2, 3, 4, 5};

  auto s21_it = s21_list_1.cbegin();

  s21_list_1.splice(s21_it, s21_list_2);

  EXPECT_TRUE(s21_list_1 == s21_expected);
}

TEST(ListTest, ReverseNormal1) {
  s21::list<int> l{2, 1, 3, 5, 2, 9, 7};
  s21::list<int> expected{7, 9, 2, 5, 3, 1, 2};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, ReverseNormal2) {
  s21::list<int> l{2, 1};
  s21::list<int> expected{1, 2};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, ReverseNormal3) {
  s21::list<int> l{1};
  s21::list<int> expected{1};

  l.reverse();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, UniqueNormal1) {
  s21::list<int> l{2, 2, 1, 2, 2, 2, 3, 3, 4, 1};
  s21::list<int> expected{2, 1, 2, 3, 4, 1};

  l.unique();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort1) {
  s21::list<int> l{1};
  s21::list<int> expected{1};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort2) {
  s21::list<int> l{3, 2, 1};
  s21::list<int> expected{1, 2, 3};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort3) {
  s21::list<int> l{2, 3, 2};
  s21::list<int> expected{2, 2, 3};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort4) {
  s21::list<int> l{9, 1, 3, 2, 1, 3, 4, 9, 8, 2, 3, -19, 0};
  s21::list<int> expected{-19, 0, 1, 1, 2, 2, 3, 3, 3, 4, 8, 9, 9};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort5) {
  s21::list<int> l{3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5, 8, 9,
                   7, 9, 3, 2, 3, 8, 4, 6, 2, 6, 4, 3};
  s21::list<int> expected{1, 1, 2, 2, 2, 3, 3, 3, 3, 3, 4, 4, 4,
                          5, 5, 5, 6, 6, 6, 7, 8, 8, 9, 9, 9};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort6) {
  s21::list<int> l{20, -1, 15, 2,  2,  8,  4, 4, 7,  6,  5, 5,
                   0,  -3, 10, 12, 11, -2, 9, 3, 13, 14, 1, -5};
  s21::list<int> expected{-5, -3, -2, -1, 0, 1,  2,  2,  3,  4,  4,  5,
                          5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 20};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort7) {
  s21::list<int> l{42, 23, 16, 15, 8, 4,  42, 23, 15,
                   8,  16, 4,  42, 8, 23, 15, 16, 4};
  s21::list<int> expected{4,  4,  4,  8,  8,  8,  15, 15, 15,
                          16, 16, 16, 23, 23, 23, 42, 42, 42};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort8) {
  s21::list<int> l{100, 99, 98, 97, 96, 95, 94, 93, 92, 91, 90,
                   89,  88, 87, 86, 85, 84, 83, 82, 81, 80};
  s21::list<int> expected{80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90,
                          91, 92, 93, 94, 95, 96, 97, 98, 99, 100};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort9) {
  s21::list<int> l{-100, 0, 50, -50, 25, -25, 75, -75, 100,
                   -100, 0, 50, -50, 25, -25, 75, -75, 100};
  s21::list<int> expected{-100, -100, -75, -75, -50, -50, -25, -25, 0,
                          0,    25,   25,  50,  50,  75,  75,  100, 100};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, Sort10) {
  s21::list<int> l{1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12, 13, 14,
                   15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28,
                   29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
  s21::list<int> expected{1,  2,  3,  4,  5,  6,  7,  8,  9,  10,
                          11, 12, 13, 14, 15, 16, 17, 18, 19, 20,
                          21, 22, 23, 24, 25, 26, 27, 28, 29, 30,
                          31, 32, 33, 34, 35, 36, 37, 38, 39, 40};
  l.sort();

  EXPECT_TRUE(l == expected);
}

TEST(ListTest, EmplaseBegin) {
  std::list<int> std_l{1, 2, 3, 4};
  std_l.emplace(std_l.begin(), 2);

  s21::list<int> s21_l{1, 2, 3, 4};
  s21_l.emplace(s21_l.begin(), 2);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseEnd) {
  std::list<int> std_l{1, 2, 3, 4};
  std_l.emplace(std_l.end(), 2);

  s21::list<int> s21_l{1, 2, 3, 4};
  s21_l.emplace(s21_l.end(), 2);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseMiddle) {
  std::list<int> std_l{1, 2, 3, 4};
  auto std_it = std_l.begin();
  std_it++;
  std_it++;
  std_l.emplace(std_it, 10);

  s21::list<int> s21_l{1, 2, 3, 4};
  auto s21_it = s21_l.begin();
  s21_it++;
  s21_it++;
  s21_l.emplace(s21_it, 10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseEmpty) {
  std::list<int> std_l;
  std_l.emplace(std_l.begin(), 10);

  s21::list<int> s21_l;
  s21_l.emplace(s21_l.begin(), 10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseFrontEmpty) {
  std::list<int> std_l;
  std_l.emplace_front(10);

  s21::list<int> s21_l;
  s21_l.emplace_front(10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseFront) {
  std::list<int> std_l{1, 10, 20, 312, 12, 3};
  std_l.emplace_front(10);

  s21::list<int> s21_l{1, 10, 20, 312, 12, 3};
  s21_l.emplace_front(10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseBackEmpty) {
  std::list<int> std_l;
  std_l.emplace_back(10);

  s21::list<int> s21_l;
  s21_l.emplace_back(10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}

TEST(ListTest, EmplaseBack) {
  std::list<int> std_l{1, 10, 20, 312, 12, 3};
  std_l.emplace_back(10);

  s21::list<int> s21_l{1, 10, 20, 312, 12, 3};
  s21_l.emplace_back(10);

  EXPECT_TRUE(compare_lists(std_l, s21_l, true));
  EXPECT_EQ(std_l.size(), s21_l.size());
}
