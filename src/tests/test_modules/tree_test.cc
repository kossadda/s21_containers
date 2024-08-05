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

using tree = s21::tree<const int, const int>;
using pair = std::pair<const int, const int>;
using str = std::string;
using init_list = std::initializer_list<const int>;

TEST(tree, initializerListConstructor) {
  std::initializer_list<pair> items = {{30, 3}, {40, 4}, {20, 2}, {10, 1}};
  int res[] = {1, 2, 3, 4};
  tree t{items};

  int i = 0;
  for (auto it1 = t.begin(); it1 != t.end(); i++) {
    EXPECT_TRUE((*it1).second == res[i]);
    ++it1;
  }
}

TEST(tree, copyConstructor) {
  tree t1;
  init_list list = {30, 40, 20, 10};

  for (auto key : list) t1.insert({key, 1});

  tree t2{t1};

  for (auto it1 = t1.begin(), it2 = t2.begin(); it1 != t1.end();) {
    EXPECT_TRUE((*it1).second == (*it2).second);
    ++it1;
    ++it2;
  }
}

TEST(tree, moveConstructor) {
  tree t1;
  init_list list = {30, 40, 20, 10};
  int res[] = {10, 20, 30, 40};

  for (auto key : list) t1.insert({key, 1});

  tree t2{std::move(t1)};

  int i = 0;
  for (auto it1 = t1.begin(); it1 != t1.end(); i++) {
    EXPECT_TRUE((*it1).second == res[i]);
    ++it1;
  }

  EXPECT_TRUE(t1.structure().empty());
}

TEST(tree, copyAssignment) {
  tree t1;
  init_list list = {30, 40, 20, 10};

  for (auto key : list) t1.insert({key, 1});

  tree t2;
  t2 = t1;

  for (auto it1 = t1.begin(), it2 = t2.begin(); it1 != t1.end();) {
    EXPECT_TRUE((*it1).second == (*it2).second);
    ++it1;
    ++it2;
  }
}

TEST(tree, moveAssignment) {
  tree t1;
  init_list list = {30, 40, 20, 10};
  int res[] = {10, 20, 30, 40};

  for (auto key : list) t1.insert({key, 1});

  tree t2;
  t2 = std::move(t1);

  int i = 0;
  for (auto it1 = t1.begin(); it1 != t1.end(); i++) {
    EXPECT_TRUE((*it1).second == res[i]);
    ++it1;
  }

  EXPECT_TRUE(t1.structure().empty());
}

