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

using maps = s21::map<int, const char *>;
using p = std::pair<int, const char *>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;

int main() {
  // std::initializer_list<p> list{{30, 1}, {10, 1}, {70, 1}, {5, 1}, {20, 1}, {50, 1}, {90, 1}, {25, 1}, {27, 1}};
  maps map{{5, "five"}, {13, "thirteen"}, {1, "one"}, {31, "thirty one"}};

  std::cout << map[2] << std::endl;

  // std::cout << t.structure();

  return 0;
}