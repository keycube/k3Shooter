// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "k3ShooterShopItem.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterShopItem : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ak3ShooterShopItem();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void Buy(); //Actually buy the object. Private because it does no check, please use TryBuy if calling from outside this class.
						//To Implement by inherited classes

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int Price; // Note : Despite the fact that the player can have cents, the price here can't and is always flat. This is by design - cents are not useful.

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Word; // The word that has to be typed

	UFUNCTION()
	void TryBuy(); //Attempt to buy the object.
};
