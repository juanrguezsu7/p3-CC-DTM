/**
 * @file DTMInput.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to read a deterministic Turing Machine from a JSON file.
 * @date 19/10/2024
 * 
 * This file uses the nlohmann/json library for reading and processing JSON files.
 * nlohmann/json is distributed under the MIT License.
 * 
 * Copyright (c) 2013-2024 Niels Lohmann
 * Licensed under the MIT License: https://opensource.org/licenses/MIT
 * 
 * @see https://github.com/nlohmann/json for more information on the JSON library used.
 */

#pragma once

#include <fstream>

#include "../utils/json.hpp"
#include "../structure/DTM.hpp"

/**
 * @brief Shortcut to nlohmann::json library.
 */
using JSON = nlohmann::json;

/**
 * @brief Class to read a deterministic Turing Machine from a JSON file.
 * @example Check the examples folder to see the format of the JSON file.
 */
class DTMInput {
  public:
    static DTM ReadDTM(const std::string&);
    static void AddTransitions(std::map<std::string, State*>&, const std::vector<JSON>&, const Alphabet&, const unsigned);
  private:
    static std::string AlphabetFormatting(const Alphabet&);
    static std::string StatesFormatting(const std::map<std::string, State*>&);
};
