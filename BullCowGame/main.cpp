/**********************************************************
 * TITLE: UNREAL/C++ PRACTICE COURSE, BULL COW GAME
 * AUTHOR: Brandon Trimble
 * SUMMARY: Console executable that makes use of the 
 * BullCow Class. This acts as the view in a MVC pattern 
 * and is responsible for all user interaction. For game 
 * logic see the FBullCowGame Class.
 **********************************************************/
#pragma once

#include <iostream>
#include <string>
#include "FBullCowGame.h"

// Syntax adjustments to Unreal standards
using FText = std::string;
using int32 = int;

// Prototypes
void GameIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();

FBullCowGame BCGame; // Instantiate a new game.

/**********************************************************
* [MAIN]
* Controller.
**********************************************************/
int main()
{
	bool bPlayAgain = false;

	do
	{
		// Introduce the game
		GameIntro();

		// Play the game
		PlayGame();

		// Ask user if they want to play again
		bPlayAgain = AskToPlayAgain();
	} 
	while (bPlayAgain); 

	return 0;
}

/**********************************************************
* [GAME INTRO]
* Prints the introduction of the game to the screen.
**********************************************************/
void GameIntro()
{
	std::cout << "\n\nWelcome to Bulls and Cows, a fun word game.\n";
	std::cout << std::endl;
	std::cout << "******************************************************************\n"; // Fun ascii art to enrich the intro and the game as a whole.
	std::cout << "*                                                                *\n";
	std::cout << "*                       --^^--    ------                         *\n";
	std::cout << "*                      /   , ,|   |, ,  \\                        *\n";
	std::cout << "*        _____________,      @@   @@     ,___________            *\n";
	std::cout << "*       /|                  /     \\                 |\\           *\n";
	std::cout << "*      / |                 |      |                 | \\          *\n";
	std::cout << "*     &  |_________________|      |_________________|   &        *\n";
	std::cout << "*          || ||      || ||        || || VVVV || ||              *\n";
	std::cout << "*          mm mm      mm mm        mm mm      mm mm              *\n";
	std::cout << "*                                                                *\n";
	std::cout << "*                                                                *\n";
	std::cout << "*  ****          *  *          \\   ****                          *\n";
	std::cout << "*  *   *         *  *          \\   *                             *\n";
	std::cout << "*  ****   *   *  *  *    ***   \\   *     ****  *     *    ****   *\n";
	std::cout << "*  *   *  *   *  *  *    *     \\   *     *  *  *  *  *    *      *\n";
	std::cout << "*  ****   *****  *  *  ***     \\   ****  ****  *** ***  ***      *\n";
	std::cout << "*                                                                *\n";
	std::cout << "******************************************************************\n";
	std::cout << "Bulls and Cows is a game where you guess the word that the program\n"; // Some explanation of how the game works.
	std::cout << "is thinking of. The word will always be an isogram, a word with no\n"; // May replace this with a Game menu that includes an option for 'about'.
	std::cout << "more than one of each letter in it.\n"; 
	std::cout << "\nYou are provided with the length of the word in numbers. Your\n";
	std::cout << "current try is displayed along with the amount of tries that you\n";
	std::cout << "have to guess correctly. The amount of tries changes depending on\n";
	std::cout << "the length of the word.\n";
	std::cout << "\nEach time you enter a guess the game will show you a number of\n";
	std::cout << "Bulls and number of Cows. A 'Bull' is the correct letter in the\n";
	std::cout << "correct position of the word. A 'Cow' is the correct letter, but is\n";
	std::cout << "in the wrong position in the word. Have fun!!\n";
	std::cout << "\n-----------------------------------------------------------------";
	std::cout << std::endl;
	std::cout << "Can you guess the " << BCGame.GetHiddenWordLength();
	std::cout << " letter isogram I'm thinking of?\n";
	std::cout << std::endl;

	return;
}

/**********************************************************
* [PLAY GAME]
* Play the game. Loops through GetGuess and ConfirmGuess.
**********************************************************/
void PlayGame()
{
	BCGame.Reset();
	int32 MaxTries = BCGame.GetMaxTries();

	// Loop asking for guesses while the game
	// is NOT won and there are still tries remaining
	while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
	{
		FText Guess = GetValidGuess(); // TODO make loop for validation

		// Submit valid guess to the game
		FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);

		// Print number of bulls and cows
		std::cout << "Bulls = " << BullCowCount.Bulls;
		std::cout << ". Cows = " << BullCowCount.Cows << "\n\n";
	}

	// Summarize game
	PrintGameSummary();

	return;
}

/**********************************************************
* [GET VALID GUESS]
* Prompt user for guess. Loop until the guess is valid.
**********************************************************/
FText GetValidGuess()
{
	FText Guess = "";
	EGuessStatus Status = EGuessStatus::Invalid_Status;

	do
	{
		int32 CurrentTry = BCGame.GetCurrentTry();

		std::cout << "Try " << CurrentTry << " of " << BCGame.GetMaxTries();
		std::cout << ". Enter Guess: ";
		std::getline(std::cin, Guess);

		Status = BCGame.CheckGuessValidity(Guess);
		switch (Status)
		{
		case EGuessStatus::Not_Isogram:
			std::cout << "Please enter a word without repeating letters!\n\n";
			break;
		case EGuessStatus::Not_Lowercase:
			std::cout << "Please enter all lowercase letters!\n\n";
			break;
		case EGuessStatus::Wrong_Length:
			std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word!\n\n";
			break;
		default:
			// assume the guess is valid
			break;
		}
	} while (Status != EGuessStatus::OK); // Keep looping until there are no errors

	return Guess;
}

/**********************************************************
* [ASK TO PLAY AGAIN]
* Prompt user and ask if they want to play again.
**********************************************************/
bool AskToPlayAgain()
{
	std::cout << "Do you want to play again?(y/n): ";
	FText Response = "";
	std::getline(std::cin, Response);

	return (Response[0] == 'y' || Response[0] == 'Y');
}


/**********************************************************
* [PRINT GAME SUMMARY]
* Determine if the player won or lost and then print the 
* message appropriate.
**********************************************************/
void PrintGameSummary()
{
	if (BCGame.IsGameWon())
	{
		std::cout << "CONGRATULATIONS! --- YOU WON!\n";
	}
	else
	{
		std::cout << "Better luck next time!\n";
	}
}
