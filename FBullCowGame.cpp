#include "FBullCowGame.h"

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
    }
    // otherwise, return OK
    else {
        return EGuessStatus::OK;
    }
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

bool FBullCowGame::IsGuessIsogram(FString Guess) const {
    for (int i = 0; i < Guess.length() - 1; ++i) {
        for (int j = i + 1; j < Guess.length(); ++j) {
            if (Guess[i] == Guess[j]) {
                return false;
            }
        }
    }
    return true;
}

bool FBullCowGame::IsGuessWrongLength(FString Guess) const {
    return Guess.length() != GetHiddenWordLength();
}

bool FBullCowGame::IsGuessAllLowerCase(FString Guess) const {
    return false;
}

