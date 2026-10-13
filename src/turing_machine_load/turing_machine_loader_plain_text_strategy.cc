// University of La Laguna
// School of Engineering and Technology
// Bachelor's Degree in Computer Engineering
// Course: Computational Complexity
// Year: 4th
// Assignment 2: Turing Machine
// Author: Javier Acosta Portocarrero
// Date: 04/10/2026
// File turing_machine_loader_plain_text_strategy.cc: implementation file.
// Contains the implementation of the TuringMachineLoaderPlainTextStrategy class.

#include "../../include/turing_machine_load/turing_machine_loader_plain_text_strategy.h"
#include "../../include/exceptions/input_exception.h"

#include <sstream>
#include <vector>

/**
 * @brief Loads a Turing machine from a plain text configuration file.
 * 
 * @param file_path Path to the configuration file.
 * @return The loaded Turing machine.
 * @throws InputException If the configuration file is invalid or cannot be opened.
 */
TuringMachine TuringMachineLoaderPlainTextStrategy::LoadTuringMachine(const std::string& file_path) const {
  std::ifstream input_file{file_path};
  if (!input_file.is_open()) {
    throw InputException("Could not open configuration file '" + file_path + "'.");
  }
  unsigned line_number = 0;
  const std::set<std::string> automaton_states = ReadStates(GetNextContentLine(input_file, line_number, "states"), line_number);
  const std::set<Symbol> input_alphabet = ReadAlphabet(GetNextContentLine(input_file, line_number, "input alphabet"), line_number, "input alphabet");
  const std::set<Symbol> strings_alphabet = ReadAlphabet(GetNextContentLine(input_file, line_number, "string alphabet"), line_number, "string alphabet");
  for (const Symbol& symbol : input_alphabet) {
    if (!strings_alphabet.contains(symbol)) {
      throw InputException("Line " + std::to_string(line_number) + ": Input alphabet must be contained in the string alphabet.");
    }
  }

  const std::string start_state = ReadSingleElement(GetNextContentLine(input_file, line_number, "start state"), line_number, "start state");
  if (!automaton_states.contains(start_state)) {
    throw InputException("Line " + std::to_string(line_number) + ": Start state doesn't belong to the set of states.");
  }

  const std::string white_symbol_string = ReadSingleElement(GetNextContentLine(input_file, line_number, "white symbol"), line_number, "white symbol");
  if (white_symbol_string.size() != 1) {
    throw InputException("Line " + std::to_string(line_number) + ": White symbol must contain one character.");
  }
  const Symbol white_symbol = white_symbol_string[0];
  if (!strings_alphabet.contains(white_symbol)) {
    throw InputException("Line " + std::to_string(line_number) + ": White symbol doesn't belong to the string alphabet.");
  }
  if (input_alphabet.contains(white_symbol)) {
    throw InputException("Line " + std::to_string(line_number) + ": White symbol can't belong to the input alphabet.");
  }

  const std::set<std::string> acceptance_automaton_states = ReadStates(GetNextContentLine(input_file, line_number, "acceptance states"), line_number);
  for (const std::string& acceptance_state : acceptance_automaton_states) {
    if (!automaton_states.contains(acceptance_state)) {
      throw InputException("Line " + std::to_string(line_number) + ": Acceptance state '" + acceptance_state + "' doesn't belong to the set of states.");
    }
  }
  const unsigned amount_of_strings = ReadAmountOfStrings(GetNextContentLine(input_file, line_number, "amount of strings"), line_number);

  TransitionFunction transition_function;
  std::string line;
  unsigned transition_identifier = 0;
  while (std::getline(input_file, line)) {
    ++line_number;
    line = RemoveCommentsAndWhitespace(line);
    if (line.empty()) {
      continue;
    }
    ReadTransition(line, line_number, transition_identifier, amount_of_strings, automaton_states, strings_alphabet, transition_function);
    ++transition_identifier;
  }
  return TuringMachine(transition_function, input_alphabet, strings_alphabet, automaton_states, start_state,
      amount_of_strings, white_symbol, acceptance_automaton_states);
}

