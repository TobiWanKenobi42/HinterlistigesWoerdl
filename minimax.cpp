#include "helperFunctions.h"

#include <vector>
#include <string>

#include <iostream>
using namespace std;

extern vector<string> listOfWords;

string minimax(vector<string> remainingWords) {

	// CHECK IF WE'RE ALREADY DONE
	if (remainingWords.size() == 1) {
		return remainingWords[0];
	}
	
	cout << "Start the minimax algorithm.\n";

	// FIND THE OCCURENCE OF OVERLAPS
	vector<vector<int>> overlapCounts(listOfWords.size()); // Holds for each possible guess the number how often each overlap occurs
	for (int n = 0; n < listOfWords.size(); n++) {
		for (int m = 0; m < 243; m++) {
			overlapCounts[n].push_back(0);
		}
	}
	for (int n = 0; n < listOfWords.size(); n++) {
		for (string word: remainingWords) {
			overlapCounts[n][calculateOverlap(listOfWords[n],word)]++;
		}
	}

	// MINIMIZE NUMBER OF SOLUTIONS
	int currentMinMaxCount = remainingWords.size();
	int minMaxWord = 0;
	// For each possible guess, find the number of remaining solutions
	for (int n = 0; n < listOfWords.size(); n++) {
		int currentMaximumCount = 0;
		for (int m = 0; m < 243; m++) {
			if (overlapCounts[n][m] > currentMaximumCount) {
				currentMaximumCount = overlapCounts[n][m];
			}
		}
		if (currentMaximumCount < currentMinMaxCount) {
			minMaxWord = n;
			currentMinMaxCount = currentMaximumCount;
		}
	}

	return listOfWords[minMaxWord];
}