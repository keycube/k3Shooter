// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemMoneyPerKill.h"
#include "k3ShooterCharacter.h"

// Sets default values
AItemMoneyPerKill::AItemMoneyPerKill()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemMoneyPerKill::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemMoneyPerKill::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemMoneyPerKill::Buy()
{
	Ak3ShooterCharacter* Character = Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
	Character->MoneyGain += 0.2f;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("MoneyPerKill"));
}