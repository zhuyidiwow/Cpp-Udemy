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

std::list<EGuessError> FBullCowGame::CheckGuessValidity(FString Guess) const {
    std::list <EGuessError> statusList;

    if (!IsIsogram(Guess)) {
        statusList.push_back(EGuessError::Not_Isogram);
    }
    if (!IsAllLowerCase(Guess)) {
        statusList.push_back(EGuessError::Not_Lowercase);
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

bool FBullCowGame::IsGuessWrongLength(FString Guess) const {
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