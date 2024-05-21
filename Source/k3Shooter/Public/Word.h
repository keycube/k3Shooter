// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "Containers/UnrealString.h"
#include "CoreMinimal.h"
#include "Word.generated.h"

USTRUCT(BlueprintType)
/**
 * Structure for a word.
 */
struct FWord : public FTableRowBase {
	GENERATED_BODY()
public:

	FWord() : Word("") {}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Word")
	FString Word;	
};


USTRUCT(BlueprintType)
/**
 * Structure for a list of words. It does not have a list directly, but a data table with multiple `FWord`s.
 */
struct FWordList {
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WordList")
	UDataTable* WordList;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="WordList")
	int WordLength;
};