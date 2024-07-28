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

using m = s21::map<int, int>;
using p = std::pair<int, int>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;

int main() {
  tree t1{{5, 5}, {13, 13}, {1, 1}, {31, 31}, {4, 4}, {6, 6}, {22, 22}};
  tree t2{{15, 15}, {9, 9},{13, 13}, {1, 1}, {7, 7}, {42, 42}, {21, 21}, {31, 31}, {22, 22}, {45, 45}, {3, 3}, {4, 4}, {100, 100}};

  t1.merge(t2);

  std::cout << "\nSecond tree:\n";
  for(auto i : t1) {
    std::cout << i.first << " : " << i.second << std::endl;
  }

  std::cout << "\nSecond tree:\n";
  for(auto i : t2) {
    std::cout << i.first << " : " << i.second << std::endl;
  }

  // m kek{{5, "five"}, {13, "thirteen"}, {1, "one"}, {31, "thirty one"}};

  // m map;
  // map[100] = "hundred";
  // map[125] = "hundred twenty five";
  // map[7] = "seven";
  // map[9] = "nine";
  // map[15] = "fifteen";
  // map[0] = "zero";
  // map[-1] = "minus ten";

  // auto it = map.begin();
  
  // kek.merge(map);

  // std::cout << (*it).first << " : " << (*it).second << std::endl;

  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;
  // std::cout << std::endl;

  // for(auto i : kek) {
  //   std::cout << i.first << " : " << i.second << std::endl;
  // }

  // std::cout << std::endl;

  // for(auto i : map) {
  //   std::cout << i.first << " : " << i.second << std::endl;
  // }

  return 0;
}