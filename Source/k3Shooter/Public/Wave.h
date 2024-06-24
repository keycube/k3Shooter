// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Engine/DataTable.h"
#include "k3ShooterEnemyBase.h"
#include "CoreMinimal.h"
#include "Wave.generated.h"

USTRUCT(BlueprintType)
/**
 * Structure for an enemy wave, ready for use in a data table
 */
struct FWave : public FTableRowBase {
	GENERATED_BODY()
public:
	FWave() {}
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	TArray<TSubclassOf<Ak3ShooterEnemyBase>> Enemies;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float MinimumTimeToSpawn = 1.5f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Wave")
	float MaximumTimeToSpawn = 5.0f;
};

USTRUCT(BlueprintType)
/**
 * Structure for an enemy, used for procgen
 */
struct FEnemy {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	TSubclassOf<Ak3ShooterEnemyBase> Enemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Enemy")
	float Points = 1.0f;
};



