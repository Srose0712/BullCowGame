//
//  FBullCowGame.cpp
//  BullCowGame
//
//  Created by Samuel Rose on 5/6/19.
//  Copyright © 2019 Samuel Rose. All rights reserved.
//
#pragma once
#include "FBullCowGame.hpp"
#include <map>
#define TMap std::map

using Fstring = std::string;
using int32 = int;

FBullCowGame::FBullCowGame()
{
    Reset();
};


int32 FBullCowGame::GetCurrentTry() const { return MyCurrentTry; }
int32 FBullCowGame::GetHiddenWordLength() const { return MyHiddenWord.length();}
bool FBullCowGame::IsGameWon() const { return bGameIsWon;}

int32 FBullCowGame::GetMaxTries() const
{
    TMap <int32, int32> WordLengthToMaxTries { {3, 2}, {4, 4}, {5, 6}, {6, 8}};
    return WordLengthToMaxTries[MyHiddenWord.length()];
}

void FBullCowGame::Reset()
{
    
    const Fstring HIDDEN_WORD = "planet";
    MyHiddenWord = HIDDEN_WORD;
    
    MyCurrentTry = 1;
    bGameIsWon = false;
    
    return;
};

EWordStatus FBullCowGame::CheckGuessValidity(Fstring Guess) const
{
    // if the guess isn't an isogram
    if(!IsIsogram(Guess))
    {
        return EWordStatus::Not_Isogram;// TODO write function
        // return an error
    }
    
    // if the guess isn't all lowercase
    else if(!IsLowercase(Guess))
    {
        return EWordStatus::Not_Lowercase;// TODO write function
        // return error
    }
    
    // if the legnth is wrong
    else if (Guess.length() != GetHiddenWordLength())
    {

        return EWordStatus::Wrong_Length;
        // return error
    }
    
    // otherwise
    else
    {
        // return ok
        return EWordStatus::OK;
    }
    
};

FBullCowCount FBullCowGame::SubmitValidGuess(Fstring Guess)
{
    //incriment the turn number
    MyCurrentTry++;
    
    // setup a return variable
    FBullCowCount BullCowCount;
    
    // loop through all letters in the guess
    int32 WordLength = MyHiddenWord.length();
    for(int32 GChar= 0; GChar < WordLength; GChar++)
    {
        // compare letters against hidden word
        for(int32 MHWChar= 0; MHWChar < WordLength; MHWChar++)
        {
            // if they match then
            if(Guess[GChar] == MyHiddenWord[MHWChar])
            {
                //if index of match matches
                if(GChar == MHWChar)
                {
                    // increment bulls if in same place
                    BullCowCount.Bulls ++;
                    
                }
                // else
                else
                {
                    // increment cows
                    BullCowCount.Cows ++;
                }
            }
        }
    }
    if(BullCowCount.Bulls == WordLength)
    {
        bGameIsWon = true;
    }
    else
    {
        bGameIsWon = false;
    }
    return BullCowCount;
}

bool FBullCowGame::IsIsogram(Fstring Word) const
{
    // consider empty or 1 letter strings as isograms
    if(Word.length() <= 1 ) {return true; }
    
    // setup map
    TMap <char, bool> LetterSeen;
    
    // loop through all the letters of the word
    for(auto Letter : Word)
    {
        // handle mix cases
        Letter = tolower(Letter);
        // if the letter is in the map
        if(LetterSeen[Letter])
        {
            // we do not have an isogram
            return false;
        }
        // otherwise
        else
        {
            // add the letter to map
            LetterSeen[Letter] = true;
        }
    }
    return true;
    
}

bool FBullCowGame::IsLowercase(Fstring Word) const
{
    for(auto Checks : Word)
    {
        // if not a lowercase letter
        if (!islower(Checks))
        {
            // return false
            return false;
        }
        //otherwise
            // return true
    }
    return true;
}
