// HinterlistigesWoerdl.cpp : Diese Datei enthält die Funktion "main". Hier beginnt und endet die Ausführung des Programms.
//

#include <fstream>
#include <string>
#include <vector>

#include "helperFunctions.h"
#include "minimax.h"

#include <iostream>
using namespace std;

// Global variables and constants
extern vector<string> listOfWords;
static const int MAX_GUESSES = 20;

int main()
{
    cout << "HALLO WELT! ICH BIN DAS HINTERLISTIGE WOERDL ]:->\n\n";

	/* STORING ALL WORDS --> if a different list of words shall be used
	fstream inputFile("alleWoerdlWoerter.txt", ios::in);
	string word;

	if (inputFile.is_open()) {
		while (getline(inputFile, word)) {
			listOfWords.push_back(word);
		}
	}
	else {
		cout << "ERROR: file can't be read.\n";
	}

	inputFile.close();
	*/

	// COPY OF THE WORD LIST THAT IS REDUCED STEP BY STEP
	vector<string> remainingWords = listOfWords;

	cout << "Ich habe " << listOfWords.size() << " Woerter mit je 5 Buchstaben geladen.\n";
	cout << "Das sind alle Woerter, die mein fairer Bruder auch akzeptiert. Umlaute werden als zwei Buchstaben aufgeloest.\n";
	cout << "Viel Spass beim Raetseln!\n";
	cout << "\nBitte rate deutsche Woerter mit fuenf Buchstaben:\n";

	// INITIALIZING THE PARAMETERS
	int guessNumber = 0;
	unsigned __int8 mostCommonOverlap = 0;

	//STARTING THE LOOP FOR THE GUESSES
	while (mostCommonOverlap < 242 && guessNumber < MAX_GUESSES) {
		// INPUT OF THE GUESS
		string guess;
		
		// NORMALES RATEN
		cin >> guess;

		// MINIMAX SOLVER
		/* guess = minimax(remainingWords);
		cout << "\n"; */

		// VALIDATE INPUT AND CONVERT TO UPPER-CASE LETTERS
		try {
			guess = checkInput(guess);
		}
		catch (int errorCode) {	// Skip execution for bad guesses
			cout << "\x1b[1A";
			switch (errorCode) {
			case 1:
				cout << guess << "  Die Eingabe enthaelt andere Zeichen als Buchstaben.\n";
				continue;
			case 2:
				cout << guess << "  Die Eingabe hat nicht genau 5 Buchstaben.\n";
				continue;
			case 3:
				cout << guess << "  Dieses Wort ist nicht in der Liste.\n";
				continue;
			default:
				cout << "ERROR: unexpected error occured when calling the input check function with (" << guess << ").\n";
				continue;
			}
		}

		guessNumber++;	// Only increase guess number for legal guesses

		// OVERLAP WITH ALL WORDS IN THE LIST
		vector<vector<string>> overlapList(243);	// There are 243 possible values for the overlap, sort the words by overlap
		try {
			overlapList = calculateOverlapList(guess, remainingWords);
		}
		catch (int errorCode) {
			switch (errorCode) {
			case 1:
				cout << "ERROR: " << guess << " is not a 5-letter word.\n";
				break;
			case 2:
				cout << "ERROR: one element in the list of words is not a 5-letter word.\n";
				break;
			default:
				cout << "ERROR: unexpected error occured when calculating the overlaps with (" << guess << ").\n";
			}
		}

		//FIND MOST COMMON OVERLAP
		mostCommonOverlap = 0;
		for (int n = 1; n < 243; n++) {
			if (overlapList[n].size() > overlapList[mostCommonOverlap].size()) {
				mostCommonOverlap = n;
			}
		}
		remainingWords = overlapList[mostCommonOverlap];

		// OUTPUT OF THE OVERLAP
		printOverlap(guess, mostCommonOverlap);
		cout << "  (" << guessNumber << ")";
		if (mostCommonOverlap == 242) {
			cout << "\nGlueckwunsch! Du hast das Raetsel in " << guessNumber << " Versuchen geloest!\n";
		}
		else {
			if (guessNumber < MAX_GUESSES) {
				cout << " Es gibt noch " << remainingWords.size() << " Moeglichkeiten.\n";
				// cout << "\n";
			}
			else {
				cout << "\nSchade! Du hast die maximale Anzahl an Versuchen erreicht.\n";
			}
		}
	}
	system("PAUSE");
}

// Programm ausführen: STRG+F5 oder Menüeintrag "Debuggen" > "Starten ohne Debuggen starten"
// Programm debuggen: F5 oder "Debuggen" > Menü "Debuggen starten"