// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemHealthPotion.h"
#include "k3ShooterCharacter.h"

// Sets default values
AItemHealthPotion::AItemHealthPotion()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AItemHealthPotion::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AItemHealthPotion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AItemHealthPotion::Buy()
{
	Ak3ShooterCharacter* Character = Cast<Ak3ShooterCharacter>(UGameplayStatics::GetActorOfClass(GetWorld(), Ak3ShooterCharacter::StaticClass()));
	Character->Health += 10;
	GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("LifePotion"));
}