// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterEnemySpawner.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


// Sets default values
Ak3ShooterEnemySpawner::Ak3ShooterEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	SpawnZone = CreateDefaultSubobject<UBoxComponent>("Box");

	RootComponent = SpawnZone;
}

// Called when the game starts or when spawned
void Ak3ShooterEnemySpawner::BeginPlay()
{
	Super::BeginPlay();
	CurrentWave = Waves->FindRow<FWave>(FName(*FString::FromInt(WaveNumber)), TEXT(""), false);
}

// Called every frame
void Ak3ShooterEnemySpawner::Tick(float DeltaTime){
	Super::Tick(DeltaTime);

	if (WaveNumber <= 0) return; // WaveNumber == 0 means tutorial. It will be set to 1 externally.

	if (IsOnBreak){
		BreakTime -= DeltaTime;
		if (BreakTime <= 0.0f) {
			IsOnBreak = false;
			WaveNumber++;
			CurrentWave = Waves->FindRow<FWave>(FName(*FString::FromInt(WaveNumber)), TEXT(""), false); //TODO : idk what to do if it doesnt exist lol
			CurrentEnemy = 0;
		}
	} else if (CurrentWave != nullptr && CurrentEnemy >= CurrentWave->Enemies.Num()) {
		TArray<AActor*> aliveEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Ak3ShooterEnemyBase::StaticClass(), aliveEnemies);
		if (aliveEnemies.Num() <= 0) {
			IsOnBreak = true;
			BreakTime = 30.0f;
		}
		return;
	} else {
		NextSpawnIn -= DeltaTime;
		if (NextSpawnIn <= 0.0f){
			//Spawn
			FRotator spawnedActorRotation(0.0f,0.0f,0.0f);
			FVector spawnedActorLocation = UKismetMathLibrary::RandomPointInBoundingBox(GetActorLocation(), SpawnZone->GetScaledBoxExtent());
			FActorSpawnParameters spawnedActorInfo;
			spawnedActorInfo.Owner = this;
			if (CurrentWave == nullptr) return;
			GetWorld()->SpawnActor<Ak3ShooterEnemyBase>(CurrentWave->Enemies[CurrentEnemy], spawnedActorLocation, spawnedActorRotation, spawnedActorInfo); //TODO add check to see if it's present

			NextSpawnIn = FMath::RandRange(CurrentWave->MinimumTimeToSpawn, CurrentWave->MaximumTimeToSpawn);
			CurrentEnemy++;
		}
	}
}