/**
 * @brief Reads the next non-empty line from the input file, removing comments and whitespace.
 * 
 * @param input_file Input file stream.
 * @param line_number Current line number in the file.
 * @param expected_content Description of the expected content for error messages.
 * @return The next non-empty line from the input file.
 * @throws InputException If the end of the file is reached unexpectedly.
 */
std::string TuringMachineLoaderPlainTextStrategy::GetNextContentLine(std::ifstream& input_file, unsigned& line_number, const std::string& expected_content) const {
  std::string line;
  while (std::getline(input_file, line)) {
    ++line_number;
    line = RemoveCommentsAndWhitespace(line);
    if (!line.empty()) {
      return line;
    }
  }
  throw InputException("Unexpected end of configuration file while reading " + expected_content + ".");
}

/**
 * @brief Removes comments and leading/trailing whitespace from a line.
 * 
 * @param line The line to process.
 * @return The processed line with comments and whitespace removed.
 */
std::string TuringMachineLoaderPlainTextStrategy::RemoveCommentsAndWhitespace(const std::string& line) const {
  std::string processed_line = line.substr(0, line.find('#'));
  const size_t first_character = processed_line.find_first_not_of(" \t\r\n");
  if (first_character == std::string::npos) {
    return "";
  }
  const size_t last_character = processed_line.find_last_not_of(" \t\r\n");
  return processed_line.substr(first_character, last_character - first_character + 1);
}

/**
 * @brief Reads the set of states from a line.
 * 
 * @param line The line containing the states.
 * @param line_number Current line number in the file.
 * @return The set of states.
 * @throws InputException If the state set is empty.
 */
std::set<std::string> TuringMachineLoaderPlainTextStrategy::ReadStates(const std::string& line, unsigned line_number) const {
  std::istringstream line_stream{line};
  std::set<std::string> states;
  std::string state;
  while (line_stream >> state) {
    states.insert(state);
  }
  if (states.empty()) {
    throw InputException("Line " + std::to_string(line_number) + ": State set can't be empty.");
  }
  return states;
}

/**
 * @brief Reads the alphabet from a line.
 * 
 * @param line The line containing the alphabet.
 * @param line_number Current line number in the file.
 * @param alphabet_name Name of the alphabet for error messages.
 * @return The set of symbols in the alphabet.
 * @throws InputException If the alphabet is empty or contains invalid symbols.
 */
std::set<Symbol> TuringMachineLoaderPlainTextStrategy::ReadAlphabet(const std::string& line, unsigned line_number, const std::string& alphabet_name) const {
  std::istringstream line_stream{line};
  std::set<Symbol> alphabet;
  std::string symbol;
  while (line_stream >> symbol) {
    if (symbol.size() != 1) {
      throw InputException("Line " + std::to_string(line_number) + ": Every symbol in the " + alphabet_name + " must contain one character.");
    }
    alphabet.insert(symbol[0]);
  }
  if (alphabet.empty()) {
    throw InputException("Line " + std::to_string(line_number) + ": " + alphabet_name + " can't be empty.");
  }
  return alphabet;
}

/**
 * @brief Reads a single element from a line.
 * 
 * @param line The line containing the element.
 * @param line_number Current line number in the file.
 * @param element_name Name of the element for error messages.
 * @return The read element as a string.
 * @throws InputException If the line does not contain exactly one element.
 */
std::string TuringMachineLoaderPlainTextStrategy::ReadSingleElement(const std::string& line, unsigned line_number, const std::string& element_name) const {
  std::istringstream line_stream{line};
  std::string element;
  std::string additional_element;
  if (!(line_stream >> element) || line_stream >> additional_element) {
    throw InputException("Line " + std::to_string(line_number) + ": " + element_name + " must contain one element.");
  }
  return element;
}

/**
 * @brief Reads the amount of strings from a line.
 * 
 * @param line The line containing the amount of strings.
 * @param line_number Current line number in the file.
 * @return The amount of strings as an unsigned integer.
 * @throws InputException If the amount is not a positive integer or if there are additional elements in the line.
 */
