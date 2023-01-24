#include <algorithm>
#include <iostream>
#include <set>
#include <string>
#include <utility>
#include <vector>

using namespace std;

// Function to evaluate a guess and return the number of black and white pegs
pair<int, int> evaluateGuess(const string &code, const string &guess) {
  int blackPegs = 0, whitePegs = 0;
  string codeCopy = code, guessCopy = guess;
  // Count the number of black pegs
  for (int i = 0; i < 4; i++) {
    if (codeCopy[i] == guessCopy[i]) {
      blackPegs++;
      codeCopy[i] = guessCopy[i] = ' '; // Mark the peg as used
    }
  }
  // Count the number of white pegs
  for (int i = 0; i < 4; i++) {
    if (guessCopy[i] == ' ')
      continue; // Skip the used pegs
    for (int j = 0; j < 4; j++) {
      if (codeCopy[j] == guessCopy[i]) {
        whitePegs++;
        codeCopy[j] = ' '; // Mark the peg as used
        break;
      }
    }
  }
  return make_pair(blackPegs, whitePegs);
}

string user(string previous_code, int blackpeg, int whitepeg, set<string> &usedCodes) {
  string nextGuess;
  while (true) {
    string letters = "BRGPY";
    vector<string> codeList;
    for (char c1 : letters) {
      for (char c2 : letters) {
        for (char c3 : letters) {
          for (char c4 : letters) {
            // Check if the code has no repeating letters
            if (c1 != c2 && c1 != c3 && c1 != c4 && c2 != c3 && c2 != c4 &&
                c3 != c4) {
              codeList.push_back(string(1, c1) + c2 + c3 + c4);
            }
          }
        }
      }
    }
    // Eliminate codes that are not consistent with the feedback
    for (int i = 0; i < codeList.size(); i++) {
      auto res = evaluateGuess(codeList[i], previous_code);
      if (res.first != blackpeg || res.second != whitepeg) {
        codeList.erase(codeList.begin() + i);
        i--;
      }
    }
    srand(time(0));
    random_shuffle(codeList.begin(), codeList.end());
    // Choose the next guess
    if (usedCodes.count(codeList[0]) == 0) {
      nextGuess = codeList[0];
      break;
    }
  }
  usedCodes.insert(nextGuess);
  return nextGuess;
}