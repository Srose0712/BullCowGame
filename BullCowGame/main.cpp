/*
  main.cpp
  BullCowGame

  Created by Samuel Rose on 4/21/19.
  Copyright © 2019 Samuel Rose. All rights reserved.

  This is the console executable, that makes use of the BullCow Class
  This acts as the view in the MVC pattern, and is responsible for all
  user interaction. For game logic see the FBullCowGame class.

*/
#pragma once
// Call to standard library
#include <iostream>
#include <string>
#include "FBullCowGame.hpp"

// Call to namespace
using Ftext = std::string;
using int32 = int;

// Declaration of functions
void PrintIntro();
Ftext GetValidGuess();
void PlayGame();
bool AskToPlayAgain();
void PrintGameSummary();

// Instantiate a new game
FBullCowGame BCGame;

// Main function of game
int main() {
   do
   {
       PrintIntro();
       PlayGame();
       
   }
    while(AskToPlayAgain() == true);
    return 0;
}

// Function introduction the game and word legnth
void PrintIntro()
{
    
    // Introduction to game
    std :: cout << "Welcome to Bulls and Cows, a fun word game." << std :: endl;
    std :: cout << "Can you guess the "<< BCGame.GetHiddenWordLength() <<" letter isogram I'm Thinking of?\n" << std :: endl;
    return;
}

// Player plays the game
void PlayGame()
{
    // Start and reset state of game.
    BCGame.Reset();
    
    // Instantiate a new game
    int32 MaxTries = BCGame.GetMaxTries();
    int32 RemainingTries = MaxTries - BCGame.GetCurrentTry();
    // loop asking for guesses while the game is NOT won
    // and there are still tries remaining
    while(!BCGame.IsGameWon() && BCGame.GetCurrentTry() <= MaxTries)
    {
        Ftext Guess = GetValidGuess();
        
        FBullCowCount BullCowCount = BCGame.SubmitValidGuess(Guess);
        
        std::cout << "Bulls = " << BullCowCount.Bulls;
        std::cout << " Cows = " << BullCowCount.Cows;
        std::cout << " Tries Remaining = \n" << RemainingTries << std::endl;
        
    }
    
    // TODO: Summarize the game
    PrintGameSummary();
    return;
}


// Function prompting and taking player input
Ftext GetValidGuess()
{
    Ftext Guess = "";
    
    EWordStatus Status = EWordStatus::Invalid_Status;
    do
    {
        // Get a guess from the player
        int32 CurrentTry = BCGame.GetCurrentTry();
        std :: cout << "Try " << CurrentTry << "."<< " Guess the word: ";
        

        getline(std :: cin,Guess);
        
        
        Status = BCGame.CheckGuessValidity(Guess);
        switch (Status)
        {
        case EWordStatus::Wrong_Length:
            std::cout << "Please enter a " << BCGame.GetHiddenWordLength() << " letter word.\n" << std::endl;
            break;
                
        case EWordStatus::Not_Isogram:
            std::cout << "Your guess " << Guess << " repeats letters.\n" << std::endl;
            break;
                
        case EWordStatus::Not_Lowercase:
            std::cout << "Your guess " << Guess << " is not the same case as the isogram.\n" << std::endl;
            break;
             
        // assuming the guess is valid
        default:
            break;
            
        }
        
    }while(Status != EWordStatus::OK);
    
    return Guess;
}

void PrintGameSummary()
{
    if(BCGame.IsGameWon() == true)
    {
        std::cout << "You Won the Game! " << std::endl;
    }
    else
    {
        std::cout << "Better Luck next time! " << std::endl;
    }
}

bool AskToPlayAgain()
{
    std :: cout << "Would you like to play again? (y/n) ";
    
    Ftext Response = "";
    getline(std :: cin, Response);

    return (Response[0] == 'y' || Response[0] == 'Y');

}

