#pragma once
#include "FBullCowGame.h"
#include <map>
#include <list>
#include <ctime>

#define TMap std::map // no semicolon in the end

// to make syntax Unreal friendly
using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return static_cast<int32>(MyHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }
int32 FBullCowGame::GetMaxTries() const {
    TMap<int32, int32> WordLengthToMaxTries { {3, 3}, {4, 4}, {5, 5}, {6, 6} };
    return WordLengthToMaxTries[GetHiddenWordLength()];
}

void FBullCowGame::Reset() {
    // constants are usually named with all capital
    const std::array<FString, 3> HIDDEN_WORDS = {"ant", "halo", "earth"};

    MyCurrentTry = 1;
    std::srand(static_cast<unsigned int>(std::time(0)));
    int32 index = std::rand() % 3;
    MyHiddenWord = HIDDEN_WORDS[index];
    bIsGameWon = false;
}

<<<<<<< HEAD
std::list<EGuessError> FBullCowGame::CheckGuessValidity(FString Guess) const {
    std::list <EGuessError> statusList;

    if (!IsIsogram(Guess)) {
        statusList.push_back(EGuessError::Not_Isogram);
    }
    if (!IsAllLowerCase(Guess)) {
        statusList.push_back(EGuessError::Not_Lowercase);
=======
EGuessStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    // if the guest isn't isogram, return an error
    if (!IsGuessIsogram(Guess)) {
        return EGuessStatus::Not_Isogram;
    }
    // if the guess isn't all lowercase, return an error
    //TODO: find a way to detect lower case input
    else if (false) {
        return EGuessStatus::Not_Lowercase;
    }
    // if the guess length is wrong, return an error
    else if (IsGuessWrongLength(Guess)) {
        return EGuessStatus::Wong_Length;
>>>>>>> 03026110997fc753a371cfc8d5ab951d5589afa9
    }
    if (IsInCorrectLength(Guess)) {
        statusList.push_back(EGuessError::Wong_Length);
    }

    return statusList;
}

FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    MyCurrentTry++;

    FBullCowCount BullCowCount = FBullCowCount();

    for (int32 i = 0; i < Guess.length(); i++) {
        for (int32 j = 0; j < MyHiddenWord.length(); j++) {
            if (Guess[i] == MyHiddenWord[j]) {
                if (i == j) {
                    BullCowCount.Bulls++;
                } else {
                    BullCowCount.Cows++;
                }
            }
        }
    }

    bIsGameWon = BullCowCount.Bulls == GetHiddenWordLength();

    return BullCowCount;
}

bool FBullCowGame::IsIsogram(FString Guess) const {
    if (Guess.length() <= 1) {
        return true;
    }

    TMap <char, bool> LetterSeen;

    // this is O(n)!
    for (char Letter : Guess) {
        Letter = static_cast<char>(tolower(Letter));

        if (LetterSeen[Letter]) {
            return false;
        } else {
            LetterSeen[Letter] = true;
        }
    }

    return true;
}

<<<<<<< HEAD
bool FBullCowGame::IsInCorrectLength(FString Guess) const {
=======
bool FBullCowGame::IsGuessWrongLength(FString Guess) const {
>>>>>>> 03026110997fc753a371cfc8d5ab951d5589afa9
    return Guess.length() != GetHiddenWordLength();
}

bool FBullCowGame::IsAllLowerCase(FString Guess) const {
    for (auto Letter : Guess) {
        if (!islower(Letter)) {
            return false;
        }
    }
    return true;
}