TEST(tree, invariant_1) {
  str result = "R---{B:30}\n    L---{B:10}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 10};
  init_list erase = {20};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_2) {
  str result = "R---{B:40}\n    L---{B:30}\n    R---{B:50}\n";
  init_list list = {30, 10, 40, 50};
  init_list erase = {10};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_3) {
  str result =
      "R---{B:40}\n    L---{B:30}\n        R---{R:35}\n    R---{B:50}\n";
  init_list list = {30, 40, 20, 35, 50};
  init_list erase = {20};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_4) {
  str result = "R---{B:35}\n    L---{B:30}\n    R---{B:40}\n";
  init_list list = {30, 40, 20, 35};
  init_list erase = {20};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_5) {
  str result = "R---{B:30}\n    L---{B:20}\n    R---{B:35}\n";
  init_list list = {30, 40, 20, 35};
  init_list erase = {40};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_6) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{B:120}\n        L---{R:110}\n        R---{R:130}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5};
  init_list erase = {30};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_7) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{R:10}\n        R---{R:30}\n   "
      " R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 140};
  init_list erase = {110};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_8) {
  str result =
      "R---{B:100}\n    L---{R:10}\n        L---{B:5}\n        R---{B:20}\n    "
      "R---{R:130}\n        L---{B:120}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5, 140};
  init_list erase = {110, 30};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_9) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:117}\n   "
      "         L---{B:115}\n                R---{R:116}\n            "
      "R---{B:118}\n        R---{B:130}\n            L---{R:122}\n            "
      "R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
  init_list erase = {110};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_10) {
  str result =
      "R---{B:100}\n    L---{B:20}\n        L---{B:10}\n            "
      "L---{R:5}\n        R---{B:30}\n    R---{B:120}\n        L---{R:116}\n   "
      "         L---{B:115}\n            R---{B:117}\n        R---{B:130}\n    "
      "        L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20,  120, 10,  30,  110, 130,
                    5,   140, 122, 115, 116, 117, 118};
  init_list erase = {110, 118};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_11) {
  str result =
      "R---{B:100}\n    L---{R:30}\n        L---{B:10}\n            "
      "L---{B:5}\n            R---{B:20}\n        R---{B:88}\n            "
      "L---{B:77}\n                R---{R:80}\n            R---{B:99}\n    "
      "R---{B:120}\n        L---{R:117}\n            L---{B:115}\n             "
      "   R---{R:116}\n            R---{B:118}\n        R---{B:130}\n          "
      "  L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list erase = {60, 82, 66, 26, 22, 69, 1, 110};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_12) {
  str result =
      "R---{B:100}\n    L---{R:30}\n        L---{B:10}\n            "
      "L---{B:5}\n            R---{B:20}\n        R---{B:88}\n            "
      "L---{B:77}\n                R---{R:80}\n            R---{B:99}\n    "
      "R---{B:120}\n        L---{R:116}\n            L---{B:115}\n            "
      "R---{B:117}\n        R---{B:130}\n            L---{R:122}\n            "
      "R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list erase = {60, 82, 66, 26, 22, 69, 1, 110, 118};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_13) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:88}\n            L---{B:77}\n                "
      "R---{R:80}\n            R---{B:99}\n    R---{B:120}\n        "
      "L---{R:116}\n            L---{B:115}\n            R---{B:117}\n        "
      "R---{B:130}\n            L---{R:122}\n            R---{R:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list erase = {60, 82, 66, 26, 22, 69, 1, 110, 118, 5};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_14) {
  str result =
      "R---{B:100}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{R:80}\n            L---{B:77}\n            "
      "R---{B:88}\n    R---{B:130}\n        L---{B:120}\n            "
      "R---{R:122}\n        R---{B:140}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list erase = {60, 82, 66, 26, 22, 69, 1, 110, 118, 5, 99, 115, 116, 117};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_15) {
  str result =
      "R---{B:80}\n    L---{B:30}\n        L---{B:10}\n            "
      "R---{R:20}\n        R---{B:77}\n    R---{B:100}\n        L---{B:88}\n   "
      "     R---{B:122}\n            L---{R:120}\n";
  init_list list = {100, 20, 120, 10, 30, 110, 130, 5,  140, 122, 115, 116, 117,
                    118, 60, 26,  1,  22, 66,  69,  77, 82,  88,  99,  80};
  init_list erase = {60,  82, 66, 26,  22,  69,  1,   110,
                     118, 5,  99, 115, 116, 117, 140, 130};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_16) {
  str result =
      "R---{B:10}\n    L---{B:4}\n        L---{B:2}\n            R---{R:3}\n   "
      "     R---{B:5}\n    R---{R:16}\n        L---{B:14}\n            "
      "L---{B:12}\n                L---{R:11}\n            R---{B:15}\n        "
      "R---{B:20}\n            L---{B:17}\n                R---{R:19}\n        "
      "    R---{B:25}\n                L---{R:23}\n";
  init_list list = {20, 10, 25, 23, 30, 33, 4,  16, 2,
                    5,  14, 17, 3,  12, 15, 19, 11};
  init_list erase = {33, 30};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_17) {
  str result =
      "R---{B:10}\n    L---{B:4}\n        L---{B:2}\n            R---{R:3}\n   "
      "     R---{B:5}\n    R---{B:14}\n        L---{B:12}\n            "
      "L---{R:11}\n        R---{R:20}\n            L---{B:17}\n                "
      "R---{R:19}\n            R---{B:25}\n                L---{R:23}\n";
  init_list list = {20, 10, 25, 23, 30, 33, 4,  16, 2,
                    5,  14, 17, 3,  12, 15, 19, 11};
  init_list erase = {33, 30, 16, 15};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_18) {
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
  init_list erase = {44};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_19) {
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
  init_list erase = {44, 64};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_20) {
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
  init_list erase = {44, 64, 49};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_21) {
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
  init_list erase = {44, 64, 49, 100};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_22) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:112}\n        "
      "L---{B:105}\n            L---{B:54}\n                R---{R:91}\n       "
      "     R---{B:111}\n        R---{B:211}\n            L---{B:202}\n        "
      "        L---{R:199}\n                R---{R:209}\n            "
      "R---{B:222}\n                R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_23) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{R:112}\n        "
      "L---{B:91}\n            L---{B:54}\n            R---{B:105}\n        "
      "R---{B:211}\n            L---{B:202}\n                L---{R:199}\n     "
      "           R---{R:209}\n            R---{B:222}\n                "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_24) {
  str result =
      "R---{B:43}\n    L---{B:12}\n        L---{B:5}\n            L---{R:1}\n  "
      "      R---{B:33}\n            L---{R:22}\n    R---{B:105}\n        "
      "L---{B:91}\n            L---{R:54}\n        R---{R:211}\n            "
      "L---{B:202}\n                L---{R:199}\n                R---{R:209}\n "
      "           R---{B:222}\n                R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111, 112};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_25) {
  str result =
      "R---{B:43}\n    L---{B:22}\n        L---{B:12}\n        R---{B:33}\n    "
      "R---{B:105}\n        L---{B:91}\n            L---{R:54}\n        "
      "R---{R:211}\n            L---{B:202}\n                L---{R:199}\n     "
      "           R---{R:209}\n            R---{B:222}\n                "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111, 112, 5, 1};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_26) {
  str result =
      "R---{B:105}\n    L---{B:43}\n        L---{B:22}\n            "
      "L---{R:12}\n        R---{B:91}\n            L---{R:54}\n    "
      "R---{B:211}\n        L---{B:202}\n            L---{R:199}\n            "
      "R---{R:209}\n        R---{B:222}\n            R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_27) {
  str result =
      "R---{B:54}\n    L---{B:22}\n        L---{B:12}\n        R---{B:43}\n    "
      "R---{B:211}\n        L---{B:202}\n            L---{R:199}\n            "
      "R---{R:209}\n        R---{B:222}\n            R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33, 105, 91};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_28) {
  str result =
      "R---{B:43}\n    L---{B:12}\n    R---{R:211}\n        L---{B:202}\n      "
      "      L---{R:199}\n            R---{R:209}\n        R---{B:222}\n       "
      "     R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49, 100, 77, 111, 112, 5, 1, 33, 105, 91, 22, 54};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_29) {
  str result =
      "R---{B:211}\n    L---{R:202}\n        L---{B:43}\n            "
      "R---{R:199}\n        R---{B:209}\n    R---{B:222}\n        "
      "R---{R:228}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64, 49,  100, 77, 111, 112, 5,
                     1,  33, 105, 91,  22, 54,  12};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, invariant_30) {
  str result =
      "R---{B:199}\n    L---{B:43}\n    R---{B:211}\n        L---{R:202}\n";
  init_list list = {64, 44,  22,  112, 43, 33, 12,  5,   105, 211, 54,
                    77, 222, 111, 1,   49, 91, 199, 202, 209, 228, 100};
  init_list erase = {44, 64,  49, 100, 77, 111, 112, 5,   1,
                     33, 105, 91, 22,  54, 12,  209, 222, 228};
  tree t;

  for (auto key : list) t.insert({key, 1});

  for (auto key : erase) t.erase(key);

  EXPECT_TRUE(t.structure() == result) << t.structure();
}

