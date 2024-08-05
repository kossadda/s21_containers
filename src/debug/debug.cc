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
  st v{1, 2, 3, 6, 7};
  auto it{v.end()};
  
  v.emplace(3);

  for(auto i : v) {
    std::cout << i << " ";
  }

  std::cout << "\n";

  return 0;
}