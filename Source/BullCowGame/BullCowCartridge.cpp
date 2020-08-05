// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"
#include "HiddenWordList.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();

    SetupGame();
    // If using a .txt file
    // const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
     //FFileHelper::LoadFileToStringArray(WordList, *WordListPath);
    
    PrintLine(TEXT("The number of possible words is %i"), Words.Num());
    PrintLine(TEXT("The hidden word is: %s\nIt is %i letters long."), *HiddenWord, HiddenWord.Len()); // Debug Line


    TArray<FString> ValidWords;

    for (int32 i = 0; i < 10; i++)
    {
        if (Words[i].Len() >= 4 && Words[i].Len() <= 8)
        {
            ValidWords.Emplace(Words[i]);
            //PrintLine(TEXT("%s"), *Words[i]);
        }
        
    }

    for (int32 i=0; i < ValidWords.Num(); i++)
    {
        PrintLine(TEXT("%s."), *ValidWords[i]);
    }
    
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    if (bGameOver)
    {
        ClearScreen();
        SetupGame();
    }
    else     // Checking PlayerGuess
    {
        ProcessGuess(Input);
    }
}

void UBullCowCartridge::SetupGame()
{
    HiddenWord = TEXT("farts");
    Lives = HiddenWord.Len();
    bGameOver = false;

    // Intro text
    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Guess the %i letter word! You have %i lives."), Lives, Lives);
    PrintLine(TEXT("Type in your guess and\nPress Enter to continue..."));  // Prompt player for guess

    // If using a .txt file
    // const TCHAR HW[] = TEXT("plums");
    // PrintLine(TEXT("The first letter is %c"), HiddenWord[0]);
    // PrintLine(TEXT("The 4th letter in HW is %c"), HW[3]);

}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    
    PrintLine(TEXT("\nPress Enter to play again!"));
}

void UBullCowCartridge::ProcessGuess(FString Guess)
{
    if (Guess == HiddenWord)
    {
        PrintLine(TEXT("Hell ya brother! YoU wIN!"));
        EndGame();
        return;
    }
    
    // Check if correct number of characters and Prompt to GuessAgain
    if(Guess.Len() != HiddenWord.Len())
    {
        PrintLine(TEXT("Try again!\nYou have %i lives remaining."), Lives);
        PrintLine(TEXT("The hidden word is %i letters."), HiddenWord.Len());
        return;
    }

    // Check if isogram and Prompt to GuessAgain
    if(!IsIsogram(Guess))
    {
        PrintLine(TEXT("No repeating letters, guess again."));
        return;
    }

    // Remove a life
    PrintLine(TEXT("You lost a life.")); 
    --Lives;

    // Check if lives > 0
    if(Lives <= 0)
    {
        ClearScreen();
        PrintLine(TEXT("You have no lives left. GAME OVER."));
        PrintLine(TEXT("The hidden word was: %s"), *HiddenWord);
        EndGame();   
        return;
    }

    PrintLine(TEXT("You have %i lives remaining."), Lives);
}

bool UBullCowCartridge::IsIsogram(FString Word) const
{
   
    // Check if each letter appears only once
    // Start at element [0]
    // Compare against the next letter
    // Until we reach [Word.Len() -1]
    for ( int32 Index = 0; Index < Word.Len(); Index++)
    {
        for ( int32 Comparison = Index + 1; Comparison < Word.Len() - 1; Comparison++)
        {
            if (Word[Index] == Word[Comparison])
            {
                return false; // Return false if any are repeated
            }
        }
    }
    return true;
}