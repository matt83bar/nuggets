/* This is the console executable that makes use of the BullCow class
This acts as the view in a MVC pattern, and is responsible for all
user interaction.  For game logic see the FBullCowGame class.
*/

#pragma once
#include <iostream>
#include <string>
#include "FBullCowGame.h"

// to make syntax UE-friendly
using FText = std::string;
using int32 = int;

// function prototypes
void PrintInfo();
FText GetValidGuess();
void PlayGame();
void PrintGameSummary();
bool AskToPlayAgain();
FBullCowGame BCGame;

int main()
{
	PrintInfo();
	do {
		PlayGame();
		PrintGameSummary();
	} while (AskToPlayAgain());
	return 0;
}

void PrintInfo()
{
	std::cout << "Welcome to Bulls and Cows" << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
	return;
}

// gets guesses until game is over
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTry = BCGame.GetMaxTries();
	while (!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTry) {
		FText Guess = GetValidGuess();
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
		std::cout << "Bulls: " << BullCowCount.Bulls;
		std::cout << " Cows: " << BullCowCount.Cows << "\n\n";
	}
}

void PrintGameSummary()
{
	if (BCGame.IsGameWon()) {
		std::cout << "Congratulations! You figured out the word!";
	}
	else {
		std::cout << "Oh Noes! You failed in this simple challenge! You really suck!";
	}
	std::cout << std::endl;
}

bool AskToPlayAgain()
{
	std::cout << "Do you want to play again with the same word (y/n)? ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');

}

// gets guess and makes sure it's valid
FText GetValidGuess()
{
	int32 CurrentTry = BCGame.GetCurrentTry();
	int32 MaxTry = BCGame.GetMaxTries();
	
	FText Guess = "";
	bool IsValid = false;
	do {
		std::cout << "Try " << CurrentTry << " of " << MaxTry << ". Enter your guess: ";
		std::getline(std::cin, Guess);

		EGuessStatus ErrorCheck = BCGame.CheckGuessValidity(Guess);
		switch (ErrorCheck) {
		case EGuessStatus::Not_Isogram:
			std::cout << "Your guess is not an isogram!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Your guess should not include uppercase letters!\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Your guess is not " << BCGame.GetHiddenWordLength() << " letters!\n\n";
			break;
		case EGuessStatus::OK:
			IsValid = true;
		}
	} while (!IsValid);

	return Guess;
}
