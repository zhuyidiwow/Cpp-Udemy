#pragma once
#include <string>
#include <list>

// makes syntax Unreal friendly
// FString is mutable strings in Unreal's context
using FString = std::string;
using int32 = int;

// all variables initialized to 0
struct FBullCowCount {
    int32 Bulls = 0;
    int32 Cows = 0;
};

// "enum class" is what called strong typed enum
enum class EGuessError {
    Not_Isogram,
    Wong_Length,
    Not_Lowercase
};

class FBullCowGame {
public:
    // constructor
    FBullCowGame();

    // "const" keyword can only be used in member methods
    // which means you cannot change any *member variable* inside the method
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    // usually this type of function (returning bool) doesn't change variables
    bool IsGameWon() const;

    // Notes: in C++, it's ok to just provide the type of a parameter without giving a name to it
    // this feature looks quite handy
    std::list<EGuessError> CheckGuessValidity(FString) const;

    // provide a method for counting bulls and cows, and increasing try #
    FBullCowCount SubmitGuess(FString);
    void Reset();

// please ignore this and focus of the interface above
private:
    int32 MyCurrentTry;
    FString MyHiddenWord;
    bool bIsGameWon;

    bool IsIsogram(FString) const;
    bool IsInCorrectLength(FString) const;
    bool IsAllLowerCase(FString) const;
};
