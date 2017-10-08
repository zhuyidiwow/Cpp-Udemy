/*
 * This is the console executable, that makes use of the BullCow class
 * This acts as the view in a MVC pattern, and is responsible for all user interaction.
 * For game logic, see the FBullCowGame class.
 */

#include <iostream>
#include "FBullCowGame.h"

using FText = std::string;
using int32 = int;

/* notes: these are like contracts, which appears before real function definitions
 * I think they are good because it's easy to get a glimpse of what a class does
 */
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;

int main() {
    PrintIntro();
    PlayGame();
    return 0;
}

void PlayGame() {
    do {
        BCGame.Reset();

        // TODO change from FOR to WHILE loop once we are validating inputs
        while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && !BCGame.IsGameWon()) {
            FText Guess = GetValidGuess();

            // submit the guess
            // print number of bulls and cows
            FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
            std::cout << "Bull = " << BullCowCount.Bulls << ", Cow = " << BullCowCount.Cows << ".\n";
        }

        PrintGameSummary();

    } while (AskToPlayAgain());
    // TODO: Summarize game here
}

void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

FText GetValidGuess() {
    FText Guess;
    EGuessStatus Status;

    do {
        std::cout << "\nTry " << BCGame.GetCurrentTry() << ". Enter your guess: ";
        getline(std::cin, Guess);
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status) {
            case EGuessStatus::Wong_Length:
                std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n";
                break;
            case EGuessStatus::Not_Lowercase:
                std::cout << "Please only enter all lowercase word\n";
                break;
            case EGuessStatus::Not_Isogram:
                std::cout << "Please enter a word without repeating letters.\n";
                break;
            default:
                // assuming the guess is valid
                break;
        }
    } while (Status != EGuessStatus::OK);

    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again with the same hidden word? (y / n)\n";
    FText Response;
    getline(std::cin, Response);
    return Response[0] == 'y' || Response[0] == 'Y';
}

void PrintGameSummary() {
    if (BCGame.IsGameWon()) {
        std::cout << "\nCongratulations! You Win!\n";
    } else {
        std::cout << "\nYou Lose!\n";
    }
}