// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Engine/DataTable.h"
#include "Word.h"
#include "k3ShooterGameInstance.generated.h"

/**
 * k3Shooter's Game Instance C++ Class.
 * Provides the function to get a random word of a certain length, though it is needed to load in the Data Tables first.
 */
UCLASS()
class K3SHOOTER_API Uk3ShooterGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	TArray<FWordList> WordLists;

	UFUNCTION(BlueprintCallable)
	void PopulateList(TArray<FWordList> ListOfFWordList);

	UFUNCTION(BlueprintCallable)
	FString GetRandomWordOfLength(int length);

};
