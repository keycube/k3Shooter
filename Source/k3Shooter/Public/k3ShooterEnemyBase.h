// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "k3ShooterCharacter.h"
#include "Components/StaticMeshComponent.h" 
#include "Components/BoxComponent.h" 
#include "Components/MaterialBillboardComponent.h"
#include "k3ShooterEnemyBase.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterEnemyBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ak3ShooterEnemyBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	Ak3ShooterCharacter* GetPlayer();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UBoxComponent* BoxCollision;

	//Might change later because slime
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	UMaterialBillboardComponent* HealthBar;

	// Player - we move in its direction
	UPROPERTY(BlueprintReadOnly)
	Ak3ShooterCharacter* Player;

	// Current Health. Should be defined in ResetToDefaultValues
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float CurrentHealth = 10.0f;

	// Movement speed. Should be defined in ResetToDefaultValues
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MovementSpeed = 0.0f;

	// Money given on kill. Should be defined in ResetToDefaultValues
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float MoneyValue = 0.0f;

	// Damage multiplier. Should be defined in ResetToDefaultValues
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	float DamageMultiplier = 1.0f;

	// To implement this in blueprint, just override it.
	// To implement this in C++, create `void Ak3ShooterEnemyBase::ResetToDefaultValues_Implementation(){}`
	// This is where default values, such are the money gained on defeating the enemy, the health points, etc., are defined.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ResetToDefaultValues();

	// Same as above regarding implementation.
	// Custom action on death, if necessary.
	// Called when at 0 Health, before destroying the actor.
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnDeath();
};
