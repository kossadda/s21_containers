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
  container::vector<int> arr{1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

  container::vector<int>::iterator b;
  // b = arr.begin();
  // b += 10;

  // container::vector<int>::iterator e;
  // e = arr.end();

  std::cout << "\nRESULT: " << 1 << "\n\n";
  
  return 0;
}