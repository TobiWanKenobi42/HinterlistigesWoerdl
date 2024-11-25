#include <string>
#include <vector>

using namespace std;

#ifndef HELPERFUNCTIONS_H
#define HELPERFUNCTIONS_H

string checkInput(string wordGuess);
vector<vector<string>> calculateOverlapList(string wordGuess, vector<string> allWords);
unsigned __int8 calculateOverlap(string wordGuess, string wordSolution);
void printOverlap(string guess, unsigned __int8 overlap);

#endif