/**
 * @file tape.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a DTM tape.
 * @date 19/10/2024
 */

#include "../../include/structure/tape.hpp"

/**
 * @brief Constructs a new Tape object.
 * 
 * @param BLANK_SYMBOL Blank symbol of the tape.
 */
Tape::Tape(const Symbol& BLANK_SYMBOL) : blankSymbol{BLANK_SYMBOL} {
  Reset();
}

/**
 * @brief Writes a symbol in the current position of the tape.
 * 
 * @param SYMBOL Symbol to write.
 */
void Tape::Write(const Symbol& SYMBOL) {
  symbols[head] = SYMBOL;
}

/**
 * @brief Reads the symbol in the current position of the tape.
 * 
 * @return Symbol in the current position of the tape.
 */
const Symbol& Tape::Read() const {
  return symbols[head];
}

/**
 * @brief Moves the head of the tape to the left, right or stays in the same position.
 * 
 * @param MOVEMENT Movement to perform.
 */
void Tape::MoveHead(const Movement& MOVEMENT) {
  switch (MOVEMENT) {
    case Movement::LEFT: {
      --head;
      if (head == 0) {
        symbols.insert(symbols.begin(), blankSymbol);
        ++head;
      }
      break;
    }
    case Movement::RIGHT: {
      ++head;
      if (head == symbols.size() - 1) {
        symbols.emplace_back(blankSymbol);
      }
      break;
    }
    case Movement::STAY:
      break;
  }
}

/**
 * @brief Resets the tape and its content.
 */
void Tape::Reset() {
  head = 1;
  symbols.clear();
  symbols.resize(3, blankSymbol);
}

/**
 * @brief Resets the tape and inserts a sequence of symbols.
 * 
 * @param SYMBOLS Symbols to insert.
 */
void Tape::InsertSymbols(const std::vector<Symbol>& SYMBOLS) {
  Reset();
  symbols.insert(symbols.begin() + head, SYMBOLS.begin(), SYMBOLS.end());
}

/**
 * @brief Returns a string representation of the tape.
 * 
 * @return A string representation of the tape.
 */
const std::string Tape::ToString() const {
  int contentStart{-1}, contentEnd;
  for (unsigned i{0}; i < symbols.size(); ++i) {
    if (contentStart == -1 && (symbols[i] != blankSymbol || i == head)) {
      contentStart = i - 1;
    }
    if (symbols[i] != blankSymbol || i == head) {
      contentEnd = i + 1;
    }
  }
  const std::vector<Symbol> CONTENT_SYMBOLS{symbols.begin() + contentStart, symbols.begin() + contentEnd + 1};
  unsigned newHead{head - contentStart};
  std::string result;
  for (unsigned i{0}; i < CONTENT_SYMBOLS.size(); ++i) {
    if (i == newHead) {
      result += ">";
    }
    result += CONTENT_SYMBOLS[i].ToString();
    if (i == newHead) {
      result += "<";
    }
    result += " ";
  }
  return result;
}