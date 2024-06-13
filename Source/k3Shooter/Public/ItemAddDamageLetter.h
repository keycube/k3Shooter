// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "k3ShooterShopItem.h"
#include "ItemAddDamageLetter.generated.h"

UCLASS()
class K3SHOOTER_API AItemAddDamageLetter : public Ak3ShooterShopItem
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AItemAddDamageLetter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Buy();
};