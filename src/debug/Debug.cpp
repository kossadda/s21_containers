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

int main()
{
  std::vector<int> test{1, 2, 3, 4, 5};

  test.clear();
  test.reserve(0);

  std::cout << "size:" << test.size() << std::endl;
  std::cout << "capacity:" << test.capacity() << std::endl;

  if(test.data() == nullptr) {
    std::cout << "Pts is null" << std::endl;
  }

  // vector v1{5};

  // std::cout << "size:" << v1.size() << std::endl;
  
  return 0;
}