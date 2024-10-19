/**
 * @file DTMInput.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to read a DTM from a JSON file.
 * @date 19/10/2024
 */

#include "../../include/input/DTMInput.hpp"

/**
 * @brief Reads a DTM from a file. The format is specified in the class documentation.
 * 
 * @param JSON_FILENAME Name of the file to read the DRM from.
 * @return The DTM read from the file.
 * @throw std::invalid_argument If the file does not exist or the DTM specified in the file is invalid.
 */
DTM DTMInput::ReadDTM(const std::string& JSON_FILENAME) {
  std::ifstream reader{JSON_FILENAME};
  if (!reader.is_open()) {
    throw std::invalid_argument{"Reading file error: File '" + JSON_FILENAME + "' not found"};
  }
  JSON json;
  try {
    reader >> json;
  } catch (const JSON::parse_error& ERROR) {
    throw std::invalid_argument{"Reading file error: " + std::string{ERROR.what()}};
  }
  const Symbol BLANK_SYMBOL{json["blankSymbol"]};
  std::map<std::string, State*> states;
  for (const auto& STATE : json["states"]) {
    states.emplace(STATE, new State{STATE});
  }
  Alphabet tapeAlphabet;
  for (const auto& SYMBOL : json["tapeAlphabet"]) {
    tapeAlphabet.insert(Symbol{SYMBOL});
  }
  if (tapeAlphabet.find(BLANK_SYMBOL) == tapeAlphabet.end()) {
    throw std::invalid_argument{"Reading file error: Blank symbol: '" + BLANK_SYMBOL.ToString() + "' not found in tape alphabet ( " + AlphabetFormatting(tapeAlphabet) + ")"}; 
  }
  Alphabet alphabet;
  for (const auto& SYMBOL : json["inputAlphabet"]) {
    const Symbol TO_ADD{SYMBOL};
    if (TO_ADD == BLANK_SYMBOL) {
      throw std::invalid_argument{"Reading file error: Tape alphabet cannot contain the blank symbol"};
    }
    if (tapeAlphabet.find(TO_ADD) == tapeAlphabet.end()) {
      throw std::invalid_argument{"Reading file error: Input symbol: '" + SYMBOL.get<std::string>() + "' not found in tape alphabet ( " + AlphabetFormatting(tapeAlphabet) + ")"}; 
    }
    alphabet.insert(TO_ADD);
  }
  if (states.find(json["initialState"]) == states.end()) {
    throw std::invalid_argument{"Reading file error: Initial state: '" + json["initialState"].get<std::string>() + "' not found in states ( " + StatesFormatting(states) + ")"}; 
  }
  State* initialState{states[json["initialState"]]};
  for (const auto& STATE : json["finalStates"]) {
    if (states.find(STATE) == states.end()) {
      throw std::invalid_argument{"Reading file error: Final state: '" + STATE.get<std::string>() + "' not found in states ( " + StatesFormatting(states) + ")"}; 
    }
    states[STATE]->SetAsFinal();
  }
  const unsigned NUMBER_OF_TAPES{json["numTapes"]};
  const std::vector<JSON> TRANSITIONS = json["transitions"];
  AddTransitions(states, TRANSITIONS, tapeAlphabet, NUMBER_OF_TAPES);
  const std::vector<State*> STATES{std::accumulate(states.begin(), states.end(), std::vector<State*>{}, [](std::vector<State*>& ACCOUNT, const std::pair<std::string, State*>& PAIR) { ACCOUNT.emplace_back(PAIR.second); return ACCOUNT; })};
  return DTM{STATES, alphabet, tapeAlphabet, initialState, BLANK_SYMBOL, NUMBER_OF_TAPES};
}

/**
 * @brief Adds the transitions to the states.
 * 
 * @param STATES States to add the transitions
 * @param JSON_TRANSITIONS Transitions to add.
 * @param TAPE_ALPHABET Alphabet of the tape.
 * @param NUMBER_OF_TAPES Number of tapes of the DTM.
 * @throw std::invalid_argument If the transitions are invalid
 */
