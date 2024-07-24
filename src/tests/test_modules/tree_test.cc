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

  EXPECT_TRUE(t.print() == result) << t.print();
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

  EXPECT_TRUE(t.print() == result) << t.print();
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_4) {
  str result = "R---{B:35}\n    L---{B:30}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 35};
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_5) {
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_6) {
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_7) {
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_8) {
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_9) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:117}\n   "
      "         L---{B:115}\n                R---{R:116}\n            "
      "R---{B:118}\n        R---{B:130}\n            L---{R:122}\n            "
      "R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
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

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_10) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:116}\n   "
      "         L---{B:115}\n            R---{B:117}\n        R---{B:130}\n    "
      "        L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
  init_list remove = {110, 118};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_11) {
  str result =
      "R---{B:100}\n    L---{R:30}\n        L---{B:10}\n            "
      "L---{B:5}\n            R---{B:20}\n        R---{B:88}\n            "
      "L---{B:77}\n                R---{R:80}\n            R---{B:99}\n    "
      "R---{B:120}\n        L---{R:117}\n            L---{B:115}\n             "
      "   R---{R:116}\n            R---{B:118}\n        R---{B:130}\n          "
      "  L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60, 82, 66, 26, 22, 69, 1, 110};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_12) {
  str result =
      "R---{B:100}\n    L---{R:30}\n        L---{B:10}\n            "
      "L---{B:5}\n            R---{B:20}\n        R---{B:88}\n            "
      "L---{B:77}\n                R---{R:80}\n            R---{B:99}\n    "
      "R---{B:120}\n        L---{R:116}\n            L---{B:115}\n            "
      "R---{B:117}\n        R---{B:130}\n            L---{R:122}\n            "
      "R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60, 82, 66, 26, 22, 69, 1, 110, 118};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_13) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:88}\n            L---{B:77}\n                "
      "R---{R:80}\n            R---{B:99}\n    R---{B:120}\n        "
      "L---{R:116}\n            L---{B:115}\n            R---{B:117}\n        "
      "R---{B:130}\n            L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60, 82, 66, 26, 22, 69, 1, 110, 118, 5};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_14) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:80}\n            L---{B:77}\n            "
      "R---{B:88}\n    R---{B:130}\n        L---{B:120}\n            "
      "R---{R:122}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60,  82,  66, 26, 22,  69,  1,
                      110, 118, 5,  99, 115, 116, 117};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_15) {
  str result =
      "R---{B:80}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{B:77}\n    R---{B:100}\n        L---{B:88}\n   "
      "     R---{B:122}\n            L---{R:120}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60,  82, 66, 26,  22,  69,  1,   110,
                      118, 5,  99, 115, 116, 117, 140, 130};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(TreeTest, test_16) {
  str result =
      "R---{B:10}\n    L---{B:4}\n        L---{B:2}\n            R---{R:3}\n   "
      "     R---{B:5}\n    R---{R:16}\n        L---{B:14}\n            "
      "L---{B:12}\n                L---{R:11}\n            R---{B:15}\n        "
      "R---{B:20}\n            L---{B:17}\n                R---{R:19}\n        "
      "    R---{B:25}\n                L---{R:23}\n";
  init_list list = {20, 10, 25, 23, 30, 33, 4,  16, 2,
                    5,  14, 17, 3,  12, 15, 19, 11};
  init_list remove = {33, 30};
  Tree t;

  auto iterator = list.begin();
  for (init_list::size_type i = 0; i < list.size(); i++) {
    t.add(*iterator++, 1);
  }

  auto rem_iterator = remove.begin();
  for (init_list::size_type i = 0; i < remove.size(); i++) {
    t.remove(*rem_iterator++);
  }

  EXPECT_TRUE(t.print() == result) << t.print();
}