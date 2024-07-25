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

#include "./../main_test.h"

using tree = s21::tree<int, int>;
using str = std::string;
using init_list = std::initializer_list<int>;

TEST(tree, test_1) {
  str result = "R---{B:30}\n    L---{B:10}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 10};
  init_list remove = {20};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_2) {
  str result = "R---{B:40}\n    L---{B:30}\n    R---{B:50}\n";
  init_list list = {30, 10, 40, 50};
  init_list remove = {10};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_3) {
  str result =
      "R---{B:40}\n    L---{B:30}\n        R---{R:35}\n    R---{B:50}\n";
  init_list list = {30, 40, 20, 35, 50};
  init_list remove = {20};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_4) {
  str result = "R---{B:35}\n    L---{B:30}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 35};
  init_list remove = {20};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_5) {
  str result = "R---{B:30}\n    L---{B:20}\n    R---{B:35}\n";
  init_list list = {30, 40, 20, 35};
  init_list remove = {40};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_6) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{B:120}\n        L---{R:110}\n        R---{R:130}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5};
  init_list remove = {30};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_7) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{R:10}\n        R---{R:30}\n   "
      " R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 140};
  init_list remove = {110};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_8) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5, 140};
  init_list remove = {110, 30};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_9) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:117}\n   "
      "         L---{B:115}\n                R---{R:116}\n            "
      "R---{B:118}\n        R---{B:130}\n            L---{R:122}\n            "
      "R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
  init_list remove = {110};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_10) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:116}\n   "
      "         L---{B:115}\n            R---{B:117}\n        R---{B:130}\n    "
      "        L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
  init_list remove = {110, 118};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_11) {
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
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_12) {
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
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_13) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:88}\n            L---{B:77}\n                "
      "R---{R:80}\n            R---{B:99}\n    R---{B:120}\n        "
      "L---{R:116}\n            L---{B:115}\n            R---{B:117}\n        "
      "R---{B:130}\n            L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60, 82, 66, 26, 22, 69, 1, 110, 118, 5};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_14) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:80}\n            L---{B:77}\n            "
      "R---{B:88}\n    R---{B:130}\n        L---{B:120}\n            "
      "R---{R:122}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60,  82,  66, 26, 22,  69,  1,
                      110, 118, 5,  99, 115, 116, 117};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_15) {
  str result =
      "R---{B:80}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{B:77}\n    R---{B:100}\n        L---{B:88}\n   "
      "     R---{B:122}\n            L---{R:120}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list remove = {60,  82, 66, 26,  22,  69,  1,   110,
                      118, 5,  99, 115, 116, 117, 140, 130};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_16) {
  str result =
      "R---{B:10}\n    L---{B:4}\n        L---{B:2}\n            R---{R:3}\n   "
      "     R---{B:5}\n    R---{R:16}\n        L---{B:14}\n            "
      "L---{B:12}\n                L---{R:11}\n            R---{B:15}\n        "
      "R---{B:20}\n            L---{B:17}\n                R---{R:19}\n        "
      "    R---{B:25}\n                L---{R:23}\n";
  init_list list = {20, 10, 25, 23, 30, 33, 4,  16, 2,
                    5,  14, 17, 3,  12, 15, 19, 11};
  init_list remove = {33, 30};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_17) {
  str result =
      "R---{B:10}\n    L---{B:4}\n        L---{B:2}\n            R---{R:3}\n   "
      "     R---{B:5}\n    R---{B:14}\n        L---{B:12}\n            "
      "L---{R:11}\n        R---{R:20}\n            L---{B:17}\n                "
      "R---{R:19}\n            R---{B:25}\n                L---{R:23}\n";
  init_list list = {20, 10, 25, 23, 30, 33, 4,  16, 2,
                    5,  14, 17, 3,  12, 15, 19, 11};
  init_list remove = {33, 30, 16, 15};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_18) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:105}\n        "
      "L---{B:64}\n            L---{B:54}\n                L---{R:49}\n        "
      "    R---{B:91}\n                L---{R:77}\n                "
      "R---{R:100}\n        R---{B:211}\n            L---{R:112}\n             "
      "   L---{B:111}\n                R---{B:202}\n                    "
      "L---{R:199}\n                    R---{R:209}\n            R---{B:222}\n "
      "               R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_19) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:105}\n        "
      "L---{B:54}\n            L---{B:49}\n            R---{B:91}\n            "
      "    L---{R:77}\n                R---{R:100}\n        R---{B:211}\n      "
      "      L---{R:112}\n                L---{B:111}\n                "
      "R---{B:202}\n                    L---{R:199}\n                    "
      "R---{R:209}\n            R---{B:222}\n                R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_20) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:105}\n        "
      "L---{B:91}\n            L---{B:54}\n                R---{R:77}\n        "
      "    R---{B:100}\n        R---{B:211}\n            L---{R:112}\n         "
      "       L---{B:111}\n                R---{B:202}\n                    "
      "L---{R:199}\n                    R---{R:209}\n            R---{B:222}\n "
      "               R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_21) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:105}\n        "
      "L---{B:77}\n            L---{B:54}\n            R---{B:91}\n        "
      "R---{B:211}\n            L---{R:112}\n                L---{B:111}\n     "
      "           R---{B:202}\n                    L---{R:199}\n               "
      "     R---{R:209}\n            R---{B:222}\n                "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_22) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:112}\n        "
      "L---{B:105}\n            L---{B:54}\n                R---{R:91}\n       "
      "     R---{B:111}\n        R---{B:211}\n            L---{B:202}\n        "
      "        L---{R:199}\n                R---{R:209}\n            "
      "R---{B:222}\n                R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_23) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:112}\n        "
      "L---{B:91}\n            L---{B:54}\n            R---{B:105}\n        "
      "R---{B:211}\n            L---{B:202}\n                L---{R:199}\n     "
      "           R---{R:209}\n            R---{B:222}\n                "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_24) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{B:105}\n        "
      "L---{B:91}\n            L---{R:54}\n        R---{R:211}\n            "
      "L---{B:202}\n                L---{R:199}\n                R---{R:209}\n "
      "           R---{B:222}\n                R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111, 112};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_25) {
  str result =
      "R---{B:43}\n    L---{B:22}\n        L---{B:12}\n        R---{B:33}\n    "
      "R---{B:105}\n        L---{B:91}\n            L---{R:54}\n        "
      "R---{R:211}\n            L---{B:202}\n                L---{R:199}\n     "
      "           R---{R:209}\n            R---{B:222}\n                "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111, 112, 5, 1};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_26) {
  str result =
      "R---{B:105}\n    L---{B:43}\n        L---{B:22}\n            "
      "L---{R:12}\n        R---{B:91}\n            L---{R:54}\n    "
      "R---{B:211}\n        L---{B:202}\n            L---{R:199}\n            "
      "R---{R:209}\n        R---{B:222}\n            R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_27) {
  str result =
      "R---{B:54}\n    L---{B:22}\n        L---{B:12}\n        R---{B:43}\n    "
      "R---{B:211}\n        L---{B:202}\n            L---{R:199}\n            "
      "R---{R:209}\n        R---{B:222}\n            R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33, 105, 91};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_28) {
  str result =
      "R---{B:43}\n    L---{B:12}\n    R---{R:211}\n        L---{B:202}\n      "
      "      L---{R:199}\n            R---{R:209}\n        R---{B:222}\n       "
      "     R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33, 105, 91, 22, 54};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_29) {
  str result =
      "R---{B:211}\n    L---{R:202}\n        L---{B:43}\n            "
      "R---{R:199}\n        R---{B:209}\n    R---{B:222}\n        "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64, 49,  100, 77, 111, 112, 5,
                      1,  33, 105, 91,  22, 54,  12};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}

TEST(tree, test_30) {
  str result =
      "R---{B:199}\n    L---{B:43}\n    R---{B:211}\n        L---{R:202}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list remove = {44, 64,  49, 100, 77, 111, 112, 5,   1,
                      33, 105, 91, 22,  54, 12,  209, 222, 228};
  tree t;

  for (auto key : list) t.insert(key, 1);

  for (auto key : remove) t.remove(key);

  EXPECT_TRUE(t.print() == result) << t.print();
}