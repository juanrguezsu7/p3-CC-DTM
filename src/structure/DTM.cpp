/**
 * @file DTM.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a deterministic Turing Machine.
 * @date 19/10/2024
 */

#include "../../include/structure/DTM.hpp"

/**
 * @brief Constructs a new DTM object.
 * 
 * @param STATES Set of states of the DTM.
 * @param ALPHABET Input alphabet of the DTM.
 * @param TAPE_ALPHABET Tape alphabet of the DTM.
 * @param givenInitialState Initial state of the DTM.
 * @param BLANK_SYMBOL Blank symbol of the DTM.
 * @param NUMBER_TAPES Number of tapes of the DTM.
 */
DTM::DTM(const std::vector<State*>& STATES, const Alphabet& ALPHABET, const Alphabet& TAPE_ALPHABET, State* givenInitialState, const Symbol& BLANK_SYMBOL, const unsigned NUMBER_TAPES) : 
         states{STATES}, alphabet{ALPHABET}, tapeAlphabet{TAPE_ALPHABET}, initialState{givenInitialState}, blankSymbol{BLANK_SYMBOL}, numberOfTapes{NUMBER_TAPES} {
  for (unsigned i{0}; i < NUMBER_TAPES; ++i) {
    tapes.emplace_back(Tape{BLANK_SYMBOL});
  }
}

/**
 * @brief Checks if the DTM accepts a given input string.
 * 
 * @param INPUT Input string to check.
 * @return true If the DTM accepts the input string.
 * @return false If the DTM does not accept the input string.
 * @throw std::invalid_argument If the input string contains symbols not found in the alphabet.
 */
bool DTM::Accepts(const std::string& INPUT) {
  for (auto& TAPE : tapes) {
    TAPE.Reset();
  }
  const std::vector<Symbol> INPUT_SYMBOLS{Symbol::ToSymbols(INPUT)};
  for (const auto& SYMBOL : INPUT_SYMBOLS) {
    if (alphabet.find(SYMBOL) == alphabet.end()) {
      const std::string ALPHABET_STR{std::accumulate(alphabet.begin(), alphabet.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; })};
      throw std::invalid_argument{"Runtime error: Input symbol: '" + SYMBOL.ToString() + "' not found in alphabet ( " + ALPHABET_STR + ")"};
    }
  }
  tapes[0].InsertSymbols(INPUT_SYMBOLS);
  State* currentState{initialState};
  while (true) {
    const std::vector<Symbol> READ_SYMBOLS{std::accumulate(tapes.begin(), tapes.end(), std::vector<Symbol>{}, [](std::vector<Symbol>& ACCOUNT, const Tape& TAPE) { ACCOUNT.emplace_back(TAPE.Read()); return ACCOUNT; })};
    if (!currentState->Transitions().HasTransition(READ_SYMBOLS)) {
      return currentState->IsFinal();
    }
    const TransitionResult& TRANSITION{currentState->Transitions().GetTransition(READ_SYMBOLS)};
    for (unsigned i{0}; i < numberOfTapes; ++i) {
      tapes[i].Write(std::get<0>(TRANSITION)[i]);
      tapes[i].MoveHead(std::get<1>(TRANSITION)[i]);
    }
    currentState = std::get<2>(TRANSITION);
  }
}

/**
 * @brief Returns a string representation of the tapes of the DTM.
 * 
 * @return A string representation of the tapes of the DTM.
 */
std::string DTM::TapesToString() const {
  std::string result;
  for (int i{0}; i < tapes.size(); ++i) {
    result += "Tape " + std::to_string(tapes.size() - i) + ": " + tapes[tapes.size() - i - 1].ToString() + "\n";
  }
  return result;
}

/**
 * @brief Destroys the DTM object, freeing the memory of the states.
 */
DTM::~DTM() {
  for (const auto& STATE : states) {
    delete STATE;
  }
}