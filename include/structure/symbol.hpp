/**
 * @file symbol.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a Symbol.
 * @date 19/10/2024
 */

#pragma once

#include <string>
#include <vector>

/**
 * @brief Class to represent a Symbol. A symbol is a character of the alphabet of a DTM. An input string is formed by a sequence of symbols.
 */
class Symbol {
  public:
    static const Symbol EPSILON;

    Symbol(const char);
    Symbol(const std::string&);
    static std::vector<Symbol> ToSymbols(const std::string&);
    bool operator==(const Symbol&) const;
    bool operator!=(const Symbol&) const;
    bool operator<(const Symbol&) const;
    Symbol& operator=(const Symbol&);
    const std::string ToString() const;
  private: 
    char value;
};