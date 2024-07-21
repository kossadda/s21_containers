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
using const_iterator = s21::vector<int>::const_iterator;
using vector = s21::vector<int>;

int main() {
  s21::vector<int> kek;
  std::vector<int> s;

  kek.insert(kek.cbegin(), 2);
  s.insert(s.cbegin(), 2);
  kek.insert(kek.cbegin(), 3);
  s.insert(s.cbegin(), 3);
  kek.insert(kek.cbegin(), 5);
  s.insert(s.cbegin(), 5);

  vector m;
  m = kek;

  for(std::vector<int>::size_type i = 0; i < m.size(); i++) {
    std::cout << m[i] << ":" << s[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "size: " << m.size() << ":" << s.size() << std::endl;
  std::cout << "capacity: " << m.capacity() << ":" << s.capacity() << std::endl;

  return 0;
}