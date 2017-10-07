#pragma once
#include <string>

// FString is mutable strings in Unreal's context
using FString = std::string;
using int32 = int;

// all variables initialized to 0
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum EWordStatus {
    OK,
    Not_Isogram
};

class FBullCowGame {
public:
    FBullCowGame(); // constructor

    // "const" keyword can only be used in member methods
    // which means you cannot change any member variable inside the method
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const; // usually this type of function doesn't change variables

    // Notes: in C++, it's ok to just provide the type of a parameter without giving a name to it
    // this feature looks quite handy
    EWordStatus CheckGuessValidity(FString) const;

    // provide a method for counting bulls and cows, and increasing try #
    FBullCowCount SubmitGuess(FString);
    void Reset(); // TODO: make a more rich return value

// please ignore this and focus of the interface above
private:
    int32 MyMaxTries;
    int32 MyCurrentTry;
    FString MyHiddenWord;
};
