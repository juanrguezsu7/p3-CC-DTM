/**
 * @file DTM.hpp
 * @author Juan Rodríguez Suárez
 * @brief Contains the class to represent a deterministic Turing Machine.
 * @date 19/10/2024
 */

#pragma once

#include <set>
#include <numeric>

#include "state.hpp"
#include "tape.hpp"

/**
 * @brief Type to represent the alphabet of the stack of a DTM.
 */
using Alphabet = std::set<Symbol>;

/**
 * @brief Class to represent a deterministic Turing Machine (DTM). The implemented DTM has the following characteristics:
 * 
 *       - The DTM has an arbitrary number of independent tapes.
 * 
 *       - On each transition, the DTM possess simultaneous writing and moving capabilities.
 * 
 *       - The DTM may not move on a transition (represented by the symbol 'S').
 * 
 *       - It has a virtual infinite tape to both sides.
 */
class DTM {
  public:
    DTM(const std::vector<State*>&, const Alphabet&, const Alphabet&, State*, const Symbol&, const unsigned);
    bool Accepts(const std::string&);
    std::string TapesToString() const;
    ~DTM();
  private:
    std::vector<State*> states;
    Alphabet alphabet;
    Alphabet tapeAlphabet;
    State* initialState;
    Symbol blankSymbol;
    unsigned numberOfTapes; 
    std::vector<Tape> tapes;
};
