/**
 * @file tree_test.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Binary tree methods testing module
 * @version 1.0
 * @date 2024-07-21
 *
 * @copyright Copyright (c) 2024
 *
 */

#include <initializer_list>
#include <sstream>

#include "./../main_test.h"

using Tree = s21::tree<int, int>;
using str = std::string;
using init_list = std::initializer_list<int>;

TEST(TreeTest, test_1) {
  str result = "R---{B:30}\n    L---{B:10}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 10};
  init_list remove = {20};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_2) {
  str result = "R---{B:40}\n    L---{B:30}\n    R---{B:50}\n";
  init_list list = {30, 10, 40, 50};
  init_list remove = {10};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_3) {
  str result =
      "R---{B:40}\n    L---{B:30}\n        R---{R:35}\n    R---{B:50}\n";
  init_list list = {30, 40, 20, 35, 50};
  init_list remove = {20};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_4) {
  str result = "R---{B:30}\n    L---{B:20}\n    R---{B:35}\n";
  init_list list = {30, 40, 20, 35};
  init_list remove = {40};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_5) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{B:120}\n        L---{R:110}\n        R---{R:130}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5};
  init_list remove = {30};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_6) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{R:10}\n        R---{R:30}\n   "
      " R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 140};
  init_list remove = {110};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result);
}

TEST(TreeTest, test_7) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5, 140};
  init_list remove = {110, 30};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }
  std::cout << t.print();

  EXPECT_TRUE(t.print() == result);
}

// TEST(TreeTest, test_8) {
//   str result =
//       "R---- BLACK {100}\n    L---- RED {10}\n        L---- BLACK {5}\n "
//       "R---- BLACK {20}\n    R---- RED {130}\n        L---- BLACK {120}\n "
//       "  R---- BLACK {140}\n";
//   init_list list = {100, 20, 120, 10, 30, 110, 130, 5, 140, 122, 115, 118};
//   init_list remove = {};
//   Tree t;

//   auto iterator = list.begin();
//   for (init_list::size_type i = 0; i < list.size(); i++) {
//     t.add(*iterator++, 1);
//   }

//   auto rem_iterator = remove.begin();
//   for (init_list::size_type i = 0; i < remove.size(); i++) {
//     t.remove(*rem_iterator++);
//   }

//   std::cout << t.print();

//   EXPECT_TRUE(t.print() == result);
// }