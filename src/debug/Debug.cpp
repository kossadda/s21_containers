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

int main()
{
  // std::vector<int> k{5};
  // container::vector<int> arr{5, 2, 4};
  int arr[] = {1, 2, 3, 4};

  container::vector<int>::iterator m;

  m = arr;

  std::cout << "\nRESULT: " << *m << "\n\n";
  



  return 0;
}