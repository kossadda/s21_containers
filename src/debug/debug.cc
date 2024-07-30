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
using set = s21::set<const int>;
using smap = std::map<const int, int>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;
using sset = std::set<int>;

int main() {
  set s{12, 2, 13, 44, 35};
  sset ss{12, 2, 13, 44, 35};

  for(auto i : s) {
    std::cout << i << " ";
  }
  std::cout << "\n\n";
  std::cout << s.max_size() << "\n\n";


  for(auto i : ss) {
    std::cout << i << " ";
  }
  std::cout << "\n\n";
  std::cout << ss.max_size() << "\n\n";


  return 0;
}