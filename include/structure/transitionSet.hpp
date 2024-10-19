/**
 * @file transitionSet.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a set of transitions of a DTM state.
 * @date 19/10/2024
 */

#pragma once

#include <stdexcept>
#include <algorithm>

#include "symbol.hpp"
#include "movement.hpp"

class State;

/**
 * @brief Type to represent the result of a transition.
 */
using TransitionResult = std::tuple<std::vector<Symbol>, std::vector<Movement>, State*>;

class TransitionSet {
  public:
    static const TransitionResult EMPTY_TRANSITION_RESULTS;

    void AddTransition(const std::vector<Symbol>&, const std::vector<Symbol>&, const std::vector<Movement>&, State*);
    bool HasTransition(const std::vector<Symbol>&) const;
    const TransitionResult& GetTransition(const std::vector<Symbol>&) const;
  private:
    std::vector<std::pair<std::vector<Symbol>, TransitionResult>> transitions;

};
