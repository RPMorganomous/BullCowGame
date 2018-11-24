#pragma once

#include "FBullCowGame.h"
#include <map>
#define TMap std::map

FBullCowGame::FBullCowGame() // constructor definition
{
	Reset();
}


int32 FBullCowGame::GetMaxTries() const
{
	TMap<int32, int32> WordLengthToMaxTries{ {3,5}, {4,5}, {5,5}, {6,5} };
	
	return WordLengthToMaxTries[MyHiddenWord.length()];
}

int32 FBullCowGame::GetCurrentTry() const
{
	return MyCurrentTry;
}

int32 FBullCowGame::GetHiddenWordLength() const
{
	return MyHiddenWord.length(); 
}

bool FBullCowGame::IsGameWon() const
{
	return bGameIsWon;
}

void FBullCowGame::Reset()
{
	const FString HIDDEN_WORD = "planet";
	MyHiddenWord = HIDDEN_WORD;
	MyCurrentTry = 1;
	bGameIsWon = false;
	return;
}

EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const
{
	if (!IsIsogram(Guess))
	{
		return EGuessStatus::Not_Isogram;
	} 
	else if (!IsLowercase(Guess))
	{
		return EGuessStatus::Not_Lowercase; 
	}
	else if (Guess.length() != GetHiddenWordLength())
	{
		return EGuessStatus::Wrong_Length;
	}
	else // the guess is ok
	{
		return EGuessStatus::OK;
	}
}

// receives a valid guess, increments turn and returns count
FBullCowCount FBullCowGame::SubmitValidGuess(FString Guess)
{
	MyCurrentTry++;
	FBullCowCount BullCowCount;

	// loop through all letters in the hidden word
	int32 WordLength = MyHiddenWord.length(); // assuming same length as guess
	for (int32 i = 0; i < WordLength; i++) // compare letters against the guess
	{
		for (int32 j = 0; j < WordLength; j++)
		{
			if (Guess[i] == MyHiddenWord[j]) // if they match
			{
				if (i == j)
				{
					BullCowCount.Bulls++; // increment bulls if they're in the same place
				}
				else
				{
					BullCowCount.Cows++;
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
	if (Word.length() <= 1) { return true;}

	TMap<char, bool> LetterSeen;

	for(auto Letter : Word)
	{
		Letter = tolower(Letter);
		if (LetterSeen[Letter])
		{
			return false;
		}
		else
		{
			LetterSeen[Letter] = true;
		}
	}

	return true;
}

bool FBullCowGame::IsLowercase(FString Word) const
{
	for(auto Letter : Word)
	{
		if(!islower(Letter))
		{
			return false;
		}
	}
	return true;
}
