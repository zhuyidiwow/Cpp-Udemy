#include "FBullCowGame.h"
#include <map>
#include <list>

#define TMap std::map // no semicolon in the end

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return static_cast<int32>(MyHiddenWord.length()); }
bool FBullCowGame::IsGameWon() const { return bIsGameWon; }

void FBullCowGame::Reset() {
    // constants are usually named with all capital
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "ant";

    MyCurrentTry = 1;
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
    bIsGameWon = false;
}

std::list<EGuessStatus> FBullCowGame::CheckGuessValidity(FString Guess) const {
    std::list <EGuessStatus> statusList;

    if (!IsIsogram(Guess)) {
        statusList.push_back(EGuessStatus::Not_Isogram);
    }
    if (!IsAllLowerCase(Guess)) {
        statusList.push_back(EGuessStatus::Not_Lowercase);
    }
    if (IsInCorrectLength(Guess)) {
        statusList.push_back(EGuessStatus::Wong_Length);
    } else {
        statusList.push_back(EGuessStatus::OK);
    }

    return statusList;
}

// receive a valid guess, increment turn, and returns count
FBullCowCount FBullCowGame::SubmitGuess(FString Guess) {
    MyCurrentTry++;
    // setup a return variable
    FBullCowCount BullCowCount = FBullCowCount();
    // loop through all letters in the guess
    for (int32 i = 0; i < Guess.length(); i++) {
        // compare the current letter against all letters in the hidden word
        for (int32 j = 0; j < MyHiddenWord.length(); j++) {
            // if they match then
            if (Guess[i] == MyHiddenWord[j]) {
                // if they're in the same place
                if (i == j) {
                    BullCowCount.Bulls++;
                // else
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

bool FBullCowGame::IsInCorrectLength(FString Guess) const {
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