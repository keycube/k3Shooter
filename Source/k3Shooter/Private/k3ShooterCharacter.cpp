// Fill out your copyright notice in the Description page of Project Settings.


#include "k3ShooterCharacter.h"

// Sets default values
Ak3ShooterCharacter::Ak3ShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void Ak3ShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void Ak3ShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void Ak3ShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("AnyKey", IE_Released, this, &Ak3ShooterCharacter::OnAnyKeyPress);
}

void Ak3ShooterCharacter::OnAnyKeyPress(FKey key){
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, key.GetFName().ToString());
}
