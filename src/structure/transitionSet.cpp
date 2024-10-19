/**
 * @file transitionSet.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a set of transitions of a DTM state.
 * @date 19/10/2024
 */

#include "../../include/structure/transitionSet.hpp"

/**
 * @brief Empty transition result.
 */
const TransitionResult TransitionSet::EMPTY_TRANSITION_RESULTS{std::vector<Symbol>{}, std::vector<Movement>{}, nullptr};

/**
 * @brief Adds a transition to the set of transitions.
 * 
 * @param READ_SYMBOLS Symbols to read.
 * @param WRITE_SYMBOLS Symbols to write.
 * @param MOVEMENTS Movements to make.
 * @param TO_STATE State to transition to.
 */
void TransitionSet::AddTransition(const std::vector<Symbol>& READ_SYMBOLS, const std::vector<Symbol>& WRITE_SYMBOLS, const std::vector<Movement>& MOVEMENTS, State* TO_STATE) {
  transitions.emplace_back(std::make_pair(READ_SYMBOLS, std::make_tuple(WRITE_SYMBOLS, MOVEMENTS, TO_STATE)));
}

/**
 * @brief Checks if there are transitions for a given read symbols.
 * 
 * @param READ_SYMBOLS Input symbols to check.
 */
bool TransitionSet::HasTransition(const std::vector<Symbol>& READ_SYMBOLS) const {
  return std::find_if(transitions.begin(), transitions.end(), [&READ_SYMBOLS](const std::pair<std::vector<Symbol>, TransitionResult>& PAIR) { return PAIR.first == READ_SYMBOLS; }) != transitions.end();
}

/**
 * @brief Returns the transitions for a given read symbols.
 * 
 * @param READ_SYMBOLS Input symbols to check.
 */
const TransitionResult& TransitionSet::GetTransition(const std::vector<Symbol>& READ_SYMBOLS) const {
  if (!HasTransition(READ_SYMBOLS)) {
    return EMPTY_TRANSITION_RESULTS;
  }
  return std::find_if(transitions.begin(), transitions.end(), [&READ_SYMBOLS](const std::pair<std::vector<Symbol>, TransitionResult>& PAIR) { return PAIR.first == READ_SYMBOLS; })->second;
}