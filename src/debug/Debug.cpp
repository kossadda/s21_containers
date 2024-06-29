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

int main()
{
  vector<int> m(5);

  for(size_t i = 0; i < m.m_size; i++) {
    std::cout << m.arr[i] << " ";
  }

  return 0;
}