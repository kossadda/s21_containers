// /**
//  * @file map_test.cc
//  * @author kossadda (https://github.com/kossadda)
//  * @brief Map methods testing module
//  * @version 1.0
//  * @date 2024-07-27
//  *
//  * @copyright Copyright (c) 2024
//  *
//  */

// #include <map>

// #include "./../main_test.h"

// using s21_map = s21::map<int, int>;
// using std_map = std::map<int, int>;

// TEST(MapTest, DefaultConstructor) {
//   s21_map s21_m;
//   std_map std_m;
//   EXPECT_EQ(s21_m.empty(), std_m.empty());
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, InitializerListConstructor) {
//   s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

//   EXPECT_EQ(s21_m.empty(), std_m.empty());
//   EXPECT_EQ(s21_m.size(), std_m.size());

//   auto s21_it = s21_m.begin();
//   auto std_it = std_m.begin();
//   for (; s21_it != s21_m.end(); s21_it++, std_it++) {
//     EXPECT_EQ((*s21_it).first, (*std_it).first);
//     EXPECT_EQ((*s21_it).second, (*std_it).second);
//   }
// }

// TEST(MapTest, CopyConstructor) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   s21_map s21_m2 = s21_m1;
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m2 = std_m1;

//   EXPECT_EQ(s21_m2.empty(), std_m2.empty());
//   EXPECT_EQ(s21_m2.size(), std_m2.size());

//   auto s21_it = s21_m2.begin();
//   auto std_it = std_m2.begin();
//   for (; s21_it != s21_m2.end(); s21_it++, std_it++) {
//     EXPECT_EQ((*s21_it).first, (*std_it).first);
//     EXPECT_EQ((*s21_it).second, (*std_it).second);
//   }
// }

// TEST(MapTest, MoveConstructor) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   s21_map s21_m2 = std::move(s21_m1);
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m2 = std::move(std_m1);

//   EXPECT_EQ(s21_m2.empty(), std_m2.empty());
//   EXPECT_EQ(s21_m2.size(), std_m2.size());

//   auto s21_it = s21_m2.begin();
//   auto std_it = std_m2.begin();
//   for (; s21_it != s21_m2.end(); s21_it++, std_it++) {
//     EXPECT_EQ((*s21_it).first, (*std_it).first);
//     EXPECT_EQ((*s21_it).second, (*std_it).second);
//   }

//   EXPECT_TRUE(s21_m1.empty());
//   EXPECT_TRUE(std_m1.empty());
// }

// TEST(MapTest, CopyAssignmentOperator) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   s21_map s21_m2;
//   s21_m2 = s21_m1;
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m2;
//   std_m2 = std_m1;

//   EXPECT_EQ(s21_m2.empty(), std_m2.empty());
//   EXPECT_EQ(s21_m2.size(), std_m2.size());

//   auto s21_it = s21_m2.begin();
//   auto std_it = std_m2.begin();
//   for (; s21_it != s21_m2.end(); s21_it++, std_it++) {
//     EXPECT_EQ((*s21_it).first, (*std_it).first);
//     EXPECT_EQ((*s21_it).second, (*std_it).second);
//   }
// }

// TEST(MapTest, MoveAssignmentOperator) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   s21_map s21_m2;
//   s21_m2 = std::move(s21_m1);
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m2;
//   std_m2 = std::move(std_m1);

//   EXPECT_EQ(s21_m2.empty(), std_m2.empty());
//   EXPECT_EQ(s21_m2.size(), std_m2.size());

//   auto s21_it = s21_m2.begin();
//   auto std_it = std_m2.begin();
//   for (; s21_it != s21_m2.end(); s21_it++, std_it++) {
//     EXPECT_EQ((*s21_it).first, (*std_it).first);
//     EXPECT_EQ((*s21_it).second, (*std_it).second);
//   }

//   EXPECT_TRUE(s21_m1.empty());
//   EXPECT_TRUE(std_m1.empty());
// }

// TEST(MapTest, Insert) {
//   s21_map s21_m;
//   std_map std_m;

//   auto s21_result = s21_m.insert({1, 1});
//   auto std_result = std_m.insert({1, 1});
//   EXPECT_EQ(s21_result.second, std_result.second);
//   EXPECT_EQ(s21_result.first->first, std_result.first->first);
//   EXPECT_EQ(s21_result.first->second, std_result.first->second);
//   EXPECT_EQ(s21_m.size(), std_m.size());

//   s21_result = s21_m.insert({2, 2});
//   std_result = std_m.insert({2, 2});
//   EXPECT_EQ(s21_result.second, std_result.second);
//   EXPECT_EQ(s21_result.first->first, std_result.first->first);
//   EXPECT_EQ(s21_result.first->second, std_result.first->second);
//   EXPECT_EQ(s21_m.size(), std_m.size());

//   s21_result = s21_m.insert({1, 3});
//   std_result = std_m.insert({1, 3});
//   EXPECT_EQ(s21_result.second, std_result.second);
//   EXPECT_EQ(s21_result.first->first, std_result.first->first);
//   EXPECT_EQ(s21_result.first->second, std_result.first->second);
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, InsertOrAssign) {
//   s21_map s21_m;
//   std_map std_m;

//   auto s21_result = s21_m.insert_or_asssign(1, 1);
//   auto std_result = std_m.insert_or_assign(1, 1);
//   EXPECT_EQ(s21_result.second, std_result.second);
//   EXPECT_EQ(s21_result.first->first, std_result.first->first);
//   EXPECT_EQ(s21_result.first->second, std_result.first->second);
//   EXPECT_EQ(s21_m.size(), std_m.size());

//   s21_result = s21_m.insert_or_asssign(1, 2);
//   std_result = std_m.insert_or_assign(1, 2);
//   EXPECT_EQ(s21_result.second, std_result.second);
//   EXPECT_EQ(s21_result.first->first, std_result.first->first);
//   EXPECT_EQ(s21_result.first->second, std_result.first->second);
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, Erase) {
//   s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

//   auto s21_it = s21_m.begin();
//   auto std_it = std_m.begin();
//   s21_m.erase(s21_it);
//   std_m.erase(std_it);
//   EXPECT_EQ(s21_m.size(), std_m.size());

//   s21_it = s21_m.begin();
//   ++s21_it;
//   std_it = std_m.begin();
//   ++std_it;
//   s21_m.erase(s21_it);
//   std_m.erase(std_it);
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, Clear) {
//   s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

//   s21_m.clear();
//   std_m.clear();
//   EXPECT_EQ(s21_m.empty(), std_m.empty());
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, At) {
//   s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

//   EXPECT_EQ(s21_m.at(1), std_m.at(1));
//   EXPECT_EQ(s21_m.at(2), std_m.at(2));
//   EXPECT_EQ(s21_m.at(3), std_m.at(3));
//   EXPECT_EQ(s21_m.at(4), std_m.at(4));
//   EXPECT_EQ(s21_m.at(5), std_m.at(5));
//   EXPECT_THROW(s21_m.at(6), std::out_of_range);
//   EXPECT_THROW(std_m.at(6), std::out_of_range);
// }

// TEST(MapTest, OperatorBracket) {
//   s21_map s21_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};
//   std_map std_m = {{1, 1}, {2, 2}, {3, 3}, {4, 4}, {5, 5}};

//   EXPECT_EQ(s21_m[1], std_m[1]);
//   EXPECT_EQ(s21_m[2], std_m[2]);
//   EXPECT_EQ(s21_m[3], std_m[3]);
//   EXPECT_EQ(s21_m[4], std_m[4]);
//   EXPECT_EQ(s21_m[5], std_m[5]);
//   s21_m[6] = 6;
//   std_m[6] = 6;
//   EXPECT_EQ(s21_m[6], std_m[6]);
//   EXPECT_EQ(s21_m.size(), std_m.size());
// }

// TEST(MapTest, Swap) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}};
//   s21_map s21_m2 = {{4, 4}, {5, 5}, {6, 6}};
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}};
//   std_map std_m2 = {{4, 4}, {5, 5}, {6, 6}};

