// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "k3ShooterShopItem.h"
#include "Kismet/GameplayStatics.h"
#include "k3ShooterShop.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterShop : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ak3ShooterShop();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	FString Typed;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	TArray<Ak3ShooterShopItem*> Items;

	void OnKeyPress(TCHAR key); // = char16_t. I dislike unreal's names just as much as MS' DWORDs ect

	bool IsWordStart(FString start, FString complete);

};
