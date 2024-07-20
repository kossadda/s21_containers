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
  s21::vector<int> test;

  test.insert(test.begin(), 5);
  // std::vector<int> test{11, 22, 33, 44, 55};
  // std::vector<int>::iterator it{test.begin() + 3};

  // auto std_it = test.insert(it, 7, 7);

  for(std::vector<int>::size_type i = 0; i < test.size(); i++) {
    std::cout << test[i] << " ";
  }
  std::cout << std::endl;

  std::cout << "size:" << test.size() << std::endl;
  std::cout << "capacity:" << test.capacity() << std::endl;
  // std::cout << "check std it: " << *(std_it + 7) << std::endl;

  // std::cout << test.size() << std::endl;
  // std::cout << *it << std::endl;
  
  // vector v1{5};

  // std::cout << "size:" << v1.size() << std::endl;
  
  return 0;
}