//   s21_m1.swap(s21_m2);
//   std_m1.swap(std_m2);
//   EXPECT_EQ(s21_m1.size(), std_m1.size());
//   EXPECT_EQ(s21_m1[4], std_m1[4]);
//   EXPECT_EQ(s21_m1[5], std_m1[5]);
//   EXPECT_EQ(s21_m1[6], std_m1[6]);
//   EXPECT_EQ(s21_m2.size(), std_m2.size());
//   EXPECT_EQ(s21_m2[1], std_m2[1]);
//   EXPECT_EQ(s21_m2[2], std_m2[2]);
//   EXPECT_EQ(s21_m2[3], std_m2[3]);
// }

// TEST(MapTest, Merge) {
//   s21_map s21_m1 = {{1, 1}, {2, 2}, {3, 3}};
//   s21_map s21_m2 = {{4, 4}, {5, 5}, {6, 6}};
//   std_map std_m1 = {{1, 1}, {2, 2}, {3, 3}};
//   std_map std_m2 = {{4, 4}, {5, 5}, {6, 6}};

//   s21_m1.merge(s21_m2);
//   std_m1.merge(std_m2);
//   EXPECT_EQ(s21_m1.size(), std_m1.size());
//   EXPECT_EQ(s21_m1[1], std_m1[1]);
//   EXPECT_EQ(s21_m1[2], std_m1[2]);
//   EXPECT_EQ(s21_m1[3], std_m1[3]);
//   EXPECT_EQ(s21_m1[4], std_m1[4]);
//   EXPECT_EQ(s21_m1[5], std_m1[5]);
//   EXPECT_EQ(s21_m1[6], std_m1[6]);
//   EXPECT_TRUE(s21_m2.empty());
//   EXPECT_TRUE(std_m2.empty());
// }