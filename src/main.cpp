/**
 * @file main.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the client code.
 * @date 19/10/2024
 */

#include <iostream>

#include "../include/input/DTMInput.hpp"

/**
 * @brief Main function which runs the program.
 * @return 0 on success, 1 on failure.
 */
int main(const int ARGC, const char* ARGV[]) {
  if (ARGC != 2) {
    std::cerr << "Usage: " << ARGV[0] << " <DTMFileName>" << std::endl;
    return EXIT_FAILURE;
  }
  const std::string FILE_NAME{ARGV[1]};
  try {
    DTM dtm{DTMInput::ReadDTM(FILE_NAME)};
    std::cout << "DTM loaded from file " + FILE_NAME;
    std::string input;
    std::cout << "\nReading input strings from console (empty string to exit)...\n";
    while (true) { 
      std::getline(std::cin, input);
      if (input.length() > 0) {
        if (dtm.Accepts(input)) {
          std::cout << "--> Accepted\n";
        } else {
          std::cout << "--> Rejected\n";
        }
        std::cout << dtm.TapesToString() << std::endl;
      } else {
        break;
      }
    }
  } catch (const std::exception& EXCEPTION) {
    std::cout << EXCEPTION.what() << std::endl;
    return EXIT_FAILURE;
  }
}
