// Fill out your copyright notice in the Description page of Project Settings.

#include "Math/UnrealMathUtility.h"
#include "k3ShooterGameInstance.h"

void Uk3ShooterGameInstance::PopulateList(TArray<FWordList> ListOfFWordList){
    WordLists = ListOfFWordList;
}

FString Uk3ShooterGameInstance::GetRandomWordOfLength(int length){
    for (auto& List : WordLists){
        if (List.WordLength == length){
            TArray<FWord*> words;
            List.WordList->GetAllRows(TEXT(""), words);
            return words[FMath::RandRange(0, words.Num()-1)]->Word;
        }
    }

    return TEXT("ERROR01");
}