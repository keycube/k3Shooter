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
			if (WaveNumber > Waves->GetRowNames().Num()){ //TODO : change this condition to fallback on procgen only if findrow fails
				WavePoints = WaveNumber * 25.0f;
			} else CurrentWave = Waves->FindRow<FWave>(FName(*FString::FromInt(WaveNumber)), TEXT(""), false);
			CurrentEnemy = 0;
		}
	} else if (EndWave) {
		TArray<AActor*> aliveEnemies;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), Ak3ShooterEnemyBase::StaticClass(), aliveEnemies);
		if (aliveEnemies.Num() <= 0) {
			EndWave = false;
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
			
			// Procedural generation of waves if they're not preprogrammed
			if (WavePoints > 0.0f){
				auto c = GetRandomEnemyWithRemainingPoints(&WavePoints);
				if (c == nullptr){
					EndWave = true;
					return;
				}
				GetWorld()->SpawnActor<Ak3ShooterEnemyBase>(c, spawnedActorLocation, spawnedActorRotation, spawnedActorInfo);
				NextSpawnIn = FMath::RandRange(1.5f, 5.0f);
			} else { // If they are preprogrammed we just load them
				if (CurrentWave == nullptr) {
					EndWave = true;
					return;
				}
				GetWorld()->SpawnActor<Ak3ShooterEnemyBase>(CurrentWave->Enemies[CurrentEnemy], spawnedActorLocation, spawnedActorRotation, spawnedActorInfo); //TODO add check to see if it's present
			
				NextSpawnIn = FMath::RandRange(CurrentWave->MinimumTimeToSpawn, CurrentWave->MaximumTimeToSpawn);
				CurrentEnemy++;
				if (CurrentEnemy >= CurrentWave->Enemies.Num()) EndWave = true;
			}
		}
	}
}

TSubclassOf<Ak3ShooterEnemyBase> Ak3ShooterEnemySpawner::GetRandomEnemyWithRemainingPoints(float* Points){
	TArray<FEnemy> ViableEnemies;
	for (auto& e : Enemies){
		if (e.Points <= *Points) ViableEnemies.Add(e);
	}
	if (ViableEnemies.Num() <= 0) return nullptr;
	auto chosen = ViableEnemies[FMath::RandRange(0, ViableEnemies.Num()-1)];
	*Points -= chosen.Points;
	return chosen.Enemy;
}