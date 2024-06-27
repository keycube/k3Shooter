// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterEnemyBase.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values
Ak3ShooterEnemyBase::Ak3ShooterEnemyBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create StaticMeshComponent and attach to BoxComponent
    HealthBar = CreateDefaultSubobject<UMaterialBillboardComponent>(TEXT("HealthBarBillboard"));
    HealthBar->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void Ak3ShooterEnemyBase::BeginPlay()
{
	GEngine->AddOnScreenDebugMessage(0x3011, 15.0f, FColor::Red, "Hey all scott here");
	Super::BeginPlay();
	GetPlayer();
	ResetToDefaultValues();
	GetCharacterMovement()->MaxWalkSpeed *= MovementSpeed;
	
}

// Called every frame
void Ak3ShooterEnemyBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (CurrentHealth <= 0.0f){
		OnDeath();
		Destroy();
	}
}

Ak3ShooterCharacter* Ak3ShooterEnemyBase::GetPlayer(){
	if (Player) return Player;
	else return Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
}


// You need to implement these yourself
void Ak3ShooterEnemyBase::ResetToDefaultValues_Implementation(){}
void Ak3ShooterEnemyBase::OnDeath_Implementation(){}