void DTMInput::AddTransitions(std::map<std::string, State*>& states, const std::vector<JSON>& JSON_TRANSITIONS, const Alphabet& TAPE_ALPHABET, const unsigned NUMBER_OF_TAPES) {
  for (const auto& TRANSITION : JSON_TRANSITIONS) {
    if (states.find(TRANSITION["fromState"]) == states.end()) {
      throw std::invalid_argument{"Reading file error: From state: '" + TRANSITION["fromState"].get<std::string>() + "' not found in states ( " + StatesFormatting(states) + ")"};
    }
    State* fromState{states[TRANSITION["fromState"]]};
    if (states.find(TRANSITION["toState"]) == states.end()) {
      throw std::invalid_argument{"Reading file error: To state: '" + TRANSITION["toState"].get<std::string>() + "' not found in states ( " + StatesFormatting(states) + ")"};
    }
    State* toState{states[TRANSITION["toState"]]};
    const std::vector<Symbol> READ_SYMBOLS{std::accumulate(TRANSITION["readSymbols"].begin(), TRANSITION["readSymbols"].end(), std::vector<Symbol>{}, [](std::vector<Symbol>& ACCOUNT, const std::string& SYMBOL) { ACCOUNT.emplace_back(Symbol{SYMBOL}); return ACCOUNT; })};
    for (const auto& SYMBOL : READ_SYMBOLS) {
      if (TAPE_ALPHABET.find(SYMBOL) == TAPE_ALPHABET.end()) {
        throw std::invalid_argument{"Reading file error: Read symbol: '" + SYMBOL.ToString() + "' not found in tape alphabet ( " + AlphabetFormatting(TAPE_ALPHABET) + ")"};
      }
    }
    if (READ_SYMBOLS.size() != NUMBER_OF_TAPES) {
      throw std::invalid_argument{"Reading file error: Number of read symbols: " + std::to_string(READ_SYMBOLS.size()) + " does not match the number of tapes: " + std::to_string(NUMBER_OF_TAPES)};
    }
    const std::vector<Symbol> WRITE_SYMBOLS{std::accumulate(TRANSITION["writeSymbols"].begin(), TRANSITION["writeSymbols"].end(), std::vector<Symbol>{}, [](std::vector<Symbol>& ACCOUNT, const std::string& SYMBOL) { ACCOUNT.emplace_back(Symbol{SYMBOL}); return ACCOUNT; })};
    for (const auto& SYMBOL : WRITE_SYMBOLS) {
      if (TAPE_ALPHABET.find(SYMBOL) == TAPE_ALPHABET.end()) {
        throw std::invalid_argument{"Reading file error: Write symbol: '" + SYMBOL.ToString() + "' not found in tape alphabet ( " + AlphabetFormatting(TAPE_ALPHABET) + ")"};
      }
    }
    if (WRITE_SYMBOLS.size() != NUMBER_OF_TAPES) {
      throw std::invalid_argument{"Reading file error: Number of write symbols: " + std::to_string(WRITE_SYMBOLS.size()) + " does not match the number of tapes: " + std::to_string(NUMBER_OF_TAPES)};
    }
    const std::vector<Movement> MOVEMENTS{std::accumulate(TRANSITION["tapeMoves"].begin(), TRANSITION["tapeMoves"].end(), std::vector<Movement>{}, [](std::vector<Movement>& ACCOUNT, const std::string& MOVEMENT) { ACCOUNT.emplace_back(static_cast<Movement>(MOVEMENT[0])); return ACCOUNT; })};
    for (const auto& MOVEMENT : MOVEMENTS) {
      if (MOVEMENT != Movement::LEFT && MOVEMENT != Movement::RIGHT && MOVEMENT != Movement::STAY) {
        throw std::invalid_argument{"Reading file error: Invalid movement: '" + std::string{static_cast<char>(MOVEMENT)} + "'"};
      }
    }
    if (MOVEMENTS.size() != NUMBER_OF_TAPES) {
      throw std::invalid_argument{"Reading file error: Number of movements: " + std::to_string(MOVEMENTS.size()) + " does not match the number of tapes: " + std::to_string(NUMBER_OF_TAPES)};
    }
    fromState->Transitions().AddTransition(READ_SYMBOLS, WRITE_SYMBOLS, MOVEMENTS, toState);
  }
}

/**
 * @brief Formats the alphabet to a string.
 * 
 * @param ALPHABET Alphabet to format.
 * @return The formatted alphabet.
 */
std::string DTMInput::AlphabetFormatting(const Alphabet& ALPHABET) {
  return std::accumulate(ALPHABET.begin(), ALPHABET.end(), std::string{}, [](const std::string& ACCOUNT, const Symbol& SYMBOL) { return ACCOUNT + SYMBOL.ToString() + " "; });
}

/**
 * @brief Formats the states to a string.
 * 
 * @param STATES States to format.
 * @return The formatted states.
 */
std::string DTMInput::StatesFormatting(const std::map<std::string, State*>& STATES) {
  return std::accumulate(STATES.begin(), STATES.end(), std::string{}, [](const std::string& ACCOUNT, const std::pair<std::string, State*>& PAIR) { return ACCOUNT + PAIR.first + " "; });
}
