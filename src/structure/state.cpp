/**
 * @file state.cpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the definition of the class to represent a DTM state.
 * @date 19/10/2024
 */

#include "../../include/structure/state.hpp"

/**
 * @brief Constructs a new State object.
 * 
 * @param NAME Name of the state.
 */
State::State(const std::string& NAME) : name(NAME) {
  isFinal = false;
}

/**
 * @brief Returns the name of the state.
 * 
 * @return The name of the state.
 */
const std::string& State::ToString() const { 
  return name; 
}

/**
 * @brief Returns a read-only reference to the transitions of the state.
 * 
 * @return A read-only reference to the transitions of the state.
 */
const TransitionSet& State::Transitions() const { 
  return transitions; 
}

/**
 * @brief Returns a reference to the transitions of the state.
 * 
 * @return A reference to the transitions of the state.
 */
TransitionSet& State::Transitions() { 
  return transitions;
}

/**
 * @brief Sets the state as final.
 */
void State::SetAsFinal() { 
  isFinal = true;
}

/**
 * @brief Checks if the state is final.
 * 
 * @return true If the state is final.
 * @return false If the state is not final.
 */
bool State::IsFinal() const { 
  return isFinal;
}