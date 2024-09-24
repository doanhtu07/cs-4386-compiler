#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class DFA {
  enum State {
    WhiteSpace,
    TypeRef1,
    TypeRef2,
    Identifier1,
    Identifier2,
    Number1,
    Number2,
    Assign1,
    Assign2,
    Assign3,
    Range1,
    Range2,
    Special,
  };

  unordered_set<string> RESERVED_WORDS = {"TAGS",    "BEGIN", "SEQUENCE",
                                          "INTEGER", "DATE",  "END"};
  vector<int> WHITESPACES = {9, 10, 11, 12, 13, 32};
  vector<int> SPECIALS = {(int)'"', (int)'|', (int)'(', (int)')',
                          (int)',', (int)'{', (int)'}'};
  vector<int> NUMBERS = {48, 49, 50, 51, 52, 53, 54, 55, 56, 57};

  vector<int> UPPER_AZ;
  vector<int> LOWER_AZ;
  unordered_map<string, string> TOKEN_NAMES;

private:
  State startState;
  unordered_set<State> finalStates;
  unordered_map<string, State> transitions;

public:
  DFA() {
    initAlphabets();
    initTokenNames();
    drawPartialDFA();
  }

  void initAlphabets() {
    // a..z
    for (int i = 97; i <= 122; i++) {
      LOWER_AZ.push_back(i);
    }
    // A..Z
    for (int i = 65; i <= 90; i++) {
      UPPER_AZ.push_back(i);
    }
  }

  string getStateName(State state) {
    switch (state) {
    case WhiteSpace:
      return "WhiteSpace";
    case TypeRef1:
      return "TypeRef1";
    case TypeRef2:
      return "TypeRef2";
    case Identifier1:
      return "Identifier1";
    case Identifier2:
      return "Identifier2";
    case Number1:
      return "Number1";
    case Number2:
      return "Number2";
    case Assign1:
      return "Assign1";
    case Assign2:
      return "Assign2";
    case Assign3:
      return "Assign3";
    case Range1:
      return "Range1";
    case Range2:
      return "Range2";
    case Special:
      return "Special";
    }
  }

  string encodeTransition(State state, int characterInt) {
    return getStateName(state) + " " + to_string(characterInt);
  }

  void initTokenNames() {
    TOKEN_NAMES[string(1, static_cast<char>(9))] = "HORIZONTAL TABULATION";
    TOKEN_NAMES[string(1, static_cast<char>(10))] = "LINE FEED";
    TOKEN_NAMES[string(1, static_cast<char>(11))] = "VERTICAL TABULATION";
    TOKEN_NAMES[string(1, static_cast<char>(12))] = "FORM FEED";
    TOKEN_NAMES[string(1, static_cast<char>(13))] = "CARRIAGE RETURN";
    TOKEN_NAMES[string(1, static_cast<char>(32))] = "SPACE";

    TOKEN_NAMES[string(1, '{')] = "LCURLY";
    TOKEN_NAMES[string(1, '}')] = "RCURLY";
    TOKEN_NAMES[string(1, ',')] = "COMMA";
    TOKEN_NAMES[string(1, '(')] = "LPAREN";
    TOKEN_NAMES[string(1, ')')] = "RPAREN";
    TOKEN_NAMES[string(1, '|')] = "VLINE";
    TOKEN_NAMES[string(1, '"')] = "QUOTE";

    TOKEN_NAMES[getStateName(TypeRef1)] = "TypeRef";
    TOKEN_NAMES[getStateName(Identifier1)] = "Identifier";
    TOKEN_NAMES[getStateName(Number1)] = "Number";
    TOKEN_NAMES[getStateName(Number2)] = "Number";
    TOKEN_NAMES[getStateName(Assign3)] = "ASSIGN";
    TOKEN_NAMES[getStateName(Range2)] = "Range_Separator";
  }

  void drawSingle(State start, State end, int characterInt) {
    transitions[encodeTransition(start, characterInt)] = end;
  }

  void drawMultiple(State start, State end, vector<int> characters) {
    for (int i = 0; i < characters.size(); i++) {
      int character = characters[i];
      transitions[encodeTransition(start, character)] = end;
    }
  }

  void drawPartialDFA() {
    startState = WhiteSpace;

    finalStates.insert(WhiteSpace);
    finalStates.insert(TypeRef1);
    finalStates.insert(Identifier1);
    finalStates.insert(Number1);
    finalStates.insert(Number2);
    finalStates.insert(Assign3);
    finalStates.insert(Range2);
    finalStates.insert(Special);

    drawMultiple(WhiteSpace, WhiteSpace, WHITESPACES);

    drawMultiple(WhiteSpace, TypeRef1, UPPER_AZ);
    drawMultiple(TypeRef1, TypeRef1, LOWER_AZ);
    drawMultiple(TypeRef1, TypeRef1, UPPER_AZ);
    drawMultiple(TypeRef1, TypeRef1, NUMBERS);
    drawMultiple(TypeRef1, WhiteSpace, WHITESPACES); // Final
    drawSingle(TypeRef1, TypeRef2, (int)'-');
    drawMultiple(TypeRef2, TypeRef1, LOWER_AZ);
    drawMultiple(TypeRef2, TypeRef1, UPPER_AZ);
    drawMultiple(TypeRef2, TypeRef1, NUMBERS);

    drawMultiple(WhiteSpace, Identifier1, LOWER_AZ);
    drawMultiple(Identifier1, Identifier1, LOWER_AZ);
    drawMultiple(Identifier1, Identifier1, UPPER_AZ);
    drawMultiple(Identifier1, Identifier1, NUMBERS);
    drawMultiple(Identifier1, WhiteSpace, WHITESPACES); // Final
    drawSingle(Identifier1, Identifier2, (int)'-');
    drawMultiple(Identifier2, Identifier1, LOWER_AZ);
    drawMultiple(Identifier2, Identifier1, UPPER_AZ);
    drawMultiple(Identifier2, Identifier1, NUMBERS);

    drawSingle(WhiteSpace, Number1, (int)'0');
    drawMultiple(Number1, WhiteSpace, WHITESPACES); // Final

    vector<int> subvector(NUMBERS.begin() + 1, NUMBERS.end());
    drawMultiple(WhiteSpace, Number2, subvector);
    drawMultiple(Number2, Number2, NUMBERS);
    drawMultiple(Number2, WhiteSpace, WHITESPACES); // Final

    drawSingle(WhiteSpace, Assign1, (int)':');
    drawSingle(Assign1, Assign2, (int)':');
    drawSingle(Assign2, Assign3, (int)'=');
    drawMultiple(Assign3, WhiteSpace, WHITESPACES); // Final

    drawSingle(WhiteSpace, Range1, (int)'.');
    drawSingle(Range1, Range2, (int)'.');
    drawMultiple(Range2, WhiteSpace, WHITESPACES); // Final

    drawMultiple(WhiteSpace, Special, SPECIALS);
    drawMultiple(Special, WhiteSpace, WHITESPACES); // Final
  }

  bool accepts(string input) {
    State prevState = startState;
    State currentState = startState;
    ostringstream oss; // string builder
    string currentString = "";

    for (int i = 0; i < input.length(); i++) {
      char character = input.at(i);

      if (transitions.find(encodeTransition(currentState, character)) ==
          transitions.end()) {

        oss << character;
        currentString = oss.str();

        cout << "Token: [" << currentString << "] --> " << "Invalid" << endl;
        return false;
      }

      prevState = currentState;
      currentState = transitions[encodeTransition(currentState, character)];

      if (currentString.size() == 1 &&
          TOKEN_NAMES.find(currentString) != TOKEN_NAMES.end()) {

        cout << "Token: [" << currentString << "] --> ["
             << TOKEN_NAMES[currentString] << "]" << endl;

        oss.str(""); // Clear the contents
        oss.clear(); // Reset the error state
      }

      else if (currentString.size() != 0 && prevState != currentState &&
               finalStates.find(prevState) != finalStates.end()) {

        if (RESERVED_WORDS.find(currentString) != RESERVED_WORDS.end()) {
          cout << "Token: [" << currentString << "] --> [" << "RESERVED"
               << " - " << currentString << "]" << endl;
        } else {
          cout << "Token: [" << currentString << "] --> ["
               << TOKEN_NAMES[getStateName(prevState)] << "]" << endl;
        }

        oss.str(""); // Clear the contents
        oss.clear(); // Reset the error state
      }

      oss << character;
      currentString = oss.str();
    }

    if (finalStates.find(currentState) == finalStates.end()) {
      cout << "Token: [" << currentString << "] --> " << "Incomplete" << endl;
    }

    return finalStates.find(currentState) != finalStates.end();
  }
};

string readInputFile(string path) {
  ifstream file(path); // Open the file
  if (!file) {         // Check if the file opened successfully
    throw runtime_error("Could not open the file: " + path);
  }

  ostringstream oss;   // Create a string stream
  oss << file.rdbuf(); // Read the file content into the stream

  return oss.str(); // Convert the stream to a string
}

int main(int argc, char *argv[]) {
  string input = readInputFile(argv[1]);

  DFA dfa = DFA();
  bool result = dfa.accepts(input);
  cout << "Result: " << result << endl;

  return 0;
}
