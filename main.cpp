#include "user.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <string>

using namespace std;

// Function to generate a random code
string generateCode() {
  string code = "    ";
  srand(time(0));
  char letters[5] = {'B', 'R', 'G', 'Y', 'P'};
  for (int i = 0; i < 5;) {
    int k = rand() % 5;
    if (code.find(letters[k]) == string::npos) {
      code[i] = letters[k];
      i++;
    }
  }
  return code;
}

// Function to check the entered code against the actual code
void checkCode(string entered, string actual, int &blackPegs, int &whitePegs) {

  blackPegs = 0, whitePegs = 0;
  // Check for black pegs
  for (int i = 0; i < 4; i++) {
    if (entered[i] == actual[i]) {
      blackPegs++;
      actual[i] = ' '; // Mark the letter as used
    }
  }

  // Check for white pegs
  for (int i = 0; i < 4; i++) {
    if (entered[i] != ' ') { // Skip already used letters
      int index = actual.find(entered[i]);
      if (index !=
          string::npos) { // If the letter is present in the actual code
        whitePegs++;
        actual[index] = ' '; // Mark the letter as used
      }
    }
  }
  // Print the results
  cout << "BLACK PEGS: " << blackPegs << endl;
  cout << "WHITE PEGS: " << whitePegs << endl;
}

int main() {
  cout << "Welcome to Mastermind!" << endl;

  // Generate the actual code
  string actualCode = generateCode();
  cout << actualCode << endl;
  cout << "The code has been generated. You have 10 chances to guess the code "
          "(B, R, G, Y, P)."
       << endl;
  string pc = "";
  string enteredCode;
  int blackpegs, whitepegs, ap = 0;
  enteredCode = user(pc, blackpegs, whitepegs);
  // Allow the player to make 10 guesses
  cout << "Click 'y' if you want the computer to play, 'n' to exit: ";
  char value;
  cin >> value;
  cout << endl;
  if (value == 'n') {
    return 0;
  } else if (value == 'y') {
    while (true) {
      ap++;
      cout << "Enter your guess (in capital letters): ";
      cout << enteredCode << endl;
      if (enteredCode == actualCode) {
        cout << "Congratulations, you guessed the correct code!" << endl;
        cout << "It took " << ap << " guesses." << endl;
        break;
      } else {
        cout << "Incorrect guess. Here's how close you were: " << endl;
        checkCode(enteredCode, actualCode, blackpegs, whitepegs);
      }
      pc = enteredCode;
      enteredCode = user(pc, blackpegs, whitepegs);
    }
    cout << "Thanks for playing!" << endl;
  }

  else {
    cout << "Error!";
  }

  return 0;
}
