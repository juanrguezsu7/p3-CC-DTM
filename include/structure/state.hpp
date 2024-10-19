/**
 * @file state.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a DTM state.
 * @date 19/10/2024
 */

#pragma once

#include "transitionSet.hpp"

/**
 * @brief Class to represent a DTM state. A state is a node in the DTM graph that contains a set of transitions to other states.
 */
class State {
  public:
    State(const std::string&);
    const std::string& ToString() const;
    const TransitionSet& Transitions() const;
    TransitionSet& Transitions();
    void SetAsFinal();
    bool IsFinal() const;
  private:
    const std::string name;
    TransitionSet transitions;
    bool isFinal;
};
