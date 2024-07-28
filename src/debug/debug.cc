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

using m = s21::map<const int, int>;
using md = std::map<const int, int>;
using p = std::pair<const int, int>;
using tree = s21::tree<int, int>;
using vector = s21::vector<int>;

int main() {
  m s21_m1 = {{1, 1}, {2, 2}, {3, 3}, {10, 10}, {20, 20}, {30, 30}, {40, 40}, {50, 50}};

  md std_m1 = {{1, 1}, {2, 2}, {3, 3}, {10, 10}, {20, 20}, {30, 30}, {40, 40}, {50, 50}};

  auto s21_it1 = s21_m1.begin();
  auto std_it1 = std_m1.begin();
  ++s21_it1;
  ++std_it1;
  ++s21_it1;
  ++std_it1;
  auto s21_it2{s21_it1};
  auto std_it2{std_it1};
  ++s21_it2;
  ++std_it2;
  ++s21_it2;
  ++std_it2;

  auto kk = --std_m1.end();
  s21_m1.erase(s21_it1, --s21_m1.end());
  std_m1.erase(std_it1, kk);


  for(auto i : s21_m1) {
    std::cout << i.first << " : " << i.second << std::endl;
  }
  
  std::cout << "SIZE: " << s21_m1.size() << "\n\n";
  
  for(auto i : std_m1) {
    std::cout << i.first << " : " << i.second << std::endl;
  }

  std::cout << "SIZE: " << std_m1.size() << "\n\n\n\n";

  return 0;
}