TEST(tree, insert) {
  tree t1;

  auto it = t1.insert({12, 12});

  EXPECT_EQ((*it).first, 12);
}

TEST(tree, insertNonunique) {
  tree t1;

  t1.insert({12, 12});
  auto it = t1.insert({12, 12});

  EXPECT_EQ(it, t1.end());
}

TEST(tree, find) {
  tree t1{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  auto it = t1.find(45);

  EXPECT_EQ((*(it - 1)).first, 42);
  EXPECT_EQ((*it).first, 45);
  EXPECT_EQ((*(it + 1)).first, 100);
}

TEST(tree, eraseByKey) {
  tree t1{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  auto next_it = t1.erase(45);
  auto it = t1.find(42);

  EXPECT_EQ((*it).first, 42);
  EXPECT_EQ((*(it + 1)).first, 100);
  EXPECT_EQ((*next_it).first, 100);
}

TEST(tree, eraseByIterator) {
  tree t1{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  t1.erase(t1.find(45));
  auto it = t1.find(42);

  EXPECT_EQ((*it).first, 42);
  EXPECT_EQ((*(it + 1)).first, 100);
}

TEST(tree, eraseAll) {
  tree t1{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  while (t1.size()) {
    t1.erase(t1.begin());
  }

  EXPECT_EQ(t1.size(), 0);
}

TEST(tree, merge) {
  tree t1{{5, 5}, {13, 13}, {1, 1}, {31, 31}, {4, 4}, {6, 6}, {22, 22}};
  tree t2{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};
  int res_t1[] = {1, 3, 4, 5, 6, 7, 9, 13, 15, 21, 22, 31, 42, 45, 100};
  int res_t2[] = {1, 4, 13, 22, 31};

  t1.merge(t2);

  int j = 0;
  for (auto i : t1) {
    EXPECT_EQ(i.first, res_t1[j++]);
  }

  j = 0;
  for (auto i : t2) {
    EXPECT_EQ(i.first, res_t2[j++]);
  }
}

TEST(tree, clear) {
  tree t1{{15, 15}, {9, 9},   {13, 13}, {1, 1}, {7, 7}, {42, 42},  {21, 21},
          {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  t1.clear();

  auto it = t1.insert({1123412, 1});

  EXPECT_EQ(it++, t1.begin());
  EXPECT_EQ(it, t1.end());
}

TEST(treeIterator, treeIterateCheck_1) {
  init_list list = {30, 40, 20, 10};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 4);
  ++it;
  EXPECT_EQ((*it).second, 3);
  ++it;
  EXPECT_EQ((*it).second, 1);
  ++it;
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ(it, t.end());
}

TEST(treeIterator, treeIterateCheck_2) {
  init_list list = {30, 10, 40, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ((*it).second, 1);
  ++it;
  EXPECT_EQ((*it).second, 3);
  ++it;
  EXPECT_EQ((*it).second, 4);
  ++it;
  EXPECT_EQ(it, t.end());
}

TEST(treeIterator, treeIterateCheck_3) {
  init_list list = {30, 40, 20, 35, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 3);
  ++it;
  EXPECT_EQ((*it).second, 1);
  ++it;
  EXPECT_EQ((*it).second, 4);
  ++it;
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ((*it).second, 5);
  ++it;
  EXPECT_EQ(it, t.end());
}

TEST(treeIterator, treeIterateCheck_4) {
  init_list list = {30, 40, 20, 35};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 3);
  ++it;
  EXPECT_EQ((*it).second, 1);
  ++it;
  EXPECT_EQ((*it).second, 4);
  ++it;
  EXPECT_EQ((*it).second, 2);
  ++it;
  EXPECT_EQ(it, t.end());
}

TEST(treeIterator, treeIterateCheck_5) {
  init_list list = {30, 40, 20, 35};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.end();
  --it;
  EXPECT_EQ((*it).second, 2);
  --it;
  EXPECT_EQ((*it).second, 4);
  --it;
  EXPECT_EQ((*it).second, 1);
  --it;
  EXPECT_EQ((*it).second, 3);
  --it;
  EXPECT_EQ(it, t.begin());
}

TEST(treeIterator, treeIterateCheck_6) {
  init_list list = {30, 10, 40, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.end();
  --it;
  EXPECT_EQ((*it).second, 4);
  --it;
  EXPECT_EQ((*it).second, 3);
  --it;
  EXPECT_EQ((*it).second, 1);
  --it;
  EXPECT_EQ((*it).second, 2);
  --it;
  EXPECT_EQ(it, t.begin());
}

TEST(treeIterator, treeIterateCheck_7) {
  init_list list = {30, 40, 20, 35, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.end();
  --it;
  EXPECT_EQ((*it).second, 5);
  --it;
  EXPECT_EQ((*it).second, 2);
  --it;
  EXPECT_EQ((*it).second, 4);
  --it;
  EXPECT_EQ((*it).second, 1);
  --it;
  EXPECT_EQ((*it).second, 3);
  --it;
  EXPECT_EQ(it, t.begin());
}

TEST(treeIterator, treeIterateCheck_8) {
  init_list list = {30, 40, 20, 35};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 3);
  it = it + 2;
  EXPECT_EQ((*it).second, 4);
  it = it - 1;
  EXPECT_EQ((*it).second, 1);
}

TEST(treeIterator, treeIterateCheck_9) {
  init_list list = {30, 10, 40, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 2);
  it = it + 3;
  EXPECT_EQ((*it).second, 4);
  it = it - 2;
  EXPECT_EQ((*it).second, 1);
}

TEST(treeIterator, treeIterateCheck_10) {
  init_list list = {30, 40, 20, 35, 50};
  tree t;

  int i = 0;
  for (auto key : list) t.insert({key, ++i});

  auto it = t.begin();
  EXPECT_EQ((*it).second, 3);
  it = it + 4;
  EXPECT_EQ((*it).second, 5);
  it = it - 3;
  EXPECT_EQ((*it).second, 1);
}

TEST(treeIterator, treeIterateCheck_11) {
  init_list list = {30, 40, 20, 35};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  ++it2;
  EXPECT_NE(it1, it2);
  ++it1;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_12) {
  init_list list = {30, 10, 40, 50};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  ++it2;
  EXPECT_NE(it1, it2);
  ++it1;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_13) {
  init_list list = {30, 40, 20, 35, 50};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  ++it2;
  EXPECT_NE(it1, it2);
  ++it1;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_14) {
  init_list list = {30, 40, 20, 35};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  ++it2;
  EXPECT_NE(it1, it2);
  ++it1;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_15) {
  init_list list = {30, 40, 20, 35};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  it2 = it2 + 2;
  EXPECT_NE(it1, it2);
  it1 = it1 + 2;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_16) {
  init_list list = {30, 10, 40, 50};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  it2 = it2 + 2;
  EXPECT_NE(it1, it2);
  it1 = it1 + 2;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_17) {
  init_list list = {30, 40, 20, 35, 50};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  it2 = it2 + 3;
  EXPECT_NE(it1, it2);
  it1 = it1 + 3;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_18) {
  init_list list = {30, 40, 20, 35};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.begin();
  auto it2 = t.begin();
  it2 = it2 + 2;
  EXPECT_NE(it1, it2);
  it1 = it1 + 2;
  EXPECT_EQ(it1, it2);
}

TEST(treeIterator, treeIterateCheck_19) {
  init_list list = {30, 40, 20, 35};
  tree t;

  for (auto key : list) t.insert({key, 1});

  auto it1 = t.end();
  auto it2 = t.end();
  it2 = it2 - 1;
  EXPECT_NE(it1, it2);
  it1 = it1 - 1;
  EXPECT_EQ(it1, it2);
}
