#include "helperFunctions.h"

#include <string>
#include <vector>
#include <algorithm>
#include <iostream>
#include <windows.h>
using namespace std;

extern vector<string> listOfWords;

string checkInput(string wordGuess) {
	// convert to upper-case letters, and check whether it only consists of letters
	for (int n = 0; n < wordGuess.length(); n++) {
		if (97 <= wordGuess[n] && wordGuess[n] <= 122) {
			wordGuess[n] -= 32;
		}
		if (65 > wordGuess[n] || wordGuess[n] > 90) {
			throw 1;
		}
	}
	
	// Check that length of word is 5
	if (wordGuess.length() != 5) { throw 2; }

	// Check whether the guess is in the list of words
	if (!(binary_search(listOfWords.begin(), listOfWords.end(), wordGuess))) {
		throw 3;
	}

	return wordGuess;
}

vector<vector<string>> calculateOverlapList(string wordGuess, vector<string> allWords) {
	// INPUT CHECKS
	// Check word length==5, convert to upper-case letters, and check whether it only consists of letters
	if (wordGuess.length() != 5) { throw 1; }

	for (int n = 0; n < 5; n++) {
		if (97 <= wordGuess[n] && wordGuess[n] <= 122) {
			wordGuess[n] -= 32;
		}
		if (65 > wordGuess[n] || wordGuess[n] > 90) {
			throw 1;
		}
	}

	vector<vector<string>> overlapList(243);	// There are 243 possible values for the overlap, sort the words by overlap
	for (string word: allWords) {
		overlapList[calculateOverlap(wordGuess, word)].push_back(word);	// Add the word to the list of words with a specific overlap
	}
	return overlapList;
}

unsigned __int8 calculateOverlap(string wordGuess, string wordSolution) {
	// There are 3^5=243 possibilities for the overlap:
	// 5 positions, each can be gray (nothing), yellow (wrong position) or green (correct position)
	// encoding: as a trinary number, first letter determines the 3^0 position, last letter the 3^4 position

	// INPUT CHECKS
	// Check word length==5, convert to upper-case letters, and check whether it only consists of letters
	if (wordGuess.length() != 5) { throw 1; }
	if (wordSolution.length() != 5) { throw 2; }

	for (int n = 0; n < 5; n++) {
		if (97 <= wordGuess[n] && wordGuess[n] <= 122) {
			wordGuess[n] -= 32;
		}
		if (65 > wordGuess[n] || wordGuess[n] > 90) {
			throw 1;
		}
	}
	for (int n = 0; n < 5; n++) {
		if (97 <= wordSolution[n] && wordSolution[n] <= 122) {
			wordSolution[n] -= 32;
		}
		if (65 > wordSolution[n] || wordSolution[n] > 90) {
			throw 2;
		}
	}

	// CALCULATE THE OVERLAP
	unsigned __int8 overlap = 0;
	// find letters at the correct position
	for (int n = 0; n < 5; n++) {
		if (wordGuess[n] == wordSolution[n]) {
			overlap += 2*pow(3, n);
			wordGuess.replace(n,1,"!");	// Dummy values to eliminate these letters from being used twice
			wordSolution.replace(n,1,"?");
		}
	}
	// find letters that occur at other positions
	for (int n = 0; n < 5; n++) {
		for (int m = 0; m < 5; m++) {
			if (wordGuess[n] == wordSolution[m]) {
				overlap += 1 * pow(3, n);
				wordGuess.replace(n, 1, ".");	// Dummy values to eliminate these letters from being used again
				wordSolution.replace(m, 1, ",");
			}
		}
	}

	return overlap;
}

void printOverlap(string guess, unsigned __int8 overlap) {
	// Set the cursor to the beginning of the input, in order to overwrite it with the color-coded word
	cout << "\x1b[1A";

	// Change color of the console
	HANDLE console_color;
	console_color = GetStdHandle(STD_OUTPUT_HANDLE);

	// when printing: gray -> 0, yellow -> 1, green -> 2
	for (int n = 0; n < 5; n++) {
		int color = (static_cast<int> (overlap) / pow(3, n));
		color = color % 3;
		switch (color) {
		case 0: SetConsoleTextAttribute(console_color, 0x80);	// gray background, black text for wrong letters
			break;
		case 1: SetConsoleTextAttribute(console_color, 0x60);	// yellow background, black text for correct letters in the wrong position
			break;
		case 2: SetConsoleTextAttribute(console_color, 0xA0);	// light-green background, black text for correct letters
			break;
		}
		cout << guess[n];
	}
	SetConsoleTextAttribute(console_color, 0x0F);	// Reset colors to default
}