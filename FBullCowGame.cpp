#pragma once
#include "FBullCowGame.h"
#include <map>

// make syntax UE-friendly
#define TMap std::map
using int32 = int;

// default constructor
FBullCowGame::FBullCowGame()
{
	Reset();
}

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameWon; }

int32 FBullCowGame::GetMaxTries() const { 
	TMap<int32, int32> WordLengthToMaxTries{ {3, 4}, {4, 7}, {5, 10}, {6, 16}, {7, 20} };
	return WordLengthToMaxTries[GetHiddenWordLength()];
}

// sets all game vars
void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyCurrentTry = 1;
	MyHiddenWord = HIDDEN_WORD;
	bGameWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) { // check for non-isogram
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowercase(Guess)) { // check for uppercase
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) { // check for wrong length
		return EGuessStatus::Wrong_Length;
	}
	// otherwise OK
	return EGuessStatus::OK;
}

FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;
	int32 WordLength = MyHiddenWord.length();

	// loop through all letters in the guess
	for (int32 i = 0; i < WordLength; i++) {
		if (Guess[i] == MyHiddenWord[i]) { // exact matches are bulls
			BullCowCount.Bulls++;
		}
		else {
			for (int32 j = 0; j < WordLength; j++) { // if no exact match but the letter exists in the word, count it as a cow
				if (Guess[i] == MyHiddenWord[j]) {
					BullCowCount.Cows++;
				}
			}
		}
	}

	if (BullCowCount.Bulls == WordLength) {
		bGameWon = true;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const
{
	// treat empty or single char as isogram
	if (Guess.length() < 2) { return true; }

	// create TMap dictionary to use for comparison
	TMap<char, bool> LetterSeen;
		// initialize values?

	for (auto Letter : Guess) // loop through letters in guess
	{
		Letter = tolower(Letter); // translate to lowercase
		if (LetterSeen[Letter]) { // check for existing position in map
			return false; // if found, return false
		}
		LetterSeen[Letter] = true; // if not, add it to the map
	}

	// return true, if we've gotten through all the letters with no matches it is indeed an isogram
	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for (auto Letter : Word) {
		// if not a lowercase letter, return false
		if (!islower(Letter)) {
			return false;
		}
	}
	return true;
}
