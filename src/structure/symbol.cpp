/**
 * @file symbol.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a Symbol.
 * @date 19/10/2024
 */

#include "../../include/structure/symbol.hpp"

/**
 * @brief Represents the epsilon symbol.
 */
const Symbol Symbol::EPSILON{'.'};

/**
 * @brief Constructs a new Symbol object.
 * 
 * @param VALUE Character value of the symbol.
 */
Symbol::Symbol(const char VALUE) : value(VALUE) {}

/**
 * @brief Constructs a new Symbol object.
 * 
 * @param VALUE String value of the symbol.
 */
Symbol::Symbol(const std::string& VALUE) : value(VALUE[0]) {}

/**
 * @brief Converts a string to a vector of symbols.
 * 
 * @param INPUT_STR String to convert.
 * @return The vector of symbols.
 */
std::vector<Symbol> Symbol::ToSymbols(const std::string& INPUT_STR) {
  std::vector<Symbol> symbols;
  for (const char SYMBOL_VALUE : INPUT_STR) {
    if (SYMBOL_VALUE == EPSILON.value) {
      continue;
    }
    symbols.emplace_back(Symbol{SYMBOL_VALUE});
  }
  return symbols;
}

/**
 * @brief Compares two symbols.
 * 
 * @param OTHER Symbol to compare.
 * @return true If the symbols are equal.
 * @return false If the symbols are different.
 */
bool Symbol::operator==(const Symbol& OTHER) const {
  return value == OTHER.value;
}

/**
 * @brief Compares two symbols.
 * 
 * @param OTHER Symbol to compare.
 * @return true If the symbols are different.
 * @return false If the symbols are equal.
 */
bool Symbol::operator!=(const Symbol& OTHER) const {
  return value != OTHER.value;
}

/**
 * @brief Compares two symbols. Used to order the symbols in a set or map.
 * 
 * @param OTHER Symbol to compare.
 * @return true If the current symbol is less than the other.
 * @return false If the current symbol is greater or equal than the other.
 */
bool Symbol::operator<(const Symbol& OTHER) const {
  return value < OTHER.value;
}

/**
 * @brief Copy assignment operator.
 * 
 * @param OTHER Symbol to assign from.
 * @return Reference to this symbol.
 */
Symbol& Symbol::operator=(const Symbol& OTHER) {
  if (this != &OTHER) {
    value = OTHER.value;
  }
  return *this;
}

/**
 * @brief Converts the symbol to a string.
 * 
 * @return The string representation of the symbol.
 */
const std::string Symbol::ToString() const {
  return std::string{value};
}