#include "FBullCowGame.h"

using FString = std::string;
using int32 = int;

FBullCowGame::FBullCowGame() { Reset(); }

int32 FBullCowGame::GetMaxTries() const { return MyMaxTries; }
int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return static_cast<int32>(MyHiddenWord.length()); }

void FBullCowGame::Reset() {
    // constants are usually named with all capital
    constexpr int32 MAX_TRIES = 8;
    const FString HIDDEN_WORD = "ant";

    MyCurrentTry = 1;
    MyMaxTries = MAX_TRIES;
    MyHiddenWord = HIDDEN_WORD;
}

bool FBullCowGame::IsGameWon() const {
    return false;
}

EWordStatus FBullCowGame::CheckGuessValidity(FString Guess) const {
    return EWordStatus::OK;
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
    return BullCowCount;
}

