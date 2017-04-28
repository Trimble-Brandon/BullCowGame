#pragma once

#include "FBullCowGame.h"
#include <map>

// Syntax adjustments to Unreal standards
#define TMap std::map
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); } // Default constructor

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length(); }
bool FBullCowGame::IsGameWon() const { return bGameIsWon; }

int32 FBullCowGame::GetMaxTries() const 
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,4}, {4,7}, {5,10}, {6,16}, {7,20} };

	return WordLengthToMaxTries[MyHiddenWord.length()]; 
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "brain";

	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;

	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess)) // If guess is not an isogram
	{
		return EGuessStatus::Not_Isogram;
	}
	else if (!IsLowerCase(Guess)) // If the guess is not all lowercase
	{
		return EGuessStatus::Not_Lowercase;
	}
	else if (Guess.length() != GetHiddenWordLength()) // If the guess length is wrong
	{
		return EGuessStatus::Wrong_Length; 
	}
	else // All checks pass
	{
		return EGuessStatus::OK;
	}
}

// Receives valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;

	// Setup a return variable
	FBullCowCount BullCowCount;

	int32 WordLength = MyHiddenWord.length();

	// Loop through all letters in the hidden word
	for (int32 MHWChar = 0; MHWChar < WordLength; MHWChar++)
	{ 
		// Compare letters against the guess
		for (int32 GChar = 0; GChar < WordLength; GChar++)
		{ 
			// If they match then
			if (Guess[GChar] == MyHiddenWord[MHWChar])
			{ 
				if (MHWChar == GChar) // if they're in the same place
				{
					BullCowCount.Bulls++; // Increment bulls
				}
				else
				{
					BullCowCount.Cows++; // Increment cows

				}
			}			
		}
	}
	if (BullCowCount.Bulls == WordLength)
	{
		bGameIsWon = true;
	}
	else
	{
		bGameIsWon = false;
	}

	return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Word) const
{
	// Treat 0 and 1 letter words as isograms
	if (Word.length() <= 1)
	{
		return true;
	}

	TMap<char, bool> LetterSeen; // Setup our map
	for (auto Letter : Word)	// For all letters of the word
	{
		Letter = tolower(Letter); // Handle mixed case
		if (LetterSeen[Letter]) // if the letter is in the map
		{
			return false; // This is not an isogram
		}
		else 
		{
			LetterSeen[Letter] = true; // add the letter to the map as seen
		}
	}

	return true;
}

bool FBullCowGame::IsLowerCase(FString Word) const
{
	for (auto Letter : Word)
	{
		if (!islower(Letter)) // If not a lowercase letter
		{
			return false;
		}
	}

	return true;
}
