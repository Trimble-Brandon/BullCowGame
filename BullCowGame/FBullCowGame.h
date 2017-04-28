/**********************************************************
* Header file. Contains the game logic.
**********************************************************/

#pragma once
#include <string>

// Syntax adjustments to Unreal standards
using FString = std::string;
using int32 = int;

/**********************************************************
* [FBULLCOWCOUNT]
* Structure that stores variables for Bulls and Cows
**********************************************************/
struct FBullCowCount
{
	int32 Bulls = 0;
	int32 Cows = 0;
};

/**********************************************************
* [EGUESSSTATUS]
* Enum that provides status codes for the Guess the user
* Inputs. Used for error checking.
**********************************************************/
enum class EGuessStatus
{
	Invalid_Status,
	OK,
	Not_Isogram,
	Wrong_Length,
	Not_Lowercase
};

/**********************************************************
* [FBULLCOWGAME]
* Game state class. 
**********************************************************/
class FBullCowGame
{
public:
	FBullCowGame(); // Constructor

	int32 GetMaxTries() const;
	int32 GetCurrentTry() const;
	int32 GetHiddenWordLength() const;
	bool IsGameWon() const;
	EGuessStatus CheckGuessValidity(FString) const;

	void Reset(); // TODO make a more rich return value.
	// Counts bulls and cows, and increases try #
	FBullCowCount SubmitValidGuess(FString Guess);

private:
	// See Constructor for initialization
	int32 MyCurrentTry;
	FString MyHiddenWord;
	bool bGameIsWon;

	bool IsIsogram(FString) const;
	bool IsLowerCase(FString) const;
};