unsigned TuringMachineLoaderPlainTextStrategy::ReadAmountOfStrings(const std::string& line, unsigned line_number) const {
  std::istringstream line_stream{line};
  unsigned amount_of_strings;
  std::string additional_element;
  if (!(line_stream >> amount_of_strings) || amount_of_strings == 0 || line_stream >> additional_element) {
    throw InputException("Line " + std::to_string(line_number) + ": Amount of strings must be a positive integer.");
  }
  return amount_of_strings;
}

/**
 * @brief Reads a transition from a line and adds it to the transition function.
 * 
 * @param line The line containing the transition.
 * @param line_number Current line number in the file.
 * @param transition_identifier Identifier for the transition for error messages.
 * @param amount_of_strings Number of strings in the Turing machine.
 * @param automaton_states Set of valid states in the Turing machine.
 * @param strings_alphabet Set of valid symbols in the Turing machine's alphabet.
 * @param transition_function The transition function to which the new transition will be added.
 * @throws InputException If the transition is invalid or if there are duplicate transitions.
 */
void TuringMachineLoaderPlainTextStrategy::ReadTransition(const std::string& line, unsigned line_number, unsigned transition_identifier,
    unsigned amount_of_strings, const std::set<std::string>& automaton_states, const std::set<Symbol>& strings_alphabet,
    TransitionFunction& transition_function) const {
  std::istringstream line_stream{line};
  std::vector<std::string> elements;
  std::string element;
  while (line_stream >> element) {
    elements.emplace_back(element);
  }
  const unsigned expected_elements = 2 + 3 * amount_of_strings;
  if (elements.size() != expected_elements) {
    throw InputException("Line " + std::to_string(line_number) + ": Transition " + std::to_string(transition_identifier) + " must contain " + std::to_string(expected_elements) + " elements.");
  }

  const std::string& origin_state = elements[0];
  if (!automaton_states.contains(origin_state)) {
    throw InputException("Line " + std::to_string(line_number) + ": Origin state '" + origin_state + "' doesn't belong to the set of states.");
  }
  std::string entry_symbols = "";
  for (unsigned i = 0; i < amount_of_strings; ++i) {
    const std::string& read_symbol = elements[i + 1];
    if (read_symbol.size() != 1 || !strings_alphabet.contains(read_symbol[0])) {
      throw InputException("Line " + std::to_string(line_number) + ": Invalid read symbol '" + read_symbol + "'.");
    }
    entry_symbols += read_symbol[0];
  }

  const std::string& destiny_state = elements[amount_of_strings + 1];
  if (!automaton_states.contains(destiny_state)) {
    throw InputException("Line " + std::to_string(line_number) + ": Destiny state '" + destiny_state + "' doesn't belong to the set of states.");
  }
  std::vector<Symbol> symbols_to_write;
  std::vector<StringMovements> head_movements;
  unsigned effects_start = amount_of_strings + 2;
  for (unsigned i = 0; i < amount_of_strings; ++i) {
    const std::string& write_symbol = elements[effects_start + i * 2];
    const std::string& movement = elements[effects_start + i * 2 + 1];
    if (write_symbol.size() != 1 || !strings_alphabet.contains(write_symbol[0])) {
      throw InputException("Line " + std::to_string(line_number) + ": Invalid write symbol '" + write_symbol + "'.");
    }
    symbols_to_write.emplace_back(write_symbol[0]);
    if (movement == "R") {
      head_movements.emplace_back(right);
    } else if (movement == "L") {
      head_movements.emplace_back(left);
    } else if (movement == "S") {
      head_movements.emplace_back(stop);
    } else {
      throw InputException("Line " + std::to_string(line_number) + ": Movement must be 'L', 'R' or 'S'.");
    }
  }

  InstantaneousDescription requirements{origin_state, entry_symbols};
  if (transition_function.GetPossibleTransition(requirements) != nullptr) {
    throw InputException("Line " + std::to_string(line_number) + ": More than one transition has the same requirements.");
  }
  transition_function.AddNewTransition(requirements, TransitionEffects(destiny_state, symbols_to_write, head_movements));
}