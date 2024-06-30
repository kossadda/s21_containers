/**
 * @file mainTest.cpp
 * @author kossadda (https://github.com/kossadda)
 * @brief Main module that runs testing
 * @version 1.0
 * @date 2024-04-23
 *
 * @copyright Copyright (c) 2024
 *
 */

#include "./mainTest.h"

/**
 * @brief Main running testing
 *
 * @param[in] argc number of arguments supplied
 * @param[in] argv array of arguments
 * @return int - overall test result
 */
int main(int argc, char** argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}

/**
 * @brief For error handling. Prints the matrix given as input
 *
 * @param m - matrix
 * @param mode - what matrix is given. 0 - counted, 1 - expected
 * @return std::string - outputting a matrix as a string
 */
// std::string Print(S21Matrix& m, int mode) {
// std::ostringstream os;

// os << ((!mode) ? "  Actual: " : "Expected: ");
// for (int i = 0; i < m.GetRows(); i++) {
//   for (int j = 0; j < m.GetCols(); j++) {
//     os << m(i, j) << " ";
//   }
// }
// os << std::endl;

// return os.str();
// }