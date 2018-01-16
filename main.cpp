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

// function prototypes as outside a class
void PrintIntro();
void PlayGame();
FText GetValidGuess();
bool AskToPlayAgain();
void PrintGameSummary();
FBullCowGame BCGame;

int main() {
    PlayGame();
    return 0;
}

void PrintIntro() {
    std::cout << "Welcome to Bulls and Cows, a fun word game.\n";
    std::cout << "Can you guess the " << BCGame.GetHiddenWordLength() << " letter isogram I'm thinking of?\n";
}

void PlayGame() {
    do {
        BCGame.Reset();
        PrintIntro();

        while (BCGame.GetCurrentTry() <= BCGame.GetMaxTries() && !BCGame.IsGameWon()) {
            FText Guess = GetValidGuess();

            // submit the guess
            // print number of bulls and cows
            FBullCowCount BullCowCount = BCGame.SubmitGuess(Guess);
            std::cout << "Bull = " << BullCowCount.Bulls << ", Cow = " << BullCowCount.Cows << ".\n";
        }

        PrintGameSummary();

    } while (AskToPlayAgain());
}

FText GetValidGuess() {
    FText Guess;
    std::list<EGuessError> GuessErrorList;

    do {
        std::cout << "\nTry " << BCGame.GetCurrentTry() << "/" << BCGame.GetMaxTries() << ". Enter your guess: ";
        getline(std::cin, Guess);
        GuessErrorList = BCGame.CheckGuessValidity(Guess);
        std::string strToReturn;
        if (!GuessErrorList.empty()) {
            for (auto status : GuessErrorList) {
                switch (status) {
                    case EGuessError::Wong_Length:
                        strToReturn += "Please enter a ";
                        strToReturn += std::to_string(BCGame.GetHiddenWordLength());
                        strToReturn += " letter word.\n";
                        break;
                    case EGuessError::Not_Lowercase:
                        strToReturn += "Please only enter all lowercase word.\n";
                        break;
                    case EGuessError::Not_Isogram:
                        strToReturn += "Please enter a word without repeating letters.\n";
                        break;
                    default:
                        strToReturn += "Everything is good.\n";
                        break;
                }
            }

            std::cout << "You got " << GuessErrorList.size() << " errors.\n" << strToReturn;
        }
    } while (!GuessErrorList.empty());

    return Guess;
}

bool AskToPlayAgain() {
    std::cout << "Do you want to play again? (y / n)\n";
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