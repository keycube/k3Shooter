// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "Components/BoxComponent.h"
#include "GameFramework/Actor.h"
#include "Wave.h"
#include "k3ShooterEnemyBase.h"
#include "k3ShooterEnemySpawner.generated.h"

UCLASS()
class K3SHOOTER_API Ak3ShooterEnemySpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	Ak3ShooterEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Waves data table. Data table of FWave, which contains the actors to spawn at each wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* Waves;

	//Spawn zone. Size set in blueprint but all calculations can be done in C++
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UBoxComponent* SpawnZone;

	//Break time = Time between waves. Sets itself at 30s probably, but there will be an option to skip to next wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float BreakTime = 0.0f;

	//True if between waves, false if in a wave.
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool IsOnBreak = false;

	//Current wave number. 0 = tutorial (no enemies, some menus to explain whats going on maybe? unless we make that in the main menu idk), and you have to skip to next wave manually
	//If WaveNumber >= length of Waves, ehhh figure it out. win? infinite mode? idk
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int WaveNumber = 0;

	// Current wave. 
	FWave* CurrentWave;

	//Current Enemy of Current Wave. Resets at each wave
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int CurrentEnemy = 0;

	//Next Enemy spawn time
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float NextSpawnIn = 0.0f;
};
