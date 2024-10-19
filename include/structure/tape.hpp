/**
 * @file tape.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a Tape of a Turing Machine.
 * @date 19/10/2024
 */

#pragma once

#include "symbol.hpp"
#include "movement.hpp"

/**
 * @brief Class to represent a Tape of a Turing Machine. A tape is a sequence of symbols that can be read and written by 
 *        the Turing Machine.
 */
class Tape {
  public:
    Tape(const Symbol&);
    void Write(const Symbol&);
    const Symbol& Read() const;
    void MoveHead(const Movement&);
    void Reset();
    void InsertSymbols(const std::vector<Symbol>&);
    const std::string ToString() const;
  private:
    std::vector<Symbol> symbols;
    unsigned head;
    Symbol blankSymbol;
};