//
//  FBullCowGame.hpp
//  BullCowGame
//
//  Created by Samuel Rose on 5/6/19.
//  Copyright © 2019 Samuel Rose. All rights reserved.
//
#pragma once
#ifndef FBullCowGame_hpp
#define FBullCowGame_hpp

#include <stdio.h>
#include <string>

using Fstring = std::string;
using int32 = int;


struct FBullCowCount
{
    int32 Bulls = 0;
    int32 Cows = 0;
};

enum class EWordStatus
{
    Invalid_Status,
    OK,
    Not_Isogram,
    Wrong_Length,
    Not_Lowercase
    
};

class FBullCowGame
{
public:
    
    // Constructer
    FBullCowGame();
    
    int32 GetMaxTries() const;
    int32 GetCurrentTry() const;
    int32 GetHiddenWordLength() const;
    bool IsGameWon() const;
    
    
    EWordStatus CheckGuessValidity(Fstring) const;
    
    void Reset();
    
    // Provide a method for counting bulls and cows and increasing try #
    
    FBullCowCount SubmitValidGuess(Fstring);
    
private:
    
    // See constructor for initialization
    bool IsIsogram(Fstring) const;
    bool IsLowercase(Fstring) const;
    
    int32 MyMaxTries;
    int32 MyCurrentTry;
    Fstring MyHiddenWord;
    bool bGameIsWon;
    
};
#endif /* FBullCowGame_hpp */
