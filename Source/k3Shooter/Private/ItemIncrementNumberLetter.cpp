// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemIncrementNumberLetter.h"
#include "k3ShooterCharacter.h"

// Sets default values
AItemIncrementNumberLetter::AItemIncrementNumberLetter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemIncrementNumberLetter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemIncrementNumberLetter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemIncrementNumberLetter::Buy()
{
	Ak3ShooterCharacter* Character = Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
	if (Character->CurrentWordLength < 12) {
		Character->CurrentWordLength += 1;
		Character->GetNewTargetWord();
		Price*=1.25f;
		GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("AddOneLetter"));
	}
}