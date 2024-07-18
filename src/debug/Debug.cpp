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

using iterator = containers::vector<int>::iterator;
using vector = containers::vector<int>;

int main()
{
  std::vector<int> v1{5, 6, 7, 8};

  std::cout << "\v1: " << v1[2] << "\n\n";


  // int arr1[] = {1, 2, 3, 4};
  // int arr2[] = {5, 6, 7, 8};

  // vector v1{1, 2, 3, 4, 5};
  // iterator

  // std::cout << "\nITERATOR1: " << *(++it1) << "\n\n";
  // std::cout << "\nITERATOR2: " << *it2 << "\n\n";
  
  return 0;
}