// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemAddDamageLetter.h"
#include "k3ShooterCharacter.h"

// Sets default values
AItemAddDamageLetter::AItemAddDamageLetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemAddDamageLetter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemAddDamageLetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemAddDamageLetter::Buy()
{
	Ak3ShooterCharacter* Character = Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
	Character->DamagePerLetter += 0.1f;
	Price*=1.5f;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("DamageIncreased"));
}