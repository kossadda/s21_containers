/**
 * @file debug.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Separate module for manual testing
 * @version 1.0
 * @date 2024-04-18
 * 
 * @copyright Copyright (c) 2024
 * 
 */


#include "./../s21_containers.h"
#include <vector>

using iterator = s21::vector<int>::iterator;
using vector = s21::vector<int>;

int main() {
  s21::vector<int> m;
  std::vector<int> s;

  for (vector::size_type i = 100; i < 105; i++) {
    m.push_back(i);
    s.push_back(i);
  }
  
  for(std::vector<int>::size_type i = 0; i < m.size(); i++) {
    std::cout << m[i] << ":" << s[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "size: " << m.size() << ":" << s.size() << std::endl;
  std::cout << "capacity: " << m.capacity() << ":" << s.capacity() << std::endl;

  return 0;
}