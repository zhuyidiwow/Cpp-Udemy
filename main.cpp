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
FText GetGuess();
void PrintGuess(FText strToPrint);
bool AskToPlayAgain();
FBullCowGame BCGame;

int main() {
    PrintIntro();
    PlayGame();
    return 0;
}

void PlayGame() {
    BCGame.Reset();

    // TODO change from FOR to WHILE loop once we are validating inputs
    while (BCGame.GetCurrentTry() < BCGame.GetMaxTries()) {
        FText Guess = GetGuess();

        // submit the guess
        // print number of bulls and cows
        if (BCGame.CheckGuessValidity(Guess)) {
            FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
            std::cout << "Bull = " << BullCowCount.Bulls << ", ";
            std::cout << "Cow = " << BullCowCount.Cows << ", ";
        }
    }
    // TODO: Summarize game here
}

void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

FText GetGuess() {
    FText Guess;
    std::cout << "\nTry " << BCGame.GetCurrentTry() << ". Enter your guess: ";
    getline(std::cin, Guess);
    return Guess;
}

void PrintGuess(FText strToPrint) {
    std::cout << "You typed: " + strToPrint + "\n";
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again?\n";
    FText Response;
    getline(std::cin, Response);
    return Response[0] == 'y' || Response[0] == 'Y';
}