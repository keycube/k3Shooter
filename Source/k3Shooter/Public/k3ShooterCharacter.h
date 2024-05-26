// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "k3Shooter/k3ShooterGameInstance.h"
#include "InputCoreTypes.h"
#include "k3ShooterCharacter.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	Ak3ShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called When any key is pressed, responsible for handling A-Z key events to get the 
	void OnAnyKeyPress(FKey key);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void GetNewTargetWord();

	float CompareAndGetScore();

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString TargetWord = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Typed = "";

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int CurrentWordLength = 3;

	UFUNCTION(BlueprintCallable)
	FString GetCurrentWordProgress();
};
