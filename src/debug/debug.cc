/**
 * @file debug.cc
 * @author kossadda (https://github.com/kossadda)
 * @brief Separate module for manual testing
 * @version 1.0
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "./../s21_containers.h"
#include <map>
#include <set>

using map = s21::map<const int, int>;
using st = s21::multiset<const int>;
using sd = std::multiset<int>;
using smap = std::map<const int, int>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;

int main() {
  st s1{2, 4, 7, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 12, 13, 14, 13,13, 13, 13, 13, 13, 13, 18, 20, 22, 88, 88, 13, 12,11, 22, 7, 1};
  sd s2{2, 4, 7, 2, 1, 2, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 11, 12, 13, 14, 13,13, 13, 13, 13, 13, 13, 18, 20, 22, 88, 88, 13, 12,11, 22, 7, 1};

  int i = 2;

  auto s1_range = s1.equal_range(i);
  auto s2_range = s2.equal_range(i);

  std::cout << "s21 range: " << *s1_range.first << " - " << *s1_range.second << "\n";
  std::cout << "std range: " << *s2_range.first << " - " << *s2_range.second << "\n";

  std::cout << "s21 up-low: " << *s1.lower_bound(i) << " - " << *s1.upper_bound(i) << "\n";
  std::cout << "std up-low: " << *s2.lower_bound(i) << " - " << *s2.upper_bound(i) << "\n";


  return 0;
}