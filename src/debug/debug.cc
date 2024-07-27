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

using m = std::map<int, std::string>;
using p = std::pair<int, std::string>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;

int main() {
  m kek{{5, "five"}, {13, "thirteen"}, {1, "one"}, {31, "thirty one"}};

  m map;
  map[100] = "hundred";
  map[125] = "hundred twenty five";
  map[7] = "seven";
  map[9] = "nine";
  map[15] = "fifteen";
  map[0] = "zero";
  map[-10] = "minus ten";

  kek.merge(map);

  for(auto i : kek) {
    std::cout << i.first << " : " << i.second << std::endl;
  }

  std::cout << std::endl;

  for(auto i : map) {
    std::cout << i.first << " : " << i.second << std::endl;
  }

  return 0;
}